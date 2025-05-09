#include<bits/stdc++.h>

using namespace std;

#ifndef TST_H
#define TST_H

struct TSTNode {
    char key;
    int val;

    TSTNode *lo,*mid,*hi;

    TSTNode (char _key) {
        lo=mid=hi=nullptr;
        key=_key;
        //if (key==' ') key='_';
        val=0;
    }

    TSTNode () {
        lo=mid=hi=nullptr;
        key='a';
        val=0;
    }

    TSTNode* get(string cur,int idx);
    TSTNode* get(string cur);
    TSTNode* getAlways(string cur);
    TSTNode* getAlways(string cur,int idx);
    TSTNode* getAlwaysDFS();

    TSTNode* insert(string cur);
    TSTNode* insert(string cur,int idx);

    void loadFromFile(ifstream &in);
    void loadFromFile(string path);
    void saveToFile(ofstream &out);
    void saveToFile(string path);

    void clear();
};

struct TST {
    TSTNode* pRoot;

    TST() {
        pRoot=new TSTNode();
    }

    TSTNode* get(string cur,int idx);
    TSTNode* get(string cur);
    TSTNode* getAlways(string cur,int idx);
    TSTNode* getAlways(string cur);

    TSTNode* insert(string cur);
    TSTNode* insert(string cur,int idx);

    void loadFromFile(ifstream &in);
    void loadFromFile(string path);
    void saveToFile(ofstream &out);
    void saveToFile(string path);

    void clear();
};

string encrypt(string tmp);

#endif //TST_H



