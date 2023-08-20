#pragma once
#include "core.h"
#include "prototype.h"
#include "metadata.h"
#include "trie.h"
#include "databankManager.h"
#include "generalLib.h"
#include "debugCore.h"
#include "initCore.h"

extern int dataSetCnt;
extern int curDataSet;

extern vector<pair<string,string>> favouriteList;
extern vector<pair<string,string>> historyList;

extern TST data;

void initialize() {
    historyList.clear();
    favouriteList.clear();
    loadFav();
    loadHistory();
    srand(time(nullptr));

    curDataSet=1;
    setStartSlot(getCurrentStartSlot());
    data.loadFromFile(getPath(1));

    debug("This go here");
}
