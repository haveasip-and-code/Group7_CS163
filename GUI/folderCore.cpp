#pragma once
#include <direct.h>
#include "folderCore.h"
#include "debugCore.h"

int createFolder(string name) {
    int status = mkdir((name).c_str());
    if ((status < 0)) {
        if (errno!=EEXIST) {
            debug("Folder \""+name+"\" was not created.");
            return 2;
        }
        else {
            debug("Folder \""+name+"\"already exist");
            return 1;
        }
    }
    else {
        debug("Folder \""+name+"\" was created.");
        return 0;
    }
}
