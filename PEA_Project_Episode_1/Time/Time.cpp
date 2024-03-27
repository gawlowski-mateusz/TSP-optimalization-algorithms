//
// Created by Mateusz on 23/10/2023.
//

#include <chrono>
#include "Time.h"

using namespace std;
using namespace std::chrono;

void Time::startTime() {
    startingTime = high_resolution_clock::now();
    // Record the current time as the starting time.
}

void Time::stopTime() {
    endTime = high_resolution_clock::now();
    // Record the current time as the ending time.
}

unsigned long long Time::processTime() {
    return duration_cast<nanoseconds>(Time::endTime - Time::startingTime).count();
    // Calculate the time elapsed between start and stop in nanoseconds and return it.
}
