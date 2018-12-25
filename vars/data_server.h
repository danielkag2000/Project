#ifndef PROJECT_DATA_READER_SERVER_H
#define PROJECT_DATA_READER_SERVER_H

#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include "../exceptions.h"
#include "../fdlist.h"

using namespace std;

class DataReaderServer {
private:
    int _port;
    int _hz;

    FdList _fds;
    unordered_map<string, double> _paths;
    mutex _dataLock;

    thread* _serverThread;

    int openServer();
    int connectClient(int server);
    void readData(int client, int hz);

    int readOneVar(int client);
    void readOneSequence(int client);
public:
    /**
     * Create a new data reader server.
     * @param port the port to run on
     * @param hz the frequency per second
     */
    DataReaderServer(int port, int hz) : _port(port), _hz(hz) {
    }

    /**
     * Open the data server.
     */
    void open();

    /**
     * Close the data server.
     */
    void close();

    bool isOpen();

    /**
     * Get a value that was read in the past.
     * @param name the path of the value
     * @return the value
     */
    double getValue(const string& name);

    ~DataReaderServer() { close(); }
};

class DataSender {
private:
    int _port;
    string _remoteIp;

    int _socket;

    FdList _clientFds;
public:
    DataSender(int port, const string& remoteIp) :
        _port(port), _remoteIp(remoteIp), _socket(-1) {
    }

    void open();
    void close();

    bool isOpen();

    void send(const string& path, double data);

    ~DataSender() { close(); }
};

class DataTransfer {
private:
    DataReaderServer* _reader;
    DataSender* _sender;

public:
    DataTransfer() : _reader(nullptr), _sender(nullptr) {}

    void openDataServer(int port, int hz);

    void closeDataServer();

    void openSender(int port, const string& remoteIp);

    void closeSender();

    void closeAll();

    double getValue(const string& name) const {
        return _reader->getValue(name);
    }

    void setValue(const string& path, double val) {
        _sender->send(path, val);
    }

    ~DataTransfer() {
        closeAll();
    }
};

#endif //PROJECT_DATA_READER_SERVER_H
