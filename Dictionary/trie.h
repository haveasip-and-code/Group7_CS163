#include<bits/stdc++.h>

using namespace std;

#ifndef TRIE_H
#define TRIE_H

namespace trieNodeConst{
    const int tSize=30;
}

struct trieNode{
    trieNode* arr[trieNodeConst::tSize]; //0->25: 26 character of English
                       //26: Mark UpperCase with _, example A=_a
                       //27: '

    int storagelocation;

    trieNode() {
        storagelocation=0;
        for (int ii=0;ii<30;ii++) {
            arr[ii]=nullptr;
        }
    }

    trieNode* get(string &cur,int idx);
    trieNode* get(string &cur);

    trieNode* insert(string &cur);
    trieNode* insert(string &cur,int idx);

    void loadFromFile(ifstream &in);
    void loadFromFile(string path);
    void saveToFile(ofstream &out);
    void saveToFile(string path);
};

int charcode(char c);

#endif //TRIE_H



