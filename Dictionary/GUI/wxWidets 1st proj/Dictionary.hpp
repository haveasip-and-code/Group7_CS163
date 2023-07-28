//
//  Dictionary.hpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 26/07/2023.
//

#ifndef Dictionary_hpp
#define Dictionary_hpp

#include <stdio.h>
#include "wx/wx.h"

class DictionaryWin : public wxFrame
{
public:
    DictionaryWin(const wxString& title);
    
    // Destructor
    virtual ~DictionaryWin();
 
private:
    wxPanel* searchTop;
    wxPanel* meaningLeft;
    wxPanel* toolRight;
    
};
#endif /* Dictionary_hpp */
