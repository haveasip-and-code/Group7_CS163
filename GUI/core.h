#include<bits/stdc++.h>
#include "trie.h"
#include "ternarySearchTree.h"
#include <thread>
#include <atomic> //Why tf did i use this

using namespace std;

#ifndef CORE_H
#define CORE_H

string decode(string st);
int findSlot(int &x);
string intToString(int _number);

pair<string,string> getWordDef(trieNode* dataSet,string &cur);
pair<string,string> getWordDef(TSTNode* dataSet,string &cur);
pair<string,string> getWordDef(TST dataSet,string &cur);
pair<string,string> getWordDefAlways(TST dataSet,string &cur);
pair<string,string> getRandomWord(TST& dataSet);
pair<string,string> getRandomWord(TST& dataSet,int x);
void addWord(trieNode* dataSet,string &cur,string &definition);
void addWord(TSTNode* dataSet,string &cur,string &definition);
void addWord(TST &dataSet,string &cur,string &definition);
void deleteWord(TST& dataSet, string &cur);
void setStartSlot(int x);
void setDefinition(string &curWord,int slot,string &definition);

void bulkLoadingFromDataSet(trieNode* dataSet,string &path);
void bulkLoadingFromDataSet(TSTNode* dataSet,string &path);
void bulkLoadingFromDataSet(TST& dataSet,string &path);

void game(TST& data);
void invGame(TST& data);

void addHistory(pair<string,string> &cur);
void saveHistory();
void loadHistory();

void favourite(pair<string,string> &cur);
void saveFav();
void loadFav();

string standardize(string x,int y,int z);

int getsize(int);
int searchDef(int,int,vector<string>&,int);
void searchDefThread(int,int,int,vector<string>&,int,atomic<bool>&,atomic<int>&);

void transformDef(string&,vector<string>&);


#endif // CORE_H
