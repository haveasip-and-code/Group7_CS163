#pragma once
#include <bits/stdc++.h>
#include "trie.h"
#include "debugCore.h"

int charcode(char c) {
    if (c=='\'') return 27;
    if (c=='_') return 26;
    return c-'a';
}

trieNode* trieNode::insert(string &cur,int idx) {
    if (idx==cur.length()) {
        return this;
    }
    if (!arr[charcode(cur[idx])]) {
        arr[charcode(cur[idx])]=new trieNode;
    }
    return arr[charcode(cur[idx])]->insert(cur,idx+1);
}

trieNode* trieNode::insert(string &cur) {
    return insert(cur,0);
}

void trieNode::saveToFile(ofstream &out) {
    for (int ii=0;ii<trieNodeConst::tSize;ii++) {
        if (arr[ii]) {
            out<<arr[ii]->storagelocation<<' ';
        }
        else {
            out<<-1<<' ';
        }
    }
    out<<'\n';
    for (int ii=0;ii<trieNodeConst::tSize;ii++) {
        if (arr[ii]) {
            arr[ii]->saveToFile(out);
        }
    }
}

void trieNode::saveToFile(string path) {
    ofstream tmpStream;
    tmpStream.open(path+"/structure.txt");
    saveToFile(tmpStream);
    tmpStream.close();
}

void trieNode::loadFromFile(ifstream &in) {
    for (int ii=0;ii<trieNodeConst::tSize;ii++) {
        int tmp;
        in>>tmp;
        if (tmp!=-1) {
            arr[ii]=new trieNode;
            arr[ii]->storagelocation=tmp;
        }
    }
    for (int ii=0;ii<trieNodeConst::tSize;ii++) {
        if (arr[ii]) {
            arr[ii]->loadFromFile(in);
        }
    }
}

void trieNode::loadFromFile(string path) {
    ifstream tmpStream;
    tmpStream.open(path+"/structure.txt");
    debug("Load from: "+path+"/structure.txt");
    loadFromFile(tmpStream);
    tmpStream.close();
}

trieNode* trieNode::get(string &cur,int idx) {
    if (idx==cur.length()) {
        return this;
    }
    if (!arr[charcode(cur[idx])]) {
        return nullptr;
    }
    return arr[charcode(cur[idx])]->get(cur,idx+1);
}

trieNode* trieNode::get(string &cur) {
    return get(cur,0);
}
