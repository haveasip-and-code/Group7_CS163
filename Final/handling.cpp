#pragma once
#include "handling.h"

string buffer="coreData/medium.txt";

wxString stringToWxString(string tmp) {
    wxString mystring(tmp.c_str(), wxConvUTF8);
    return mystring;
}

string wxStringToString(wxString tmp) {
    ofstream bufferOut;
    bufferOut.open(buffer);
    bufferOut<<tmp<<'\n';
    bufferOut.close();
    string kq,tmp2;
    ifstream bufferIn;
    bufferIn.open(buffer);
    while (getline(bufferIn,tmp2)) {
        if (kq=="") kq+=tmp2;
        else kq+="\n"+tmp2;
    }
    bufferIn.close();
    return kq;
}

wstring wxStringTowString(wxString tmp) {

}

