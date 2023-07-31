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
#include <wx/treebook.h>
#include "wx/wxprec.h"
#include "wx/wx.h"

#include "wx/imaglist.h"
#include "wx/artprov.h"
#include "wx/cshelp.h"
#include "wx/utils.h"

class MyFrame : public wxFrame
{
public:
    MyFrame();
    virtual ~MyFrame();
    void OnBookCtrl(wxBookCtrlBaseEvent& event);
    void OnShowImages(wxCommandEvent& event);
#if wxUSE_TREEBOOK
    void OnTreebook(wxTreebookEvent& event) { OnBookCtrl(event); }
#endif

    wxBookCtrlBase *GetCurrentBook() const { return m_bookCtrl; }

private:
    wxLog *m_logTargetOld;

    void RecreateBook();
    wxPanel *CreateNewPage() const;
    void AddFlagStrIfFlagPresent(wxString & flagStr, long flags, long flag, const wxString& flagName) const;

    // Sample setup
    enum BookType
    {
        Type_Treebook,
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

    wxDECLARE_EVENT_TABLE();
};

enum ID_COMMANDS
{
    // these should be in the same order as Type_XXX elements above
    ID_BOOK_TREEBOOK,
    ID_BOOK_MAX,

#if wxUSE_HELP
    ID_CONTEXT_HELP,
#endif // wxUSE_HELP
    ID_HITTEST
};


#define I_WAS_INSERTED_PAGE_NAME        "Inserted"
#define RADIOBUTTONS_PAGE_NAME          "Radiobuttons"
#define VETO_PAGE_NAME                  "Veto"
#define TEXT_PAGE_NAME                  "Text"
#endif /* treebook_test_hpp */
