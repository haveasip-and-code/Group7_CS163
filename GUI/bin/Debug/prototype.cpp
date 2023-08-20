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

extern vector<pair<string,string>> favouriteList;
extern vector<pair<string,string>> historyList;

extern TST data;

int prototypemode() {
    loadMetaData();
    historyList.clear();
    favouriteList.clear();
    loadFav();
    loadHistory();
    srand(time(nullptr));
    cout<<"Welcome to Dictionary!\n";
    while (true) {
        int cmd=0;
        cout<<"What do you want to do?\n";
        cout<<"1. Add a data set\n";
        cout<<"2. Access a data set\n";
        cout<<"3. See history\n";
        cout<<"4. See favourtie\n";
        cout<<"Other. Exit\n";
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
            data.loadFromFile(getPath(cmd));
            while (true) {
                cout<<"What do you want to do?\n";
                cout<<"1. Set definition for a word\n";
                cout<<"2. Get definition for a word\n";
                cout<<"3. Bulk loading data set from file (developer feature, do not use)\n";
                cout<<"4. Get random word\n";
                cout<<"5. Guess the meaning\n";
                cout<<"6. Choose the correct word\n";
                cout<<"7. Delete a word\n";
                cout<<"Other. Exit\n";
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
                    addHistory(kq);
                    cout<<"Mark word as favourite? (Y/N)\n";
                    cin>>cur;
                    if (cur=="Y") {
                        favourite(kq);
                    }
                }
                else if (cmd==3) {
                    cout<<"Please enter the path to the file: ";
                    string cur;
                    cin>>cur;
                    bulkLoadingFromDataSet(data,cur);
                    saveCurrentDataSet(data);
                    saveMetaData();
                    data.clear();
                }
                else if (cmd==4) {
                    pair<string,string> kq;
                    kq=getRandomWord(data);
                    cout<<"Your word: "<<kq.first<<'\n';
                    cout<<"Definition: "<<kq.second<<'\n';
                }
                else if (cmd==5) {
                    game(data);
                }
                else if (cmd==6) {
                    invGame(data);
                }
                else if (cmd==7) {
                    string cur;
                    cout<<"Enter your word: ";
                    cin>>cur;
                    deleteWord(data,cur);
                }
                else {
                    cout<<"Thank you. Please go to sleep!\n";
                    break;
                }
            }
        }
        else if (cmd==3) {
            cout<<"History:\n";
            for (int i=0;i<10;i++) {
                if (i==historyList.size()) break;
                cout<<historyList[i].first<<'\n';
            }
        }
        else if (cmd==4) {
            cout<<"Favourite:\n";
            for (int i=0;i<favouriteList.size();i++) {
                cout<<favouriteList[i].first<<'\n';
            }
        }
        else {
            cout<<"Thank you. Please go to sleep!\n";
            break;
        }
    }
    cout<<"Program terminating, please wait...\n";
    //saveCurrentDataSet(data);
    //saveMetaData();
    saveFav();
    saveHistory();
    cout<<"Finished, see you again.\n";
    exit(0);
}
