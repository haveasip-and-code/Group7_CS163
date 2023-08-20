#include<bits/stdc++.h>
#include<chrono>

using namespace std;

#ifndef TIMEMODULE_H
#define TIMEMODULE_H

struct timePoint {
    std::chrono::steady_clock::time_point tPoint;

    timePoint() {
        tPoint=std::chrono::steady_clock::now();
    }

    double timeDiff(timePoint x);
    double timeDiff();
};

#endif //TIMEMODULE_H



