/*#pragma once
#include "folderCore.h"
#include "storage.h"

void Container::save() {
    createFolder(path+"/"+name);
    indexer.saveToFile(path+"/"+name);
}

void Container::load() {
    indexer.loadFromFile(path+"/"+name);
}

int Container::insert(string key) {
    TSTNode* tmp=indexer.insert(key);
    int pos=tmp->val;
    return pos;
}

void Container::delete(string key) {
    TSTNode* tmp=indexer.get(key);
    int pos=tmp->val;
    deleteData(path+"/"+name,pos);
}

void Container::setPath(string _path) {
    path=_path;
}

void Container::setName(string _name) {
    name=_name;
}
*/
