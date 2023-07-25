#pragma once
#include <bits/stdc++.h>
#include "core.h"
#include "generalLib.h"
#include "debugCore.h"
#include "databankManager.h"
#include "timeModule.h"

extern int curDataSet;
extern int curMaxSlot;
extern int dataSetCnt;

extern string databankDir;
extern bool debugFlag;

void addWord(trieNode* dataSet,string &cur,string &definition) {
    trieNode* tmp=dataSet->insert(cur);
    if (!tmp) {
        //Something is wrong here.
        debug("Failure when trying to add string \""+cur+"\": Insert function get to an null node.");
        return;
    }
    else {
        //Everything is right here.
        setDefinition(cur,findSlot(tmp->storagelocation),definition);
        debug("Successful when trying to add string \""+cur+"\"!!!");
        return;
    }
}

void addWord(TSTNode* dataSet,string &cur,string &definition) {
    TSTNode* tmp=dataSet->insert(cur);
    if (!tmp) {
        //Something is wrong here.
        debug("Failure when trying to add string \""+cur+"\": Insert function get to an null node.");
        return;
    }
    else {
        //Everything is right here.
        setDefinition(cur,findSlot(tmp->val),definition);
        debug("Successful when trying to add string \""+cur+"\"!!!");
        return;
    }
}

void addWord(TST& dataSet,string &cur,string &definition) {
    addWord(dataSet.pRoot,cur,definition);
}


pair<string,string> getWordDef(trieNode* dataSet,string &cur) {
    trieNode* tmp=dataSet->get(cur);
    pair<string,string> kq;
    if (!tmp) {
        //Something is wrong here.
        debug("Failure when trying to get definition of string \""+cur+"\": Either a exception or the word haven't been added.");
        kq.first=cur;
        kq.second="A definition have not been set for this word.";
        return kq;
    }
    else {
        kq=retrieveData(curDataSet,tmp->storagelocation);
        debug("Successful when trying to get definition of string \""+cur+"\"!!!");
        return kq;
    }
}

pair<string,string> getWordDef(TSTNode* dataSet,string &cur) {
    TSTNode* tmp=dataSet->get(cur);
    pair<string,string> kq;
    if (!tmp) {
        //Something is wrong here.
        debug("Failure when trying to get definition of string \""+cur+"\": Either a exception or the word haven't been added.");
        kq.first=cur;
        kq.second="A definition have not been set for this word.";
        return kq;
    }
    else {
        kq=retrieveData(curDataSet,tmp->val);
        debug("Successful when trying to get definition of string \""+cur+"\"!!!");
        return kq;
    }
}

string decode(string st) {
    string kq="";
    for (int ii=0;ii<st.length();ii++) {
        if (st[ii]>='a'&&st[ii]<='z') {
            kq+=st[ii];
        }
        else if (st[ii]>='A'&&st[ii]<='Z') {
            kq+='_';
            kq+=st[ii];
        }
        else if (st[ii]=='\'') {
            kq+=st[ii];
        }
        else if (st[ii]=='à') {
            kq+="#af#";
        }

    }
}

int findSlot(int &x) {
    if (x==0) {
        curMaxSlot++;
        x=curMaxSlot;
    }
    return x;
}

void setStartSlot(int x) {
    curMaxSlot=x;
}

string intToString(int _number) {
    string kq="";
    int tmp=1;
    if (_number<0) {
        _number=-_number;
        tmp=-1;
    }
    if (_number==0) return "0";
    while (_number>0) {
        kq=char(_number%10+'0')+kq;
        _number/=10;
    }
    if (tmp==-1) {
        return "-"+kq;
    }
    else {
        return kq;
    }
}

void setDefinition(string &curWord,int slot,string &definition) {
    ofstream outputLog;
    outputLog.open(getPath(curDataSet)+"/"+intToString(slot)+".txt");
    outputLog<<curWord<<'\n';
    outputLog<<definition<<'\n';
    outputLog<<'\n';
}

void bulkLoadingFromDataSet(trieNode* dataSet,string &path) {
    timePoint debugStart=timePoint();
    debugFlag=false;
    ifstream inp;
    inp.open(path);
    string s1,s2;
    while (inp>>s1) {
        getline(cin,s2);
        addWord(dataSet,s1,s2);
    }
    inp.close();
    debugFlag=true;
    debug("Bulk loading from "+path+" in "+to_string(debugStart.timeDiff())+"ms");
}

void bulkLoadingFromDataSet(TSTNode* dataSet,string &path) {
    timePoint debugStart=timePoint();
    debugFlag=false;
    ifstream inp;
    inp.open(path);
    string s1,s2;
    while (inp>>s1) {
        getline(inp,s2);
        addWord(dataSet,s1,s2);
    }
    inp.close();
    debugFlag=true;
    debug("Bulk loading from "+path+" in "+to_string(debugStart.timeDiff())+"ms");
}

