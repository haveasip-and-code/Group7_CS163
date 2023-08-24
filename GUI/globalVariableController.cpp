#pragma once
#include <bits/stdc++.h>
#include "globalVariableController.h"
#include "storage.h"
#include "ternarySearchTree.h"
#include "wx/sound.h"
#include "wx/setup.h"

//From core.h
int curMaxSlot;
int dataSetCnt;

string debugLogPath="debugLog/log1.txt";
string databankDir="databank";

//From metadata.h
string metaDataPath="coreData/metaData.txt";
string favorDataPath="coreData/favData.txt";

bool writeFlag=true;
bool debugFlag=true;

string historyPath="coreData/hist.txt";
string favouritePath="coreData/fav.txt";

TST data1=TST();
TST favor=TST();

//From user
//Container userData;
//string user_userDataPath;
//string user_userDataName;


