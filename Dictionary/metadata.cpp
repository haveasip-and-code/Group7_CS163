#pragma once
#include <bits/stdc++.h>
#include "metadata.h"
#include "generalLib.h"

extern string metaDataPath;

extern int dataSetCnt;

void setMetaDataPath(string x) {
    metaDataPath=x;
}

void loadMetaData() {
    ifstream metaDataIn;
    metaDataIn.open(metaDataPath);
    metaDataIn>>dataSetCnt;
    metaDataIn.close();
}

void saveMetaData() {
    ofstream metaDataOut;
    metaDataOut.open(metaDataPath);
    metaDataOut<<dataSetCnt;
    metaDataOut.close();
}

