#include<bits/stdc++.h>
#include "trie.h"
#include "ternarySearchTree.h"

using namespace std;

#ifndef DATABANKMANAGER_H
#define DATABANKMANAGER_H

string getName(int x);
string getPath(int x);
int findName(string _name);
int getCurrentStartSlot();

pair<string,string> retrieveData(int slot,int key);

void saveCurrentDataSet(trieNode *cur);
void saveCurrentDataSet(TSTNode *cur);
void saveCurrentDataSet(TST &cur);
void createDatabank(string dataBankName);
void setDatabankDir(string path);

#endif //DATABANKMANAGER_H



