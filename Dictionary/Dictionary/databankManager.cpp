#pragma once
#include <bits/stdc++.h>
#include <direct.h>
#include "databankManager.h"
#include "debugCore.h"

int curDataSet;

extern int curMaxSlot;
extern int dataSetCnt;
extern string databankDir;

extern string intToString(int _number);

void createDatabank(string dataBankName) {
    dataSetCnt++;
    int status = mkdir((databankDir+"/"+intToString(dataSetCnt)).c_str());
    if ((status < 0)) {
        if (errno!=EEXIST) debug("Databank \""+dataBankName+"\" was not created.");
        else {
            debug("Databank \""+dataBankName+"\" already exist.");
            ofstream tmpStream;
            tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/name.txt");
            tmpStream<<dataBankName;
            tmpStream.close();
            tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/structure.txt");
            for (int ii=0;ii<trieNodeConst::tSize;ii++) {
                tmpStream<<-1<<' ';
            }
            tmpStream<<'\n';
            tmpStream.close();
            tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/TST.txt");
            tmpStream<<0<<' '<<"000"<<'\n';
            tmpStream.close();
            tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/maxslot.txt");
            tmpStream<<0;
            tmpStream.close();
        }
    }
    else {
        debug("Databank \""+dataBankName+"\" was created.");
        ofstream tmpStream;
        tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/name.txt");
        tmpStream<<dataBankName;
        tmpStream.close();
        tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/structure.txt");
        for (int ii=0;ii<trieNodeConst::tSize;ii++) {
            tmpStream<<-1<<' ';
        }
        tmpStream<<'\n';
        tmpStream.close();
        tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/TST.txt");
        tmpStream<<0<<' '<<"000"<<'\n';
        tmpStream.close();
        tmpStream.open(databankDir+"/"+intToString(dataSetCnt)+"/maxslot.txt");
        tmpStream<<0;
        tmpStream.close();
    }
}

void setDatabankDir(string path) {
    databankDir=path;
}

string getName(int x) {
    string kq="";
    ifstream tmpStream;
    tmpStream.open(databankDir+"/"+intToString(x)+"/name.txt");
    tmpStream>>kq;
    tmpStream.close();
    if (kq=="") {
        debug("Can't get name of data set "+intToString(x)+", either it doesn't exist or the name was set to empty.");
    }
    return kq;
}

int findName(string _name) {
    for (int ii=1;ii<=dataSetCnt;ii++) {
        if (getName(ii)==_name) {
            return ii;
        }
    }
    debug("Can't find data set with name \""+_name);
    return -1;
}

string getPath(int x) {
    return (databankDir+"/"+intToString(x));
}

pair<string,string> retrieveData(int slot,int key) {
    pair<string,string> kq;
    ifstream tmpStream;
    tmpStream.open(databankDir+"/"+intToString(slot)+"/"+intToString(key)+".txt");
    getline(tmpStream,kq.first);
    getline(tmpStream,kq.second);
    tmpStream.close();
    if (kq.first==""&&kq.second=="") {
        debug("Can't get definition and word in slot "+intToString(slot)+" with key "+intToString(key)+".");
    }
    return kq;
}

void saveCurrentDataSet(trieNode* cur) {
    cur->saveToFile(getPath(curDataSet));
    ofstream tmpStream;
    tmpStream.open(databankDir+"/"+intToString(curDataSet)+"/"+"maxslot.txt");
    tmpStream<<curMaxSlot<<'\n';
    tmpStream.close();
}

void saveCurrentDataSet(TST &cur) {
    saveCurrentDataSet(cur.pRoot);
}

void saveCurrentDataSet(TSTNode* cur) {
    cur->saveToFile(getPath(curDataSet));
    ofstream tmpStream;
    tmpStream.open(databankDir+"/"+intToString(curDataSet)+"/"+"maxslot.txt");
    tmpStream<<curMaxSlot<<'\n';
    tmpStream.close();
}

int getCurrentStartSlot() {
    int kq;
    ifstream tmpStream;
    tmpStream.open(databankDir+"/"+intToString(curDataSet)+"/"+"maxslot.txt");
    tmpStream>>kq;
    tmpStream.close();
    return kq;
}
