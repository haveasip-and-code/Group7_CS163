#include <bits/stdc++.h>
#include "core.h"
#include "prototype.h"
#include "metadata.h"
#include "trie.h"
#include "databankManager.h"
#include "generalLib.h"

using namespace std;

int main()
{
    prototypemode();
    return 0;
    setStartSlot(0);
    //setDatabankDir("databank");
    //setDebugLog("debugLog/log1.txt");
    trieNode* tmp;
    string st;
    st="aaaaaaa";
    string def;
    def="a abnormal string";
    addWord(tmp,st,def);
    createDatabank("Test");
    saveMetaData();
}
