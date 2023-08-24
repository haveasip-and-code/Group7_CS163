//
//  treebook test.hpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 31/07/2023.
//

#ifndef treebook_test_hpp
#define treebook_test_hpp

#include <wx/sound.h>
#include <stdio.h>
#include "wx/wx.h"
#include <wx/aui/auibook.h>
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
#include<wx/string.h>
#include "core.h"
#include "prototype.h"
#include "metadata.h"
#include "trie.h"
#include "databankManager.h"
#include "generalLib.h"
#include "debugCore.h"
#include "handling.h"


class MyPanel : public wxScrolledWindow
{
//Thank you chat GPT for your support
public:
    MyPanel(wxWindow* parent) : wxScrolledWindow(parent)
    {
        // Create a wxBoxSizer to hold the buttons
        m_sizer = new wxBoxSizer(wxVERTICAL);

        m_parent = parent;

        m_sizer->Clear();

        // Create multiple buttons and add them to the sizer

        /*
        for (int i = 0; i < 20; ++i)
        {
            wxButton* button = new wxButton(this, wxID_ANY, wxString::Format("Button %d", i+1));
            m_sizer->Add(button, 0, wxALL, 0);
        }
        */


        // Set the sizer for the wxScrolledWindow
        SetSizer(m_sizer);

        // Set the virtual size of the wxScrolledWindow to be larger than its client size
        SetVirtualSize(wxSize(200, 800));

        // Enable scrolling
        SetScrollRate(0, 10);

        // Call Layout() to update the layout
        Layout();
    }
    /*
    void AddButton()
    {
        // Create a new button and add it to the sizer
        wxButton* button = new wxButton(this, wxID_ANY, wxString::Format("Button %d", m_buttonCount + 1));
        m_sizer->Add(button, 0, wxALL, 5);

        // Increment the button count
        m_buttonCount++;

        // Call Layout() to update the layout
        Layout();
    }
    */
    void build(vector<pair<string,string>>& InitList) {
        int _n=InitList.size();
        m_sizer->Clear();
        for (int i = 0; i < _n; ++i)
        {
            wxButton* button = new wxButton(this, wxID_ANY, wxString::Format("Button %d", i+1));
            button->SetClientData(reinterpret_cast<void*>(i));
            button->SetLabel(stringToWxString(InitList[i].first));
            button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
            {
                //cout<<"Fuck\n";
                //this->build(InitList);
                //this->Layout();
                m_sizer->Layout();
                m_parent->Layout();
            });
            button->SetMinSize(wxSize(150,30));
            button->SetMaxSize(wxSize(150,30));
            m_sizer->Add(button, 0, wxALL, 0);
        }
        m_sizer->Layout();
        m_parent->Layout();
    }

private:
    wxBoxSizer* m_sizer;
    wxWindow* m_parent;
    int m_buttonCount = 0;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    virtual ~MyFrame();
    void OnBookCtrl(wxBookCtrlBaseEvent& event);
    void OnShowImages(wxCommandEvent& event);

    enum GameMode {
        GuessWord,
        GuessDefinition
    };






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

    wxSound m_tabChangeSound;
    wxPanel *m_panel; // Panel containing notebook and other controls
    wxBookCtrlBase *m_bookCtrl;


    // Log window
    wxStaticText *m_text;
 // USE_LOG
    bool m_chkShowImages;
    wxBoxSizer *m_sizerFrame;

    wxBookCtrlBase::Images m_images;

    wxBitmapButton* m_reset;
    wxBitmapButton* m_logout;

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
