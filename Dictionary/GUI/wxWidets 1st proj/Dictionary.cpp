#include "Dictionary.hpp"

DictionaryWin::DictionaryWin(const wxString& title)
: wxFrame((wxFrame *) NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY), wxSize(1200, 750),wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    searchTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1100, 100));
    searchTop->SetBackgroundColour(wxColour(*wxRED));
    
    meaningLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
    meaningLeft->SetBackgroundColour(wxColour(*wxGREEN));
    
    toolRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 600));
    toolRight->SetBackgroundColour(wxColour(*wxBLUE));
    
    wxBoxSizer *dict = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *meaningTool = new wxBoxSizer(wxHORIZONTAL);
    
    meaningTool->Add(meaningLeft, 2, wxALL, 5);
    meaningTool->Add(toolRight, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
    
    dict->Add(searchTop, 0, wxEXPAND | wxALL, 5);
    dict->Add(meaningTool, 2, wxEXPAND | wxBOTTOM, 5);
    
    this->SetSizerAndFit(dict);
   
}

DictionaryWin::~DictionaryWin() {}
