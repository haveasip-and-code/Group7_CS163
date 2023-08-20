#pragma once
#include <bits/stdc++.h>
#include "timeModule.h"
using namespace std;

double timePoint::timeDiff(timePoint x) {
    return abs(std::chrono::duration<double, std::milli>(x.tPoint-tPoint).count());
}

double timePoint::timeDiff() {
    return abs(std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now()-tPoint).count());
}
