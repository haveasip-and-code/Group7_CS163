#pragma once
#include <bits/stdc++.h>
#include "ternarySearchTree.h"
#include "debugCore.h"

int cnt;

TSTNode* nullTSTNode=new TSTNode();


TSTNode* TSTNode::insert(string cur,int idx) {
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

TSTNode* TSTNode::insert(string cur) {
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

TSTNode* TSTNode::get(string cur,int idx) {
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

TSTNode* TSTNode::getAlwaysDFS() {
    //cout<<this->key<<'\n';
    if (this->val!=0) return this;
    TSTNode* kq=nullTSTNode;
    if (mid) {
        kq=mid->getAlwaysDFS();
        if (kq->val!=0) return kq;
    }
    if (lo) {
        kq=lo->getAlwaysDFS();
        if (kq->val!=0) return kq;
    }
    if (hi) {
        kq=hi->getAlwaysDFS();
        if (kq->val!=0) return kq;
    }
}

TSTNode* TSTNode::getAlways(string cur,int idx) {
    TSTNode* kq=nullTSTNode;
    //cout<<cur<<' '<<this->key<<'\n';
    if (idx==cur.length()) {
        if (this->val!=0) {
            return this;
        }
        else {
            return this->getAlwaysDFS();
        }
    }
    if (cur[idx]<key) {
        if (lo) {
            kq=lo->getAlways(cur,idx);
        }
        else {
            kq=nullTSTNode;
        }
    }
    else if (cur[idx]>key) {
        if (hi) {
            kq=hi->getAlways(cur,idx);
        }
        else {
            kq=nullTSTNode;
        }
    }
    else {
        if (mid) {
            //cout<<"->\n";
            kq=mid->getAlways(cur,idx+1);
        }
        else {
            kq=nullTSTNode;
        }
    }
    if (kq) if (kq->val!=0) return kq;
    if (lo) {
        kq=lo->getAlways(cur,idx);
        //if (kq->val!=0) kq=lo->getAlways(cur,idx);
        if (kq->val!=0) return kq;
    }
    if (hi) {
        kq=hi->getAlways(cur,idx);
        //if (kq->val!=0) kq=hi->getAlways(cur,idx);
        if (kq->val!=0) return kq;

    }
    if (mid) {
        kq=mid->getAlways(cur,idx);
        //if (kq->val!=0) kq=mid->getAlways(cur,idx);
        if (kq->val!=0) return kq;
    }
    return this->getAlwaysDFS();
}

TSTNode* TSTNode::get(string cur) {
    return get(cur,0);
    //cout<<'\n';
}


TSTNode* TSTNode::getAlways(string cur) {
    return getAlways(cur,0);
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

string encrypt(string cur) {
    int m=cur.size();
    for (int i=0;i<m;i++) {
        if (cur[i]==' ') cur[i]='_';
    }
    return cur;
}

TSTNode* TST::insert(string cur) {
    cur=encrypt(cur);
    return pRoot->insert(cur);
}

TSTNode* TST::insert(string cur,int idx) {
    cur=encrypt(cur);
    return pRoot->insert(cur,idx);
}

TSTNode* TST::get(string cur) {
    cur=encrypt(cur);
    return pRoot->get(cur);
}

TSTNode* TST::get(string cur,int idx) {
    cur=encrypt(cur);
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
