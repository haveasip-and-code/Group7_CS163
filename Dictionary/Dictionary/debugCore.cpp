#pragma once
#include <bits/stdc++.h>
#include "debugCore.h"
#include "timeModule.h"

extern string debugLogPath;
extern bool debugFlag;

void setDebugLog(string path) {
    debugLogPath=path;
}

void debug(string _log) {
    if (!debugFlag) return;
    ofstream debugLog;
    debugLog.open(debugLogPath, std::ios_base::app);
    debugLog<<_log<<'\n';
    debugLog.close();
}
