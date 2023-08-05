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
    
    wxBoxSizer* all_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    
    // wxComboBox* m_combo = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
    //                                      0, NULL, wxCB_READONLY | wxTE_READONLY);
        
    // m_combo->SetHint("Lookup Mode");
    
    // // Add items to the combo box
    // m_combo->Append("Word - Definition");
    // m_combo->Append("Definition  - Word");
    
    // Bind the selection event to an event handler
    // m_combo->Bind(wxEVT_COMBOBOX,[=](wxCommandEvent& event)
    //               {
    //     wxString selectedText = m_combo->GetValue();
    //     wxLogMessage("Selected: %s", selectedText);
    // });

    wxChoice* chooseMode = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    wxArrayString modeChoices;
    modeChoices.Add("By keyword");
    modeChoices.Add("By definition");
    chooseMode->Set(modeChoices);

    chooseMode->Bind(wxEVT_CHOICE, [=](wxCommandEvent& event){
        wxString selectedText = chooseMode->GetStringSelection();
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
    
    sizer->Add(chooseMode, 0, wxLEFT, 30);
    sizer->Add(searchBar, 0);
    sizer->Add(searchButton,0, wxLEFT, 5);
    
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxTextCtrl* word = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(200,-1), wxTE_READONLY|wxTE_CENTER);
    word->SetHint("Word");
    
    wxTextCtrl* pronounciation = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(200,-1), wxTE_READONLY|wxTE_CENTER);
    pronounciation->SetHint("Pronounciation");
    sizer2->Add(word,0, wxLEFT, 30);
    sizer2->Add(pronounciation,0, wxLEFT, 10);
    
    wxBoxSizer* sizer4 = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxBitmapButton* m_edit = new wxBitmapButton(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_HELP), wxDefaultPosition, wxSize(30,30));
    m_edit->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                 {
        wxDialog edit_dlg(panel, wxID_ANY, "Edit meaning");
        
        edit_dlg.SetSize(wxSize(300,200));
        
        wxBoxSizer* change = new wxBoxSizer(wxVERTICAL);
        wxTextCtrl* word_change = new wxTextCtrl(&edit_dlg, wxID_ANY, "Your word is ...",wxDefaultPosition, wxSize(200,-1), wxTE_READONLY|wxTE_CENTER);
        
        wxTextCtrl* meaningEntry = new wxTextCtrl(&edit_dlg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200,-1));
        meaningEntry->SetHint("Enter your new definition here");
        
        wxButton* getMeaning = new wxButton(&edit_dlg, wxID_OK, "Save");
        
        wxBoxSizer* center = new wxBoxSizer(wxVERTICAL);
        
        change->Add(word_change,0,wxBOTTOM|wxTOP, 5);
        change->Add(meaningEntry,0, wxBOTTOM,10);
        change->Add(getMeaning,0, wxALIGN_CENTER|wxBOTTOM, 10);
        
        center->Add(change, 0, wxALIGN_CENTER|wxALL,30);
        
        edit_dlg.SetSizer(center);
        edit_dlg.Center();
        
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
    
    wxBitmapButton* m_favourite = new wxBitmapButton(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_TICK_MARK), wxDefaultPosition, wxSize(30,30));
    
    wxTextCtrl* definition = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(800,300), wxTE_READONLY|wxTE_CENTER);
    definition->SetHint("Definition");
    
    sizer3->Add(m_edit,0);
    sizer3->Add(m_favourite, 0, wxLEFT, 5);
    
    wxBoxSizer* sizer5 = new wxBoxSizer(wxVERTICAL);
    
    // wxComboBox* m_dataset = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
    //                                      0, NULL);
        
    // m_dataset->SetHint("Data Set");
    
    // // Add items to the combo box
    // m_dataset->Append("Eng - Viet");
    // m_dataset->Append("Viet - Eng");
    // m_dataset->Append("Eng - Eng");
    // m_dataset->Append("Emoji - Viet");
    // m_dataset->Append("Emoji - Eng");
    // m_dataset->Append("Eng slangs");
    // m_dataset->Append("Vie slangs");
    
    // // Bind the selection event to an event handler
    // m_dataset->Bind(wxEVT_COMBOBOX,[=](wxCommandEvent& event)
    //               {
    //     wxString selectedText =m_dataset->GetValue();
    //     wxLogMessage("Selected: %s", selectedText);
    // });

    wxChoice* chooseDataSet = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    wxArrayString dataSets;
    dataSets.Add("Eng - Vie");
    dataSets.Add("Vie - Eng");
    dataSets.Add("Eng - Eng");
    dataSets.Add("Emoji - Vie");
    dataSets.Add("Emoji - Eng");
    dataSets.Add("Eng slangs");
    dataSets.Add("Vie slangs");
    chooseDataSet->Set(dataSets);

    chooseDataSet->Bind(wxEVT_CHOICE, [=](wxCommandEvent& event){
        wxString selectedText = chooseDataSet->GetStringSelection();
        wxLogMessage("Selected: %s", selectedText);
    });
    
    wxBitmapButton* m_wordOfDay = new wxBitmapButton(panel, wxID_ANY,wxArtProvider::GetBitmap(wxART_NEW) , wxDefaultPosition, wxSize(30,30));
    
    m_wordOfDay->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        word->SetValue("Word Of The Day");
        pronounciation->SetValue("pronounce");
        definition->SetValue("Definition of the word");
    });
    
    sizer5->Add(m_wordOfDay, 0);
    sizer5->Add(chooseDataSet,0,wxBOTTOM,5);
    
    sizer4->Add(sizer2,0);
    sizer4->AddSpacer(300);
    sizer4->Add(sizer3,0);
    
    all_sizer->Add(sizer,0);
    all_sizer->Add(sizer4,0);
    all_sizer->Add(definition,0);
    all_sizer->Add(sizer5, 0, wxALIGN_RIGHT);
    
    panel->SetSizer(all_sizer);
    
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
    
    wxWindow *page = CreateInsertPage(parent);
    parent->InsertPage( 0, page, DICTIONARY, false, GetIconIndex(parent) );
    
    page = CreateRadioButtonsPage(parent);
    parent->AddPage( page, ADD_NEW_WORD, false, GetIconIndex(parent) );
    
    page = CreateVetoPage(parent);
    parent->AddPage( page, FAVOURITE_LIST, false, GetIconIndex(parent) );
    
    page = CreateFullPageText(parent);
    parent->AddPage( page, GAME, false, GetIconIndex(parent) );
    
    parent->SetSelection(0);
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
    
        CreateInitialPages(m_bookCtrl);
    
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