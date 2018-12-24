#include "data_server.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>
#include <list>
#include <sys/ioctl.h>
#include <vector>
#include <netdb.h>
#include <set>
#include <sstream>
#include <cmath>
#include "../time.h"
#include "../fdlist.h"
#include "../utils.h"

mutex dataLock;
unordered_map<string, double> values;
thread* serverThreadPtr;

FdList serverfds; // a list of open file descriptors

list<string> path_list {
        "/instrumentation/airspeed-indicator/indicated-speed-kt",
        "/instrumentation/altimeter/indicated-altitude-ft",
        "/instrumentation/altimeter/pressure-alt-ft",
        "/instrumentation/attitude-indicator/indicated-pitch-deg",
        "/instrumentation/attitude-indicator/indicated-roll-deg",
        "/instrumentation/attitude-indicator/internal-pitch-deg",
        "/instrumentation/attitude-indicator/internal-roll-deg",
        "/instrumentation/encoder/indicated-altitude-ft",
        "/instrumentation/encoder/pressure-alt-ft",
        "/instrumentation/gps/indicated-altitude-ft",
        "/instrumentation/gps/indicated-ground-speed-kt",
        "/instrumentation/gps/indicated-vertical-speed",
        "/instrumentation/heading-indicator/indicated-heading-deg",
        "/instrumentation/magnetic-compass/indicated-heading-deg",
        "/instrumentation/slip-skid-ball/indicated-slip-skid",
        "/instrumentation/turn-indicator/indicated-turn-rate",
        "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
        "/controls/flight/aileron",
        "/controls/flight/elevator",
        "/controls/flight/rudder",
        "/controls/flight/flaps",
        "/controls/engines/curret-engine/throttle",
        "/engines/engine/rpm"
};

set<string> path_set(path_list.begin(), path_list.end());

const set<char> delims{ ',', '\n' };

/**
 * Read one double from client socket
 * @param client the client socket id
 * @return the double
 */
double readVar(int client) {
    // get all double string from user
    string in;
    char input;
    while (read(client, &input, sizeof(input)) > 0 && delims.count(input) == 0) {
        in += input;
    }

    if (!isNumber(in)) {
        return NAN;
    }

    return stod(in);
}

/**
 * Reads and inserts all data from socket client
 * @param client the socket client id
 */
void readInsertAllData(int client) {
    dataLock.lock();

    for (const string& path : path_list) {
        double val = readVar(client);
        values[path] = val;
    }

    dataLock.unlock();
}

struct serverInfo {
    int port;
    int hz;
};

/**
 * Create the server thread
 * @param info information to open the server with
 * @param caller the caller thread
 */
void serverThread(serverInfo* info, pthread_t caller) {
    // get socket id
    int server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0) {
        throw SocketException("Failed opening server.");
    }

    serverfds.addFd(server);

    // setup address
    sockaddr_in address;
    address.sin_family = AF_INET;           // protocol ipv4
    address.sin_addr.s_addr = INADDR_ANY;   // open it on every possible
    address.sin_port = htons(info->port);

    sockaddr* addr = (sockaddr*) &address;
    socklen_t addrlen = sizeof(address);

    // bind server
    int bindRes = bind(server, addr, addrlen);

    // listen to data connection (expecting only 1)
    int listenRes = listen(server, 5);

    if (bindRes < 0 || listenRes < 0) {
        serverfds.closeFds();
        throw SocketException("Failed binding or listening.");
    }

    // accept data client
    int client = accept(server, addr, &addrlen);

    if (client < 0) {
        serverfds.closeFds();
        throw SocketException("Failed connecting to client.");
    }

    serverfds.addFd(client);

    // calculate time between calls
    milliseconds sleepDuration(asMillis(1000 / info->hz));

    delete info;

    bool paused = true;

    // NOTE: we're blocked by read anyway, so we don't need to sleep as it occurs automatically
    while (serverfds.count()) { // while there are the sockets open
        // get current ms
        milliseconds ms(currentMillis());

        // insert all flight data
        readInsertAllData(client);

        if (paused) {
            // if the main thread is waiting, let it continue
            pthread_kill(caller, SIGCONT);
            paused = false;
        }
//        // sleep until next iteration
        ms = currentMillis() - ms;
        this_thread::sleep_for(sleepDuration - ms);
    }
}

void DataReaderServer::open() {
    serverInfo* info = new serverInfo{ _port, _hz };
    serverThreadPtr = new thread(serverThread, info, pthread_self());

    pause(); // wait until first input
}

void DataReaderServer::close() {
    serverfds.closeFds();
    serverThreadPtr->join();
}

bool DataReaderServer::isOpen() {
    return serverfds.count();
}

double DataReaderServer::getValue(const string &name) const {
    dataLock.lock();
    double val = values[name];
    dataLock.unlock();
    return val;
}


void DataSender::open() {
    sockaddr_in address;
    hostent*    server;

    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_socket < 0) {
        throw SocketException("Couldn't open sender socket.");
    }

    _clientFds.addFd(_socket);

    server = gethostbyname(_remoteIp.c_str());

    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *)&address.sin_addr.s_addr, server->h_length);
    address.sin_port = htons(_port);

    if (connect(_socket, (sockaddr*) &address, sizeof(address)) < 0) {
        _clientFds.closeFds();
        throw SocketException("Failed connecting to server.");
    }
}

inline bool pathExists(const string& path) {
    return path_set.count(path) > 0;
}

void DataSender::send(const string &path, double data) {

    stringstream ss;
    ss << "set " << path << " " << data << "\r\n";

    string sendStr = ss.str();

    if (::send(_socket, sendStr.c_str(), sendStr.length(), 0) < 0) {
        perror("Failed writing to socket.\n");
    }
}

void DataSender::close() {
    _clientFds.closeFds();
}

bool DataSender::isOpen() {
    return _clientFds.count() > 0;
}

void DataTransfer::openDataServer(int port, int hz) {
    delete _reader; // delete if needed(read from the internet - it's ok to delete a null pointer)

    _reader = new DataReaderServer(port, hz);
    _reader->open();
}

void DataTransfer::closeDataServer() {
    delete _reader;
    _reader = nullptr;
}

void DataTransfer::openSender(int port, const string &remoteIp) {
    delete _sender; // delete if needed

    _sender = new DataSender(port, remoteIp);
    _sender->open();

    if (!_sender->isOpen()) {
        delete _sender;
        _sender = nullptr;
        throw SocketException("Failed opening sender.");
    }
}

void DataTransfer::closeSender() {
    delete _sender;
    _sender = nullptr;
}

void DataTransfer::closeAll() {
    closeDataServer();
    closeSender();
}