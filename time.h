#ifndef PROJECT_TIME_H
#define PROJECT_TIME_H

#include <chrono>

using namespace std::chrono;

/**
 * Get the current time as milliseconds.
 * @return the time
 */
inline milliseconds currentMillis() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

/**
 * Convert an integer milliseconds to a milliseconds object
 * @param time the time in milliseconds
 * @return a milliseconds object
 */
inline milliseconds asMillis(int time) {
    return duration_cast<milliseconds>(milliseconds(time));
}

#endif
