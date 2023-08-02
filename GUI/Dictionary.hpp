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
#include <wx/srchctrl.h>
#include <wx/tglbtn.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include "wx/custombgwin.h"
#include <wx/image.h>
#include <wx/textctrl.h>


class DictionaryWin : public wxFrame
{
public:
    DictionaryWin(const wxString& title);
    
    // Destructor
    virtual ~DictionaryWin();
 
private:
    wxPanel* function_panel;
    wxPanel* word_panel;
    
    wxBitmap main_ig;
    wxBitmapToggleButton* m_main;
    
    wxBitmap add_ig;
    wxBitmapToggleButton* m_add;
    
    wxBitmap favourite_ig;
    wxBitmapToggleButton* m_favourite;
    
    wxBitmap game_ig;
    wxBitmapToggleButton* m_game;
    
    wxBitmap reset_ig;
    wxBitmapButton* m_reset;
    
    wxBitmap logout_ig;
    wxBitmapButton* m_logout;
    
private:
    void OnMainClick(wxCommandEvent& event);
    void OnAddClick(wxCommandEvent& event);
    void OnFavouriteClick(wxCommandEvent& event);
    void OnGameClick(wxCommandEvent& event);
    void OnResetClick(wxCommandEvent& event);
    void OnLogoutClick(wxCommandEvent& event);
    
private:
    DECLARE_EVENT_TABLE()
 
    enum
    {
        BUTTON_main = wxID_HIGHEST + 1,
        BUTTON_add = wxID_HIGHEST + 2,
        BUTTON_favourite = wxID_HIGHEST + 3,
        BUTTON_game = wxID_HIGHEST + 4,
        BUTTON_reset = wxID_HIGHEST + 5,
        BUTTON_logout = wxID_HIGHEST +6
    };
};
#endif /* Dictionary_hpp */
