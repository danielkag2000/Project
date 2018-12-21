//
// Created by Evyatar on 12/21/2018.
//

#ifndef PROJECT_FDLIST_H
#define PROJECT_FDLIST_H

#include <list>
#include <mutex>
#include <unistd.h>

using namespace std;

class FdList {
private:
    list<int> _fds;
    mutex _lock;

public:
    void addFd(int fd) {
        _lock.lock();
        _fds.push_back(fd);
        _lock.unlock();
    }

    void closeFds() {
        _lock.lock();
        for (int& fd : _fds) {
            close(fd);
        }

        _fds.clear();
        _lock.unlock();
    }

    int count() {
        _lock.lock();
        int count = _fds.size();
        _lock.unlock();
        return count;
    }
};




#endif //PROJECT_FDLIST_H
