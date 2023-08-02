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
    
    panel->SetBackgroundColour(wxColour(248, 247, 245));
    ::wxInitAllImageHandlers();
    
    
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxComboBox* m_combo = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                         0, NULL, wxCB_DROPDOWN | wxCB_READONLY);
    m_combo->SetHelpText("Lookup Mode");
    
    // Add items to the combo box
    m_combo->Append("Word - Definition");
    m_combo->Append("Definition  - Word");
    
    // Bind the selection event to an event handler
    m_combo->Bind(wxEVT_COMBOBOX,[=](wxCommandEvent& event)
                  {
        wxString selectedText = m_combo->GetValue();
        wxLogMessage("Selected: %s", selectedText);
    });
    
    
    wxSearchCtrl* searchBar = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, 20), wxTE_PROCESS_ENTER|wxTE_LEFT);
    searchBar->ShowCancelButton(true);
    
    wxBitmap search_ig = wxBitmap("add_clicked.png", wxBITMAP_TYPE_ANY);
    
    wxBitmapButton* searchButton = new wxBitmapButton(panel, wxID_ANY, search_ig, wxDefaultPosition, wxSize(30,30));
    searchButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        wxString searchText = searchBar->GetValue();
        wxMessageBox("Searching for: " + searchText);
    });
    
    sizer->Add(m_combo, 0, wxLEFT, 30);
    sizer->Add(searchBar, 0);
    sizer->Add(searchButton,0, wxLEFT, 5);
    
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxTextCtrl* word = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTER);
    word->SetHelpText("Word");
    
    wxTextCtrl* pronounciation = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTER);
    pronounciation->SetHelpText("Pronounciation");
    sizer2->Add(word,0);
    sizer2->Add(pronounciation,0);
    
    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxBitmapButton* m_edit = new wxBitmapButton(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_HELP), wxDefaultPosition, wxSize(30,30));
    m_edit->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                 {
        wxDialog edit_dlg(panel, wxID_ANY, "Edit meaning");
        
        wxBoxSizer* change = new wxBoxSizer(wxVERTICAL);
        wxTextCtrl* word_change = new wxTextCtrl(&edit_dlg, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(200,-1), wxTE_READONLY|wxTE_CENTER);
        word_change->SetHelpText("Your word is ....");
        
        wxTextCtrl* meaningEntry = new wxTextCtrl(&edit_dlg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200,-1));
        meaningEntry->SetHint("Enter your new definition here");
        
        wxButton* getMeaning = new wxButton(&edit_dlg, wxID_OK, "Save");
        
        change->Add(word_change,0,wxBOTTOM|wxTOP, 5);
        change->Add(meaningEntry,0, wxBOTTOM,10);
        change->Add(getMeaning,0, wxBOTTOM, 10);
        edit_dlg.SetSizerAndFit(change);
        int result = edit_dlg.ShowModal();
        
        // Show the dialog and wait for user input
        if (result == wxID_OK)
        {
            wxString changing = meaningEntry->GetValue();
            if (!changing.empty()) {
                
                wxMessageBox(wxEmptyString, "Changes saved", wxOK | wxICON_INFORMATION, panel);
            }
        }
        
    });
    sizer3->Add(m_edit,0);
    
    panel->SetSizer(sizer);
    
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
    
    parent->SetSize(wxSize(100,400));
    wxWindow *page = CreateRadioButtonsPage(parent);
    
    parent->AddPage( page, ADD_NEW_WORD, false, GetIconIndex(parent) );
    
    page = CreateVetoPage(parent);
    parent->AddPage( page, FAVOURITE_LIST, false, GetIconIndex(parent) );
    
    page = CreateFullPageText(parent);
    parent->AddPage( page, GAME, false, GetIconIndex(parent) );
    
    page = CreateInsertPage(parent);
    parent->InsertPage( 0, page, DICTIONARY, false, GetIconIndex(parent) );
    
    parent->SetSelection(1);
}

