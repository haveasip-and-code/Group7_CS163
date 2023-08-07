#include "Dictionary.hpp"
#include "Form Login.hpp"

wxBitmapToggleButton* pressed = 0;

DictionaryWin::DictionaryWin(const wxString& title)
: wxFrame((wxFrame *) NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY), wxSize(1200, 680),wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    //Two main parts of the window
    wxBoxSizer* dict_sz = new wxBoxSizer(wxHORIZONTAL);
    
    //Function panel
    function_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(70,680));
    function_panel->SetBackgroundColour(wxColour(73,86,111));
    
    wxBoxSizer* function_sz = new wxBoxSizer(wxVERTICAL);
    
    //set main button icon
    ::wxInitAllImageHandlers();
    main_ig = wxBitmap("dict_unclicked.png", wxBITMAP_TYPE_ANY);
    if (!main_ig.Ok())
    {
        wxMessageBox(wxT("Sorry, could not load file."));
    }
    
    m_main = new wxBitmapToggleButton(function_panel, BUTTON_main, main_ig, wxDefaultPosition, wxSize(70, 70));
    function_sz->Add(m_main,0);
    
    //Set add button icon
    add_ig = wxBitmap("add_unclicked.png", wxBITMAP_TYPE_ANY);
    if (!add_ig.Ok())
    {
        wxMessageBox(wxT("Sorry, could not load file."));
    }
    
    m_add = new wxBitmapToggleButton(function_panel, BUTTON_add, add_ig, wxDefaultPosition, wxSize(70, 70));
    function_sz->Add(m_add, 0);
    //Set favourite icon
    
    
    //Set game icon
    
    
    //Set reset icon
    
    
    //Set logout icon
    
    function_panel->SetSizer(function_sz);
    
    //Word panel
    word_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1130, 680));
    word_panel->SetBackgroundColour(wxColour(248, 247, 245));
    
    
    dict_sz->Add(function_panel, 0);
    dict_sz->Add(word_panel, 0);
    
    m_main->Bind(wxEVT_TOGGLEBUTTON, &DictionaryWin::OnMainClick, this);
    m_add->Bind(wxEVT_TOGGLEBUTTON, &DictionaryWin::OnAddClick, this);
    this->SetSizer(dict_sz);
    
    
    
}

void DictionaryWin::OnMainClick(wxCommandEvent& event)
{
    static bool click = m_main->GetValue();
    if(click==true)
    {
        if (pressed!=m_main) {
            if (pressed) pressed->SetValue(false);
            pressed = m_main;
        }
        click = false;
    
        m_main->SetBitmap(wxBitmap("dict_clicked.png", wxBITMAP_TYPE_ANY));
        wxTextCtrl* test = new wxTextCtrl(word_panel, wxID_ANY, "TEST PANEL", wxDefaultPosition, wxDefaultSize);
        wxBoxSizer* vbox1 = new wxBoxSizer(wxVERTICAL);
        vbox1->Add(test, 0 , wxALIGN_CENTER);
        word_panel->SetSizer(vbox1);
    }
    else
    {
        click = true;
        pressed = 0;
        m_main->SetBitmap(main_ig);
        word_panel->GetSizer()->Clear(true);
        word_panel->SetSizer(NULL, true);
    }
}

void DictionaryWin::OnAddClick(wxCommandEvent& event){
    static bool click = m_add->GetValue();
    if(click==true)
    {
        if (pressed!=m_add)
        {
            if (pressed) pressed->SetValue(false);
            pressed = m_add;
        }
        click = false;
        wxTextCtrl* test = new wxTextCtrl(word_panel, wxID_ANY, "TEST PANEL 2", wxDefaultPosition, wxDefaultSize);
        wxBoxSizer* vbox1 = new wxBoxSizer(wxVERTICAL);
        vbox1->Add(test,0, wxALIGN_CENTER);
        word_panel->SetSizer(vbox1);
        
        m_add->SetBitmap(wxBitmap("add_clicked.png", wxBITMAP_TYPE_ANY));
    }
    else
    {
        click = true;
        m_add->SetBitmap(add_ig);
        pressed = 0;
        
        word_panel->SetSizer(NULL);
        word_panel->Layout();
    }
}


void DictionaryWin::OnFavouriteClick(wxCommandEvent& event){
    
}

void DictionaryWin::OnGameClick(wxCommandEvent& event){
    
}

void DictionaryWin::OnResetClick(wxCommandEvent& event){
    
}

void DictionaryWin::OnLogoutClick(wxCommandEvent& event){
    this->Close();
    
    FormLogin* login = new FormLogin("Login");
    login->Show(true);
}

BEGIN_EVENT_TABLE(DictionaryWin, wxFrame)
EVT_BUTTON(BUTTON_main, DictionaryWin::OnMainClick)
EVT_BUTTON(BUTTON_add, DictionaryWin::OnAddClick)
EVT_BUTTON(BUTTON_favourite, DictionaryWin::OnFavouriteClick)
EVT_BUTTON(BUTTON_game, DictionaryWin::OnGameClick)
EVT_BUTTON(BUTTON_reset, DictionaryWin::OnResetClick)
EVT_BUTTON(BUTTON_logout, DictionaryWin::OnLogoutClick)
END_EVENT_TABLE()


DictionaryWin::~DictionaryWin() {}

/*searchTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1000,100));
 searchTop->SetBackgroundColour(wxColour(*wxRED));
 
 meaningLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1000,600));
 meaningLeft->SetBackgroundColour(wxColour(*wxGREEN));
 
 toolRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 700));
 toolRight->SetBackgroundColour(wxColour(*wxBLUE));
 
 wxBoxSizer *dict = new wxBoxSizer(wxHORIZONTAL);
 wxBoxSizer *search = new wxBoxSizer(wxVERTICAL);
 
 searchInput = new wxSearchCtrl(searchTop, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, 20), wxTE_PROCESS_ENTER|wxTE_LEFT);
 searchInput->ShowCancelButton (true);
 searchInput->SetDescriptiveText("Type word or definition");
 
 m_searchButton = new wxButton(searchTop, BUTTON_search, "Search");
 m_searchButton->Bind(wxEVT_BUTTON, &DictionaryWin::search, this);
 
 wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
 searchSizer->Add(searchInput, 1, wxALL | wxEXPAND, 5);
 searchSizer->Add(m_searchButton,0);
 searchTop->SetSizer(searchSizer);
 
 search->Add(searchTop, 0, wxALL, 5);
 search->Add(meaningLeft, 1, wxTOP | wxBOTTOM | wxRIGHT, 5);
 
 
 dict->Add(toolRight, 0, wxEXPAND | wxALL, 5);
 dict->Add(search, 2, wxEXPAND | wxBOTTOM, 5);
 
 this->SetSizerAndFit(dict);
 void DictionaryWin::search(wxCommandEvent& event){
 keyword = searchInput->GetValue();
 wxMessageBox("Your word : " + keyword, "Word", wxOK | wxICON_INFORMATION, this);
 }*/

