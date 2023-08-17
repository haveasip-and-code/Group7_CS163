#pragma once
#include "handling.h"

wxString stringToWxString(string tmp) {
    wxString mystring(tmp.c_str(), wxConvUTF8);
    return mystring;
}
