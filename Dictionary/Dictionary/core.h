#include<bits/stdc++.h>
#include "trie.h"
#include "ternarySearchTree.h"

using namespace std;

#ifndef CORE_H
#define CORE_H

string decode(string st);
int findSlot(int &x);
string intToString(int _number);

pair<string,string> getWordDef(trieNode* dataSet,string &cur);
pair<string,string> getWordDef(TSTNode* dataSet,string &cur);
void addWord(trieNode* dataSet,string &cur,string &definition);
void addWord(TSTNode* dataSet,string &cur,string &definition);
void addWord(TST &dataSet,string &cur,string &definition);
void setStartSlot(int x);
void setDefinition(string &curWord,int slot,string &definition);

void bulkLoadingFromDataSet(trieNode* dataSet,string &path);
void bulkLoadingFromDataSet(TSTNode* dataSet,string &path);

#endif // CORE_H
