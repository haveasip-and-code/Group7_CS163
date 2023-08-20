#pragma once
#include <bits/stdc++.h>
#include "wordEncoder.h"
#include "debugCore.h"

int wordTransformer::size() {
    return sizeT;
}

void wordTransformer::clear() {
    sizeT=0;
    transfromer.clear();
}

int wordTransformer::encode(string &s) {
     TSTNode* pHead=transfromer.insert(s);
     sizeT++;
     pHead->val=sizeT;
     return sizeT;
}
