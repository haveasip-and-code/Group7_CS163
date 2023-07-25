#pragma once
#include <bits/stdc++.h>
#include "prototype.h"
#include "core.h"
#include "metadata.h"
#include "trie.h"
#include "databankManager.h"
#include "generalLib.h"
#include "databankManager.h"

extern int dataSetCnt;
extern int curDataSet;

int prototypemode() {
    loadMetaData();
    //TST data=TST();
    TSTNode* data=new TSTNode();
    cout<<"Welcome to Dictionary!\n";
    while (true) {
        int cmd=0;
        cout<<"What do you want to do?\n";
        cout<<"1. Add a data set\n";
        cout<<"2. Access a data set\n";
        cout<<"3. Exit\n";
        cin>>cmd;
        if (cmd==1) {
            cout<<"Please type the name of your data set: ";
            string tmp;
            cin>>tmp;
            createDatabank(tmp);
        }
        else if (cmd==2) {
            cout<<"Please pick a data set: \n";
            cmd=0;
            while (cmd==0) {
                for (int ii=1;ii<=dataSetCnt;ii++) {
                    cout<<ii<<". "<<getName(ii)<<'\n';
                }
                cin>>cmd;
                if (cmd>dataSetCnt||cmd<=0) {
                    cout<<"Invalid input. Try again.\n";
                    cmd=0;
                }
            }
            curDataSet=cmd;
            setStartSlot(getCurrentStartSlot());
            data->loadFromFile(getPath(cmd));
            while (true) {
                cout<<"What do you want to do?\n";
                cout<<"1. Set definition for a word\n";
                cout<<"2. Get definition for a word\n";
                cout<<"3. Bulk loading data set from file (developer feature, do not use)\n";
                cout<<"4. Exit\n";
                cmd=0;
                cin>>cmd;
                if (cmd==1) {
                    string cur,def;
                    cout<<"Enter your word: ";
                    cin>>cur;
                    cout<<"Enter your definition: ";
                    cin>>def;
                    addWord(data,cur,def);
                }
                else if (cmd==2) {
                    string cur,def;
                    cout<<"Enter your word: ";
                    cin>>cur;
                    pair<string,string> kq;
                    kq=getWordDef(data,cur);
                    cout<<"Your word: "<<kq.first<<'\n';
                    cout<<"Definition: "<<kq.second<<'\n';
                }
                else if (cmd==3) {
                    cout<<"Please enter the path to the file: ";
                    string cur;
                    cin>>cur;
                    bulkLoadingFromDataSet(data,cur);
                    saveCurrentDataSet(data);
                    saveMetaData();
                }
                else if (cmd==4) {
                    cout<<"Thank you. Please go to sleep!\n";
                    break;
                }
            }
        }
        else if (cmd==3) {
            cout<<"Thank you. Please go to sleep!\n";
            break;
        }
    }
    cout<<"Program terminating, please wait...\n";
    saveCurrentDataSet(data);
    saveMetaData();
    cout<<"Finished, see you again.\n";
    exit(0);
}
