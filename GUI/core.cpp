#pragma once
#include <bits/stdc++.h>
#include <direct.h>
#include "core.h"
#include "generalLib.h"
#include "debugCore.h"
#include "databankManager.h"
#include "timeModule.h"
#include "flagging.h"
#include "wx/sound.h"

extern int curDataSet;
extern int curMaxSlot;
extern int dataSetCnt;

extern string databankDir;
extern bool debugFlag;
extern bool writeFlag;

const int blcsize=1000;

string separator="-0o+-lso6483";

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
    TSTNode* tmp=dataSet->insert(encrypt(cur));
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

pair<string,string> getWordDefAlways(TSTNode* dataSet,string &cur) {
    TSTNode* tmp=dataSet->getAlways(cur);
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
        if (kq.first=="") kq.first="Unknown word!!";
        else if (kq.second=="") kq.second="A definition have not been set for this word.";
        debug("Successful when trying to get definition of string \""+cur+"\"!!!");
        return kq;
    }
}


pair<string,string> getWordDef(TST dataSet,string &cur) {
    return getWordDef(dataSet.pRoot,cur);
}

pair<string,string> getWordDefAlways(TST dataSet,string &cur) {
    return getWordDefAlways(dataSet.pRoot,cur);
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

string intToString(int* _number) {
    int tmp=*_number;
    return intToString(tmp);
}

void setDefinition(string &curWord,int slot,string &definition) {
    if (!writeFlag) return;
    //mkdir((getPath(curDataSet)+"/"+intToString(slot/blcsize)).c_str());
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
    int cntt=0;
    while (getline(inp,s1)&&cntt<=200000) {
        if ((s1.length()>0&&s1[0]=='-')&&(s1.length()>1&&s1[1]=='-')&&(s1.length()>2&&s1[2]=='-')) {
            continue;
        }
        string tmp="";
        while (getline(inp,s2)) {
            if ((s2.length()>0&&s2[0]=='-')&&(s2.length()>1&&s2[1]=='-')&&(s2.length()>2&&s2[2]=='-')) {
                break;
            }
            else {
                if (tmp=="") tmp=s2;
                else tmp+="\n"+s2;
            }
        }
        //cout<<s1<<'\n';
        //cout<<tmp<<'\n';
        addWord(dataSet,s1,tmp);
        cntt++;
    }
    inp.close();
    debugFlag=true;
    debug("Bulk loading from "+path+" in "+to_string(debugStart.timeDiff())+"ms");
}

void bulkLoadingFromDataSet(TST& dataSet,string &path) {
    bulkLoadingFromDataSet(dataSet.pRoot,path);
}

pair<string,string> getRandomWord(TST& dataSet) {
    int p=rand()%curMaxSlot+1;
    pair<string,string> kq;
    kq=retrieveData(curDataSet,p);
    while (kq.second=="A definition have not been set for this word."||kq.second=="") {
        p=rand()%curMaxSlot+1;
        kq=retrieveData(curDataSet,p);
    }
    return kq;
}

pair<string,string> getRandomWord(TST& dataSet,int x) {
    int p=rand()%curMaxSlot+1;
    pair<string,string> kq;
    kq=retrieveData(curDataSet,p,x);
    while (kq.second=="A definition have not been set for this word.") {
        p=rand()%curMaxSlot+1;
        kq=retrieveData(curDataSet,p);
    }
    return kq;
}

void game(TST& data1) {
    pair<string,string> p[4];
    int idx=rand()%4;
    for (int i=0;i<4;i++) {
        p[i]=getRandomWord(data1);
    }
    cout<<p[idx].second<<'\n';
    cout<<"1. "<<p[0].first<<'\n';
    cout<<"2. "<<p[1].first<<'\n';
    cout<<"3. "<<p[2].first<<'\n';
    cout<<"4. "<<p[3].first<<'\n';
    int ans;
    cin>>ans;
    if (ans-1==idx) {
        cout<<"Correct\n";
    }
    else {
        cout<<"Incorrect\n";
    }
}

void invGame(TST& data1) {
    pair<string,string> p[4];
    int idx=rand()%4;
    for (int i=0;i<4;i++) {
        p[i]=getRandomWord(data1);
    }
    cout<<p[idx].first<<'\n';
    cout<<"1. "<<p[0].second<<'\n';
    cout<<"2. "<<p[1].second<<'\n';
    cout<<"3. "<<p[2].second<<'\n';
    cout<<"4. "<<p[3].second<<'\n';
    int ans;
    cin>>ans;
    if (ans-1==idx) {
        cout<<"Correct\n";
    }
    else {
        cout<<"Incorrect\n";
    }
}

vector<pair<string,string>> favouriteList;
vector<pair<string,string>> historyList;

extern string historyPath;
extern string favouritePath;

void addHistory(pair<string,string> &cur) {
    historyList.push_back(cur);
}

void favourite(pair<string,string> &cur) {
    favouriteList.push_back(cur);
}

void saveHistory() {
    ofstream out;
    out.open(historyPath);
    for (int i=0;i<historyList.size();i++) {
        out<<historyList[i].first<<'\n'<<historyList[i].second<<'\n';
        out<<separator<<'\n';
    }
    out.close();
}

void loadHistory() {
    ifstream in;
    in.open(historyPath);
    string s1,s2;
    while (getline(in,s1)) {
        string tmp;
        s2="";
        while (true) {
            getline(in,tmp);
            if (tmp!=separator) {
                if (s2=="") s2=tmp;
                else s2+="\n"+tmp;
            }
            else break;
        }
        //cout<<s1<<' '<<s2<<'\n';
        historyList.push_back({s1,s2});
    }
    in.close();
}

void saveFav() {
    ofstream out;
    out.open(favouritePath);
    for (int i=0;i<favouriteList.size();i++) {
        out<<favouriteList[i].first<<'\n'<<favouriteList[i].second<<'\n';
        out<<separator<<'\n';
    }
    out.close();
}

void loadFav() {
    ifstream in;
    in.open(favouritePath);
    string s1,s2;
    while (getline(in,s1)) {
        string tmp;
        s2="";
        while (true) {
            getline(in,tmp);
            if (tmp!=separator) {
                if (s2=="") s2=tmp;
                else s2+="\n"+tmp;
            }
            else break;
        }
        //cout<<s1<<' '<<s2<<'\n';
        favouriteList.push_back({s1,s2});
    }
    in.close();
}

void deleteWord(TST& data1,string &cur) {
    TSTNode* tmp=data1.get(cur);
    if (tmp) tmp->val=0;
}

string standardize(string x,int y,int z) {
    int cnt1,cnt2;
    string kq="";
    for (int i=0;i<x.length();i++) {
        cnt1++;
        if (x[i]=='\n') {
            cnt2++;
        }
        kq+=x[i];
        if (cnt1>=y||cnt2>=z) {
            break;
        }
    }
    return kq;
}

int getsize(int startPath) {
    int kq;
    ifstream in;
    //cout<<"databank/"+intToString(startPath)+"/maxslot.txt"<<'\n';
    in.open("databank/"+intToString(startPath)+"/maxslot.txt");
    in>>kq;
    in.close();
    return kq;
}

void searchDefThread(int startPath,int l,int r,vector<string>& val,int prio,atomic<bool>& isFound,atomic<int>& res) {
    int m=val.size();
    bool ok[1000];
    for (int i=0;i<m;i++) ok[i]=false;
    for (int i=l;i<=r;++i) {
        ifstream in;
        int kq=0;
        string s;
        in.open("databank/"+intToString(startPath)+'/'+intToString(i)+".txt");
        while (in>>s) {
            for (int j=0;j<m;++j) {
                    if (ok[j]) continue;
                if (s==val[j]) {
                    ok[j]=true;
                    //cout<<s<<'\n';
                    kq++;
                    if (kq>=prio) {
                        in.close();
                        isFound=true;
                        res=i;
                        return;
                    }
                    break;
                }
            }
            //cout<<i;
        }
        in.close();
    }
    return ;
}

int searchDef(int startPath,int startPos,vector<string>& val,int prio) {
    int n=getsize(startPath);
    int m=val.size();
    //cout<<n<<'\n';
    int numThreads = std::thread::hardware_concurrency();
    int BlcSizeThreads=(n-startPos+numThreads-1)/numThreads;
    cout<<numThreads<<'\n';

    std::vector<std::thread> threads;
    std::atomic<bool> found(false);
    std::atomic<int> result(-1);

    for (int i = 0; i < numThreads; i++) {
        int pl = startPos+1+(i-1)*BlcSizeThreads;
        int pr = startPos+i*BlcSizeThreads;
        if (i+1==numThreads) pr=n;

        threads.emplace_back(searchDefThread, startPath, pl, pr, ref(val),prio,ref(found),ref(result));
    }
    for (auto& thread : threads) {
        thread.join();
    }

    if (found) {
        return result;
    } else {
        return -1;
    }
    /*
    for (int i=startPos+1;i<=n;++i) {
        ifstream in;
        int kq=0;
        string s;
        in.open("databank/"+intToString(startPath)+'/'+intToString(i)+".txt");
        while (in>>s) {
            for (int j=0;j<m;++j) {
                if (s==val[j]) {
                    //cout<<s<<'\n';
                    kq++;
                    if (kq>=prio) {
                        in.close();
                        return i;
                    }
                    break;
                }
            }
            cout<<i;
        }
        in.close();
    }
    return -1;
    */
}


void transformDef(string& s,vector<string>& targ) {
    ofstream in;
    in.open("coreData/medium.txt");
    in<<s;
    in.close();
    ifstream out;
    targ.clear();
    string tmp;
    out.open("coreData/medium.txt");
    while (out>>tmp) {
        targ.push_back(tmp);
    }
    out.close();
}
