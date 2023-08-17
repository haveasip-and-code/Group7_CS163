#pragma once
#include "handling.h"

wxString stringToWxString(string tmp) {
    wxString mystring(tmp.c_str(), wxConvUTF8);
    return mystring;
}

string wxStringToString(wxString tmp) {
    string kq=string(tmp.mb_str());
    return kq;
}