wxWindow *CreatePage(wxBookCtrlBase *parent, const wxString&pageName)
{
    
    if ( pageName == DICTIONARY )
        return CreateInsertPage(parent);
    
    if ( pageName == FAVOURITE_LIST )
        return CreateVetoPage(parent);
    
    if ( pageName == ADD_NEW_WORD )
        return CreateRadioButtonsPage(parent);
    
    if ( pageName == GAME )
        return CreateFullPageText(parent);
    
    wxFAIL_MSG( "unknown page name" );
    
    return NULL;
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_ANY, MyFrame::OnAuiNotebook)
EVT_AUINOTEBOOK_PAGE_CHANGING(wxID_ANY, MyFrame::OnAuiNotebook)
wxEND_EVENT_TABLE()

MyFrame::MyFrame()
: wxFrame(NULL, wxID_ANY, wxString("wxWidgets book controls sample"),wxPoint(wxID_ANY, wxID_ANY), wxSize(1200, 680),
          wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    
    m_type = Type_AuiNotebook;
    this->SetBackgroundColour(wxColour(73,86,111));
    m_panel    = NULL;
    m_bookCtrl = NULL;
    m_chkShowImages = true;
    
    ::wxInitAllImageHandlers();
    wxBitmap add_ig("add_clicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap find_ig("dict_clicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap icon("dict_unclicked.png", wxBITMAP_TYPE_ANY);
    
    m_images.push_back(add_ig);
    m_images.push_back(icon);
    m_images.push_back(icon);
    m_images.push_back(find_ig);
    // m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_PLUS, wxART_OTHER, imageSize));
    // m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_TICK_MARK, wxART_OTHER, imageSize));
    // m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_NEW, wxART_OTHER, imageSize));
    // m_images.push_back(wxArtProvider::GetBitmapBundle(wxART_FIND, wxART_OTHER, imageSize));
    
    m_panel = new wxPanel(this);
    
    m_text = new wxTextCtrl(m_panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize,wxTE_MULTILINE | wxTE_READONLY);
    
    m_sizerFrame = new wxBoxSizer(wxVERTICAL);
    m_sizerFrame->Add(m_text, 1, wxEXPAND);
    
    RecreateBook();
    
    m_panel->SetSizer(m_sizerFrame);
    m_panel->Layout();
    
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_panel, wxSizerFlags(1).Expand());
    this->SetSizer(sizer);
}

MyFrame::~MyFrame()
{
}

#if wxUSE_AUI
#define CASE_AUINOTEBOOK(x) case Type_AuiNotebook: x; break;
#else
#define CASE_AUINOTEBOOK(x)
#endif

#define DISPATCH_ON_TYPE(before, aui, after)\
switch ( m_type )                                         \
{                                                      \
CASE_AUINOTEBOOK(before aui after) \
\
\
default:                                \
wxFAIL_MSG( "unknown book control type" );\
}

void MyFrame::RecreateBook()
{
    wxBookCtrlBase *oldBook = m_bookCtrl;
    
    m_bookCtrl = NULL;
    
    DISPATCH_ON_TYPE(m_bookCtrl = new, wxAuiNotebook,
                     (m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_LEFT));
    
    if ( !m_bookCtrl )
        return;
    
    m_bookCtrl->Hide();
    if ( m_chkShowImages )
    {
        m_bookCtrl->SetImages(m_images);
    }
    
    if ( oldBook )
    {
        
        const int count = oldBook->GetPageCount();
        for ( int n = 0; n < count; n++ )
        {
            const int image = GetIconIndex(m_bookCtrl);
            const wxString str = oldBook->GetPageText(n);
            
            wxWindow *page = CreatePage(m_bookCtrl, str);
            
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
        
        wxEVT_AUINOTEBOOK_PAGE_CHANGED,
        wxEVT_AUINOTEBOOK_PAGE_CHANGING,
        "wxAuiNotebook"
    }
    ;
    // wxUSE_TREEBOOK
    
    wxString nameEvent,
    nameControl,
    veto;
    const wxEventType eventType = event.GetEventType();
    
    // NB: can't use wxStaticCast here as wxBookCtrlBase is not in
    //     wxRTTI
    
    for ( size_t n = 0; n < WXSIZEOF(events); n++ )
    {
        const EventInfo& ei = events[n];
        if ( eventType == ei.typeChanged )
        {
            nameEvent = "Changed";
        }
        else if ( eventType == ei.typeChanging )
        {
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
}


