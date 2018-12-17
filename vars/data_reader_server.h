#ifndef PROJECT_DATA_READER_SERVER_H
#define PROJECT_DATA_READER_SERVER_H

#include "stable.h"

class DataReaderServer {
private:
    int _port;
    int _hz;

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
};


#endif //PROJECT_DATA_READER_SERVER_H
