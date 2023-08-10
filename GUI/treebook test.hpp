//
//  treebook test.hpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 31/07/2023.
//

#ifndef treebook_test_hpp
#define treebook_test_hpp

#include <stdio.h>
#include "wx/wx.h"
#include "wx/aui/auibook.h"
#include "wx/wxprec.h"
#include <wx/combobox.h>
#include "wx/imaglist.h"
#include "wx/artprov.h"
#include "wx/cshelp.h"
#include "wx/utils.h"
#include <wx/srchctrl.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/grid.h>

class MyFrame : public wxFrame
{
public:
    MyFrame();
    virtual ~MyFrame();
    void OnBookCtrl(wxBookCtrlBaseEvent& event);
    void OnShowImages(wxCommandEvent& event);

    void OnAuiNotebook(wxAuiNotebookEvent& event) { OnBookCtrl(event); }
    // void writeToLogPanel(const wxString& message);


    wxBookCtrlBase *GetCurrentBook() const { return m_bookCtrl; }

private:

    void RecreateBook();
    wxPanel *CreateNewPage() const;
    void AddFlagStrIfFlagPresent(wxString & flagStr, long flags, long flag, const wxString& flagName) const;

    // Sample setup
    enum BookType
    {
        Type_AuiNotebook,
        Type_Max
    } m_type;

    // Controls

    wxPanel *m_panel; // Panel containing notebook and other controls
    wxBookCtrlBase *m_bookCtrl;


    // Log window
    wxTextCtrl *m_text;
 // USE_LOG
    bool m_chkShowImages;
    wxBoxSizer *m_sizerFrame;

    wxBookCtrlBase::Images m_images;

    wxTextCtrl* m_inputTextCtrl;
    wxGrid* m_grid;


    wxDECLARE_EVENT_TABLE();
};

enum ID_COMMANDS
{
    // these should be in the same order as Type_XXX elements above
    ID_BOOK_AUINOTEBOOK,
    ID_BOOK_MAX,
};

//insert page
#define DICTIONARY        "Dictionary"

//add new word
#define ADD_NEW_WORD          "Add new word"

//favourite list
#define FAVOURITE_LIST                  "Favourite list"

//game
#define GAME                  "Game"
#endif /* treebook_test_hpp */
