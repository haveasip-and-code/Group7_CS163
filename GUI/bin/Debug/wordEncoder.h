#include<bits/stdc++.h>
#include"ternarySearchTree.h"

using namespace std;

#ifndef WORDENCODER_H
#define WORDENCODER_H

struct wordTransformer {
    TST transfromer;

    string storagePath;
    int sizeT;

    wordTransformer() {
        transfromer=TST();
        storagePath="";
    }

    wordTransformer(string& path) {
        transfromer=TST();
        storagePath=path;
    }

    int size();
    void clear();

    int encode(string& s);
    string decode(int x);
};

#endif //WORDENCODER_H



