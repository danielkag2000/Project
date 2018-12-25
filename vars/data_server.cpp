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
        "/instrumentation/heading-indicator/offset-deg",
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

int DataReaderServer::openServer() {
    // get socket id
    const int server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0) {
        throw SocketException("Failed opening server.");
    }

    // add the server as a file descriptor
    _fds.addFd(server);

    // setup address
    sockaddr_in address{};
    address.sin_family = AF_INET;           // protocol ipv4
    address.sin_addr.s_addr = INADDR_ANY;   // open it on every possible
    address.sin_port = htons(_port);

    // bind server
    const int bindRes = bind(server, (sockaddr*) &address, sizeof(address));

    // listen to data connection (expecting only 1)
    const int listenRes = listen(server, 5);

    if (bindRes < 0 || listenRes < 0) {
        _fds.closeFds();
        throw SocketException("Failed binding or listening.");
    }

    return server;
}

int DataReaderServer::connectClient(int server) {
    int client = accept(server, nullptr, nullptr);

    cout << "accepted" << endl;
    if (client < 0) {
        _fds.closeFds();
        throw SocketException("Failed connecting to client.");
    }

    _fds.addFd(client);

    return client;
}

void DataReaderServer:: readOneSequence(int client) {
    _dataLock.lock();

    for (const string& path : path_list) {
        double val = readVar(client);
        _paths[path] = val;
    }

    _dataLock.unlock();
}

void DataReaderServer::readData(int client, int hz) {
    milliseconds sleepDuration(asMillis(1000 / hz));

    // while the sockets are open
    while (_fds.count()) {
        // get current ms
        milliseconds ms(currentMillis());

        // insert all flight data
        readOneSequence(client);

        // sleep until next iteration
        ms = currentMillis() - ms;
        this_thread::sleep_for(sleepDuration - ms);
    }
}

void DataReaderServer::open() {
    int server = openServer();
    int client = connectClient(server);

    // wait until reading just the first sequence
    readOneSequence(client);

    // run the server thread on the current inner state
    _serverThread = new thread(&DataReaderServer::readData,
            this, client, _hz);
}

void DataReaderServer::close() {
    _fds.closeFds();
    _serverThread->join();
}

bool DataReaderServer::isOpen() {
    return _fds.count() > 0;
}

double DataReaderServer::getValue(const string &name) {
    _dataLock.lock();
    double val = _paths[name];
    _dataLock.unlock();
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
    bcopy(server->h_addr, (char *)&address.sin_addr.s_addr, server->h_length);
    address.sin_port = htons(_port);

    if (connect(_socket, (sockaddr*) &address, sizeof(address)) < 0) {
        _clientFds.closeFds();
        throw SocketException("Failed connecting to server.");
    }
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
    return _clientFds.count();
}

void DataTransfer::openDataServer(int port, int hz) {
    // close reader if needed
    closeDataServer();

    _reader = new DataReaderServer(port, hz);
    _reader->open();
}

void DataTransfer::closeDataServer() {
    delete _reader;
    _reader = nullptr;
}

void DataTransfer::openSender(int port, const string &remoteIp) {
    // close sender if needed
    closeSender();

    _sender = new DataSender(port, remoteIp);
    _sender->open();
}

void DataTransfer::closeSender() {
    delete _sender;
    _sender = nullptr;
}

void DataTransfer::closeAll() {
    closeDataServer();
    closeSender();
}