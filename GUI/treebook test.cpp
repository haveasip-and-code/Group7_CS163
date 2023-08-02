//
//  treebook test.cpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 31/07/2023.
//

#include "treebook test.hpp"

wxPanel *CreateInsertPage(wxBookCtrlBase *parent)
{
    wxPanel *panel = new wxPanel(parent);

#if wxUSE_HELP
    panel->SetHelpText("Maroon panel");
#endif

    panel->SetBackgroundColour( wxColour( "MAROON" ) );
    (void) new wxStaticText( panel, wxID_ANY,
                             "This page has been inserted, not added.",
                             wxPoint(10, 10) );

    return panel;
}
wxPanel *CreateRadioButtonsPage(wxBookCtrlBase *parent)
{
    wxPanel *panel = new wxPanel(parent);

#if wxUSE_HELP
    panel->SetHelpText("Panel with some Radio Buttons");
#endif

    wxString animals[] =
      { "Fox", "Hare", "Rabbit",
        "Sabre-toothed tiger", "T Rex" };

    wxRadioBox *radiobox1 = new wxRadioBox(panel, wxID_ANY, "Choose one",
        wxDefaultPosition, wxDefaultSize, 5, animals, 2, wxRA_SPECIFY_ROWS);

    wxString computers[] =
      { "Amiga", "Commodore 64", "PET",
        "Another" };

    wxRadioBox *radiobox2 = new wxRadioBox(panel, wxID_ANY,
        "Choose your favourite", wxDefaultPosition, wxDefaultSize,
        4, computers, 0, wxRA_SPECIFY_COLS);

    wxBoxSizer *sizerPanel = new wxBoxSizer(wxVERTICAL);
    sizerPanel->Add(radiobox1, 2, wxEXPAND);
    sizerPanel->Add(radiobox2, 1, wxEXPAND);
    panel->SetSizer(sizerPanel);

    return panel;
}

wxPanel *CreateVetoPage(wxBookCtrlBase *parent)
{
    wxPanel *panel = new wxPanel(parent);

#if wxUSE_HELP
    panel->SetHelpText("An empty panel");
#endif

    (void) new wxStaticText( panel, wxID_ANY,
                             "This page intentionally left blank",
                             wxPoint(10, 10) );

    return panel;
}

wxWindow *CreateFullPageText(wxBookCtrlBase *parent)
{
    wxTextCtrl *text = new wxTextCtrl(parent, wxID_ANY, "Full page text",
                                      wxDefaultPosition, wxDefaultSize,
                                      wxTE_MULTILINE);

#if wxUSE_HELP
    text->SetHelpText("Page consisting of just a text control");
#endif

    return text;
}

int GetIconIndex(wxBookCtrlBase* bookCtrl)
{
    if (bookCtrl)
    {
       const int nImages = bookCtrl->GetImageCount();
       if (nImages > 0)
       {
           return bookCtrl->GetPageCount() % nImages;
       }
    }

    return -1;
}

void CreateInitialPages(wxBookCtrlBase *parent)
{
    // Create and add some panels to the notebook

    wxWindow *page = CreateRadioButtonsPage(parent);
    parent->AddPage( page, RADIOBUTTONS_PAGE_NAME, false, GetIconIndex(parent) );

    page = CreateVetoPage(parent);
    parent->AddPage( page, VETO_PAGE_NAME, false, GetIconIndex(parent) );

    page = CreateFullPageText(parent);
    parent->AddPage( page, TEXT_PAGE_NAME, false, GetIconIndex(parent) );

    page = CreateInsertPage(parent);
    parent->InsertPage( 0, page, I_WAS_INSERTED_PAGE_NAME, false, GetIconIndex(parent) );

    parent->SetSelection(1);
}

wxWindow *CreatePage(wxBookCtrlBase *parent, const wxString&pageName)
{

    if ( pageName == I_WAS_INSERTED_PAGE_NAME )
        return CreateInsertPage(parent);

    if ( pageName == VETO_PAGE_NAME )
        return CreateVetoPage(parent);

    if ( pageName == RADIOBUTTONS_PAGE_NAME )
        return CreateRadioButtonsPage(parent);

    if ( pageName == TEXT_PAGE_NAME )
        return CreateFullPageText(parent);

    wxFAIL_MSG( "unknown page name" );

    return NULL;
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_TREEBOOK_PAGE_CHANGED(wxID_ANY, MyFrame::OnTreebook)
EVT_TREEBOOK_PAGE_CHANGING(wxID_ANY, MyFrame::OnTreebook)
wxEND_EVENT_TABLE()

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, wxString("wxWidgets book controls sample"))
{
    m_type = Type_Treebook;
    
    m_panel    = NULL;
    m_bookCtrl = NULL;
    
    const wxSize imageSize(32, 32);

    m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_INFORMATION, wxART_OTHER, imageSize));
    m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_QUESTION, wxART_OTHER, imageSize));
    m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_WARNING, wxART_OTHER, imageSize));
    m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_ERROR, wxART_OTHER, imageSize));

    m_panel = new wxPanel(this);
    
    m_text = new wxTextCtrl(m_panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize,wxTE_MULTILINE | wxTE_READONLY);

    m_logTargetOld = wxLog::SetActiveTarget( new wxLogTextCtrl(m_text) );
    
    m_sizerFrame = new wxBoxSizer(wxVERTICAL);
    m_sizerFrame->Add(m_text, 1, wxEXPAND);
    
    RecreateBook();

    m_panel->SetSizer(m_sizerFrame);
    m_panel->Layout();

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_panel, wxSizerFlags(1).Expand());
    SetSizerAndFit(sizer);
}

