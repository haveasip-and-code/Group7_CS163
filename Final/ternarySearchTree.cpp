#pragma once
#include <bits/stdc++.h>
#include "ternarySearchTree.h"
#include "debugCore.h"

int cnt;

TSTNode* TSTNode::insert(string &cur,int idx) {
    if (idx==cur.length()) {
        return this;
    }
    if (cur[idx]>key) {
        if (!hi) {
            hi=new TSTNode(cur[idx]);
        }
        return hi->insert(cur,idx);
    }
    else if (cur[idx]<key) {
        if (!lo) {
            lo=new TSTNode(cur[idx]);
        }
        return lo->insert(cur,idx);
    }
    else {
        if (!mid) {
            mid=new TSTNode(cur[idx]);
        }
        return mid->insert(cur,idx+1);
    }
}

TSTNode* TSTNode::insert(string &cur) {
    return insert(cur,0);
}

void TSTNode::saveToFile(ofstream &out) {
    out<<val<<' ';
    if (lo) {
        out<<1;
    }
    else {
        out<<0;
    }
    if (mid) {
        out<<1;
    }
    else {
        out<<0;
    }
    if (hi) {
        out<<1;
    }
    else {
        out<<0;
    }
    out<<' ';
    if (lo) out<<lo->key<<' ';
    if (mid) out<<mid->key<<' ';
    if (hi) out<<hi->key<<' ';
    out<<'\n';
    if (lo) {
        lo->saveToFile(out);
    }
    if (mid) {
        mid->saveToFile(out);
    }
    if (hi) {
        hi->saveToFile(out);
    }
}

void TSTNode::saveToFile(string path) {
    ofstream tmpStream;
    tmpStream.open(path+"/TST.txt");
    saveToFile(tmpStream);
    debug("Save to file "+path+"/TST.txt");
    tmpStream.close();
}

void TSTNode::loadFromFile(ifstream &in) {
    in>>val;
    string state;
    in>>state;
    char tmp;
    //cnt++;
    //cout<<cnt<<' '<<state<<'\n';
    if (state[0]=='1') {
        in>>tmp;
        lo=new TSTNode(tmp);
    }
    else {
        lo=nullptr;
    }
    if (state[1]=='1') {
        in>>tmp;
        mid=new TSTNode(tmp);
    }
    else {
        mid=nullptr;
    }
    if (state[2]=='1') {
        in>>tmp;
        hi=new TSTNode(tmp);
    }
    else {
        hi=nullptr;
    }
    if (lo) {
        lo->loadFromFile(in);
    }
    if (mid) {
        mid->loadFromFile(in);
    }
    if (hi) {
        hi->loadFromFile(in);
    }
}

void TSTNode::loadFromFile(string path) {
    ifstream tmpStream;
    debug(path);
    tmpStream.open(path+"/TST.txt");
    debug("Load from: "+path+"/TST.txt");
    loadFromFile(tmpStream);
    cout<<"-----------------\n";
    tmpStream.close();
}

TSTNode* TSTNode::get(string &cur,int idx) {
    if (idx==cur.length()) {
        return this;
    }
    if (cur[idx]<key) {
        if (lo) {
            return lo->get(cur,idx);
        }
        else {
            return nullptr;
        }
    }
    else if (cur[idx]>key) {
        if (hi) {
            return hi->get(cur,idx);
        }
        else {
            return nullptr;
        }
    }
    else {
        if (mid) {
            return mid->get(cur,idx+1);
        }
        else {
            return nullptr;
        }
    }
}

TSTNode* TSTNode::get(string &cur) {
    return get(cur,0);
    //cout<<'\n';
}

void TSTNode::clear() {
    if (lo) {
        lo->clear();
    }
    if (mid) {
        mid->clear();
    }
    if (hi) {
        hi->clear();
    }
    delete this;
}

void TST::clear() {
    if (pRoot) {
        pRoot->clear();
    }
}

TSTNode* TST::insert(string& cur) {
    return pRoot->insert(cur);
}

TSTNode* TST::insert(string& cur,int idx) {
    return pRoot->insert(cur,idx);
}

TSTNode* TST::get(string& cur) {
    return pRoot->get(cur);
}

TSTNode* TST::get(string& cur,int idx) {
    return pRoot->get(cur,idx);
}

void TST::loadFromFile(ifstream& in) {
    pRoot->loadFromFile(in);
}

void TST::loadFromFile(string path) {
    debug(path);
    //cout<<path;
    pRoot->loadFromFile(path);
}

void TST::saveToFile(ofstream& out) {
    if (!pRoot) {
        pRoot=new TSTNode();
    }
    pRoot->saveToFile(out);
}

void TST::saveToFile(string path) {
    if (!pRoot) {
        pRoot=new TSTNode();
    }
    pRoot->saveToFile(path);
}