MyFrame::~MyFrame()
{
#if USE_LOG
    delete wxLog::SetActiveTarget(m_logTargetOld);
#endif // USE_LOG
}

#if wxUSE_TREEBOOK
    #define CASE_TREEBOOK(x) case Type_Treebook: x; break;
#else
    #define CASE_TREEBOOK(x)
#endif

#define DISPATCH_ON_TYPE(before, tb, after)\
switch ( m_type )                                         \
    {                                                      \
        CASE_TREEBOOK(before tb after)\
                            \
                   \
        default:                                \
            wxFAIL_MSG( "unknown book control type" );\
    }

void MyFrame::RecreateBook()
{
    wxBookCtrlBase *oldBook = m_bookCtrl;
    
    m_bookCtrl = NULL;

    DISPATCH_ON_TYPE(m_bookCtrl = new, wxTreebook,
                     (m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_LEFT));

    if ( !m_bookCtrl )
        return;

    m_bookCtrl->Hide();
    if ( m_chkShowImages )
    {
        m_bookCtrl->SetImages(m_images);
    }

    if ( oldBook )
    {
#if wxUSE_TREEBOOK
        // we only need the old treebook if we're recreating another treebook
        wxTreebook *tbkOld = m_type == Type_Treebook
                                ? wxDynamicCast(oldBook, wxTreebook)
                                : NULL;
#endif // wxUSE_TREEBOOK
        const int count = oldBook->GetPageCount();
        for ( int n = 0; n < count; n++ )
        {
            const int image = GetIconIndex(m_bookCtrl);
            const wxString str = oldBook->GetPageText(n);

            wxWindow *page = CreatePage(m_bookCtrl, str);

            // treebook complication: need to account for possible parent page
#if wxUSE_TREEBOOK
            if ( tbkOld )
            {
                const int parent = tbkOld->GetPageParent(n);
                if ( parent != wxNOT_FOUND )
                {
                    wxStaticCast(m_bookCtrl, wxTreebook)->
                        InsertSubPage(parent, page, str, false, image);

                    // skip adding it again below
                    continue;
                }
            }
#endif // wxUSE_TREEBOOK

            m_bookCtrl->AddPage(page, str, false, image);
        }

        const int sel = oldBook->GetSelection();
        if ( sel != wxNOT_FOUND )
            m_bookCtrl->SetSelection(sel);


        m_sizerFrame->Detach(oldBook);
        delete oldBook;
    }
    else // no old book
    {
        CreateInitialPages(m_bookCtrl);
    }

    m_sizerFrame->Insert(0, m_bookCtrl, wxSizerFlags(5).Expand().Border());

    m_sizerFrame->Show(m_bookCtrl);
    m_sizerFrame->Layout();
}

void MyFrame::OnShowImages(wxCommandEvent& event)
{
    m_chkShowImages = event.IsChecked();
    RecreateBook();
    m_sizerFrame->Layout();
}

void MyFrame::OnBookCtrl(wxBookCtrlBaseEvent& event)
{
    static const struct EventInfo
    {
        wxEventType typeChanged,
                    typeChanging;
        const wxString name;
    } events[] =
    {
        
            wxEVT_TREEBOOK_PAGE_CHANGED,
            wxEVT_TREEBOOK_PAGE_CHANGING,
            "wxTreebook"
    }
    ;
 // wxUSE_TREEBOOK
        
        wxString nameEvent,
                 nameControl,
                 veto;
        const wxEventType eventType = event.GetEventType();

        // NB: can't use wxStaticCast here as wxBookCtrlBase is not in
        //     wxRTTI
        const wxBookCtrlBase * const
            book = static_cast<wxBookCtrlBase *>(event.GetEventObject());

        for ( size_t n = 0; n < WXSIZEOF(events); n++ )
        {
            const EventInfo& ei = events[n];
            if ( eventType == ei.typeChanged )
            {
                nameEvent = "Changed";
            }
            else if ( eventType == ei.typeChanging )
            {
                const int idx = event.GetOldSelection();

                if ( idx != wxNOT_FOUND &&
                        book && book->GetPageText(idx) == VETO_PAGE_NAME )
                {
                    if ( wxMessageBox
                         (
                          "Are you sure you want to leave this page?\n"
                          "(This demonstrates veto-ing)",
                          "Notebook sample",
                          wxICON_QUESTION | wxYES_NO,
                          this
                         ) != wxYES )
                    {
                        event.Veto();
                        veto = " (vetoed)";
                    }
                }

                nameEvent = "Changing";
            }
            else // skip end of the loop
            {
                continue;
            }

            nameControl = ei.name;
            break;
        }

        static int s_num = 0;

        wxLogMessage("Event #%d: %s: %s (%d) new sel %d, old %d, current %d%s",
                     ++s_num,
                     nameControl,
                     nameEvent,
                     eventType,
                     event.GetSelection(),
                     event.GetOldSelection(),
                     book->GetSelection(),
                     veto);

    #if USE_LOG
        m_text->SetInsertionPointEnd();
    #endif
    }


