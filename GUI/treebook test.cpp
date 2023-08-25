//
//  treebook test.cpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 31/07/2023.
//
#pragma once

#include "treebook test.hpp"
#include "Form Login.hpp"
#include "Form Login.hpp"
#include "core.h"
#include "prototype.h"
#include "metadata.h"
#include "trie.h"
#include "databankManager.h"
#include "generalLib.h"
#include "debugCore.h"
#include "handling.h"
#include "wx/sound.h"
#include "wx/setup.h"
#include "Windows.h"

#ifdef __WXMSW__
#include <windows.h>
#endif

// class displayList : public wxPanel {
// public:
//     displayList(wxWindow* parent, const wxString& labelText, const wxString& imageName)
//         : wxPanel(parent, wxID_ANY) {

//         // Create a box sizer to arrange contents
//         wxBoxSizer* theList = new wxBoxSizer(wxVERTICAL);
//         // Add a static text label
//         wxStaticText* label = new wxStaticText(this, wxID_ANY, labelText);
//         theList->Add(label, 0, wxALIGN_CENTER | wxALL, 10);

//         // Load and display an image
//         wxImage image(imageName, wxBITMAP_TYPE_ANY);
//         if (image.IsOk()) {
//             wxStaticBitmap* bitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(image));
//             theList->Add(bitmap, 0, wxALIGN_RIGHT, 10);
//         }

//         SetSizer(theList);
//     }
// };

int point;
int cmd;
int mode;
int factor;
int deltaPos;
int UserVal;

string username;
int userID;

wxString curWord;
wxString curDef;

extern int dataSetCnt;
extern int curDataSet;

extern vector<pair<string,string>> favouriteList;
extern vector<pair<string,string>> historyList;

extern TST data1;

MyFrame* dictionary;

bool isEditable;

/*
string correctAnswer="sound/correct.wav";
string wrongAnswer("sound/wrong.wav");
string clickSound("sound/click.wav");
string startSound("sound/startup.wav");
string doneSound("sound/donesearch.wav");
*/

wxSound correctAnswer("sound/correct.wav");
wxSound wrongAnswer("sound/wrong.wav");
wxSound clickSound("sound/click.wav");
wxSound startSound("sound/startup.wav");
wxSound doneSound("sound/donesearch.wav");
wxSound delSound("sound/del.wav");
wxSound tadaSound("sound/tada.wav");

vector<string> inputRegex;

MyPanel* subpanel;

wxPanel* mainPart;
wxScrolledWindow* panelt;
wxBoxSizer* sizer2t;
wxFont myAppFont2t;
wxTextCtrl* targett;

wxPanel* mainParr;
wxScrolledWindow* panelr;
wxBoxSizer* sizer2r;
wxFont myAppFont2r;
wxTextCtrl* targetr;

wxTextCtrl* word;

wxBitmap unfavorited_ico;
wxBitmap favorited_ico;

void constructSc(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target);
void resetSizer(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target);

void constructSr(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target);
void resetSizerr(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target);

wxWindow* CreateGamePage(wxBookCtrlBase* parent);
wxPanel *FavoriteList(wxBookCtrlBase *parent);
wxPanel *CreateAddPage(wxBookCtrlBase *parent);
wxPanel *DictionaryPage(wxBookCtrlBase *parent);
int GetIconIndex(wxBookCtrlBase* bookCtrl);

wxBitmapButton* m_favourite;

void searchFav(wxString key,wxTextCtrl* textArea) {
    string tmp=wxStringToString(key);
    for (int i=0;i<favouriteList.size();i++) {
        if (favouriteList[i].first==key) {
            textArea->SetValue(stringToWxString(favouriteList[i].first+"\n"+favouriteList[i].second));
            return;
        }
    }
    textArea->SetValue(stringToWxString("I have no idea what you are trying to search. Please, make some sense!!!"));
}

void moveFileData(string path) {
    ifstream in;
    ofstream out;
    in.open("backup/"+path);
    out.open("databank/"+path);
}

void resetAll() {
    historyList.clear();
    favouriteList.clear();
    saveFav();
    saveHistory();
    for (int i=1;i<=5;i++) {
        moveFileData(intToString(i)+"/maxslot.txt");
        moveFileData(intToString(i)+"/TST.txt");
    }
}

void searchHistory(wxString key,wxTextCtrl* textArea) {
    string tmp=wxStringToString(key);
    for (int i=0;i<historyList.size();i++) {
        if (historyList[i].first==key) {
            textArea->SetValue(stringToWxString(historyList[i].first+"\n"+historyList[i].second));
            return;
        }
    }
    textArea->SetValue(stringToWxString("I have no idea what you are trying to search. Please, make some sense!!!"));
}

void CreateInitialPages(wxBookCtrlBase *parent,int idx)
{
    // Create and add some panels to the notebook

    parent->SetSize(wxSize(70,680));

    wxWindow *page = DictionaryPage(parent);
    parent->InsertPage( 0, page, wxEmptyString, false, GetIconIndex(parent) );

    page = CreateAddPage(parent);
    parent->AddPage( page, wxEmptyString, false, GetIconIndex(parent) );

    page = FavoriteList(parent);
    parent->AddPage( page, wxEmptyString, false, GetIconIndex(parent) );

    page = CreateGamePage(parent);
    parent->AddPage( page, wxEmptyString, false, GetIconIndex(parent) );

    parent->SetSelection(idx);
}

void pSound(const std::string filename) {
    wxSound bitCHSound(filename);
    if (bitCHSound.Play(wxSOUND_ASYNC)) cout<<"Sound should play right?\n";
    //sndPlaySound(bitCHSound, SND_FILENAME | SND_ASYNC);
    /*
    int size = MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), -1, NULL, 0);
    wchar_t* wFileName = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), -1, wFileName, size);

    sndPlaySound(wFileName, SND_FILENAME | SND_ASYNC);

    delete[] wFileName;
    */
}

void pSound(wxSound& filename) {
    //wxSound bitCHSound(filename);
    if (filename.Play(wxSOUND_ASYNC)) cout<<"Sound should play right?\n";
    //sndPlaySound(bitCHSound, SND_FILENAME | SND_ASYNC);
    /*
    int size = MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), -1, NULL, 0);
    wchar_t* wFileName = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), -1, wFileName, size);

    sndPlaySound(wFileName, SND_FILENAME | SND_ASYNC);

    delete[] wFileName;
    */
}

void updateFavourite(pair<string,string> tmp) {
    //cout<<"+ "<<tmp.first<<'\n';
    favouriteList.push_back(tmp);
    sort(favouriteList.begin(),favouriteList.end());
    for (int i=0;i<favouriteList.size();i++) {
        cout<<favouriteList[i].first<<'\n';
    }
    saveFav();
}

void removeFavourite(pair<string,string> tmp) {
    //cout<<"- "<<tmp.first<<'\n';
    for (int i=0;i<favouriteList.size();i++) {
        if (tmp.first==favouriteList[i].first) {
            favouriteList.erase(favouriteList.begin()+i);
            return;
        }
    }
    saveFav();
}

void removeFavourite(int x) {
    favouriteList.erase(favouriteList.begin()+x);
    saveFav();
}


void updateHistory(pair<string,string> tmp) {
    //cout<<"+ "<<tmp.first<<'\n';
    historyList.insert(historyList.begin(),tmp);
    //sort(favouriteList.begin(),favouriteList.end());
    for (int i=0;i<historyList.size();i++) {
        cout<<historyList[i].first<<'\n';
    }
    saveHistory();
}

void removeHistory(pair<string,string> tmp) {
    //cout<<"- "<<tmp.first<<'\n';
    for (int i=0;i<historyList.size();i++) {
        if (tmp.first==historyList[i].first) {
            historyList.erase(historyList.begin()+i);
            return;
        }
    }
    saveHistory();
}

void removeHistory(int x) {
    historyList.erase(historyList.begin()+x);
    saveHistory();
}

bool isFavourite(string tmp) {
    for (int i=0;i<favouriteList.size();i++) {
        if (favouriteList[i].first==tmp) {
            return true;
        }
    }
    return false;
}

bool notFavorite;
wxBitmap statusBitmap;

wxPanel *DictionaryPage(wxBookCtrlBase *parent)
{
    pSound(startSound);
    //pSound("click.wav");
    //cout<<"What just happen?\n";
    wxPanel *panel = new wxPanel(parent);
    wxFont myAppFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");

    panel->SetBackgroundColour(wxColour(249, 246, 246));
    ::wxInitAllImageHandlers();

    wxBoxSizer* all_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    favorited_ico = wxBitmap("favorited.png", wxBITMAP_TYPE_ANY);
    unfavorited_ico = wxBitmap("unfavorited.png", wxBITMAP_TYPE_ANY);

    m_favourite = new wxBitmapButton(panel, wxID_ANY, unfavorited_ico, wxDefaultPosition, wxSize(30,30));

    wxChoice* chooseMode = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(110, 25));
    chooseMode->SetForegroundColour(wxColour(142, 159, 157));

    wxArrayString modeChoices;
    modeChoices.Add("By keyword");
    modeChoices.Add("By definition");
    modeChoices.Add("By part definition");
    chooseMode->Set(modeChoices);
    chooseMode->SetFont(myAppFont);

    chooseMode->SetSelection(0);
    mode=1;
    cmd=1;

    chooseMode->Bind(wxEVT_CHOICE, [=](wxCommandEvent& event){
        wxString selectedText = chooseMode->GetStringSelection();
        //wxLogMessage("Selected: %s", selectedText);
        if (selectedText=="By keyword") mode=1;
        else if (selectedText=="By definition") mode=2;
        else mode=3;
    });

    wxSearchCtrl* searchBar = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, 25), wxTE_PROCESS_ENTER|wxTE_LEFT);
    searchBar->SetForegroundColour(wxColour(73, 86, 111));
    // searchBar->ShowCancelButton(false);

    wxWindowListNode* firstChild = searchBar->GetChildren().GetFirst();

    if (firstChild) {
        wxTextCtrl* textCtrl = wxDynamicCast(firstChild->GetData(), wxTextCtrl);
        if (textCtrl) {
            textCtrl->SetFont(myAppFont);
        }
        else {
            wxLogMessage("No data");
        }
    }
    else {
        wxLogMessage("No firstChild");
    }

    word = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(200,-1), wxTE_PROCESS_ENTER|wxTE_READONLY/*|wxTE_CENTER*/);
    word->SetFont(wxFont(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Bold"));
    word->SetHint("the word");
    word->SetBackgroundColour(wxColour(249, 246, 246));
    word->SetForegroundColour(wxColour(73, 86, 111));

    #ifdef __WXMSW__
    // Disable the drop shadow effect on Windows
    HWND hwndTextCtrl = static_cast<HWND>(word->GetHWND());
    SetWindowLong(hwndTextCtrl, GWL_EXSTYLE, GetWindowLong(hwndTextCtrl, GWL_EXSTYLE) & ~WS_EX_CLIENTEDGE);
    #endif

    wxTextCtrl* definition = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(800,200), wxTE_PROCESS_ENTER|wxTE_READONLY/*|wxTE_CENTER*/|wxTE_MULTILINE|wxTE_NO_VSCROLL);
    //definition->SetScrollbar(wxVERTICAL, 0, 0, 0);

    definition->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium"));
    definition->SetHint("definition");
    definition->SetBackgroundColour(wxColour(249, 246, 246));
    definition->SetForegroundColour(wxColour(73, 86, 111));

    hwndTextCtrl = static_cast<HWND>(definition->GetHWND());
    SetWindowLong(hwndTextCtrl, GWL_EXSTYLE, GetWindowLong(hwndTextCtrl, GWL_EXSTYLE) & ~WS_EX_CLIENTEDGE);

    isEditable=false;
    word->SetEditable(isEditable);
    definition->SetEditable(isEditable);

    wxBitmap search_ig = wxBitmap("search-25.png", wxBITMAP_TYPE_ANY);

    //cout<<cmd<<'\n';

    wxBitmapButton* searchButton = new wxBitmapButton(panel, wxID_ANY, search_ig, wxDefaultPosition, wxSize(25,25));
    searchButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        pSound(clickSound);
        wxString searchText = searchBar->GetValue();
        //wxMessageBox("Searching for: " + searchText);
        //wxMessageBox(getPath(1));
        string tmp=string(searchText.mb_str());
        //cout<<tmp<<'\n';
        //string testStr="make";
        //cout<<data1.get(testStr)->val<<' '<<tmp<<'\n';
        pair<string,string> searchResult;
        if (mode==1) {
            searchResult=getWordDefAlways(data1,tmp);
            curDef=stringToWxString(searchResult.second);
            curWord=stringToWxString(searchResult.first);
            //cout<<curDef<<' '<<curWord<<'\n';
            //wxMessageBox(curWord+" "+curDef);
            //definition->ChangeValue("To hell with wxWidgets");
            word->ChangeValue(curWord);
            definition->ChangeValue(curDef);
        }
        else {
            factor=mode-1;
            deltaPos=0;
            transformDef(tmp,inputRegex);
            cout<<searchDef(cmd,deltaPos,inputRegex,inputRegex.size()/factor);
            searchResult=retrieveData(curDataSet,searchDef(cmd,deltaPos,inputRegex,inputRegex.size()/factor));
            curDef=stringToWxString(searchResult.second);
            curWord=stringToWxString(searchResult.first);
            //cout<<curDef<<' '<<curWord<<'\n';
            //wxMessageBox(curWord+" "+curDef);
            //definition->ChangeValue("To hell with wxWidgets");
            word->ChangeValue(curWord);
            definition->ChangeValue(curDef);
        }
        pSound(doneSound);
        if (isFavourite(wxStringToString(word->GetValue()))) {
            notFavorite=false;
        }
        else {
            notFavorite=true;
        }
        statusBitmap=notFavorite ? unfavorited_ico : favorited_ico;
        m_favourite->SetBitmapLabel(statusBitmap);
        m_favourite->SetSize(wxSize(30,30));
        updateHistory(searchResult);
        resetSizerr(mainParr,panelr,sizer2r,myAppFont2r,targetr);
        sizer2r->Layout();
    });

    sizer->Add(chooseMode, 0, wxLEFT);
    sizer->Add(searchBar, 0);
    sizer->Add(searchButton, 0, wxLEFT);

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);

    //wxTextCtrl* pronounciation = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(200,-1), wxTE_READONLY|wxTE_CENTER);
    //pronounciation->SetHint("Pronunciation");
    sizer2->Add(word, 0, wxLEFT);
    //sizer2->Add(pronounciation,0, wxLEFT, 10);

    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);

    // wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxBitmap unedit_ico = wxBitmap("edit_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap edit_ico = wxBitmap("edit_clicked.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* m_edit = new wxBitmapButton(panel, wxID_ANY, unedit_ico, wxDefaultPosition, wxSize(30,30));
    //wxBitmapButton* m_edit = new wxBitmapButton(panel, wxID_ANY, edit_ico, wxDefaultPosition);
    //m_edit->SetSize(wxSize(30, 30));
    m_edit->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                 {
            pSound(clickSound);
            wxBitmap statusBitmap = (isEditable) ? unedit_ico : edit_ico;
            m_edit->SetBitmapLabel(statusBitmap);
            panel->Layout();
            //notEdit = !notEdit;
        /*
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
        */
        word->SetEditable(!isEditable);
        definition->SetEditable(!isEditable);
        if (isEditable) {
            string tmp1,tmp2;
            tmp1=wxStringToString(word->GetValue());
            tmp2=wxStringToString(definition->GetValue());
            addWord(data1,tmp1,tmp2);
            saveCurrentDataSet(data1);
            //cout<<tmp1<<' '<<tmp2<<' '<<word->GetValue()<<' '<<definition->GetValue()<<'\n';
        }
        else {

        }
        isEditable=!isEditable;
    });
    wxButton* m_remove = new wxButton(panel, wxID_ANY, "Remove", wxDefaultPosition, wxSize(95, 30));
    m_remove->SetBackgroundColour(wxColour(218, 85, 83));
    m_remove->SetForegroundColour(*wxWHITE);
    m_remove->SetFont(myAppFont);
    m_remove->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                   {
        pSound(clickSound);
        //Function cua Cuong
        //wxLogMessage("This word has been removed!");
        //pronounciation->Clear();
        string tmp1,tmp2;
        tmp1=wxStringToString(word->GetValue());
        tmp2="";
        //cout<<"Yes\n";
        addWord(data1,tmp1,tmp2);
        saveCurrentDataSet(data1);
        word->Clear();
        definition->Clear();
        word->SetHint("Word");
        definition->SetHint("Definition");
    });

    if (isFavourite(wxStringToString(word->GetValue()))) {
        notFavorite=false;
    }
    else {
        notFavorite=true;
    }
    statusBitmap = notFavorite ? unfavorited_ico : favorited_ico;
    m_favourite->SetBitmapLabel(statusBitmap);
    m_favourite->SetSize(wxSize(30,30));

    m_favourite->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        //notFavorite = !notFavorite;
        pSound(clickSound);
        if (isFavourite(wxStringToString(word->GetValue()))) {
            notFavorite=false;
        }
        else {
            notFavorite=true;
        }
        if (!notFavorite) {
            string tmp1,tmp2;
            tmp1=wxStringToString(word->GetValue());
            tmp2="";
            removeFavourite({tmp1,tmp2});
            //addWordFavorite(favor,tmp1,tmp2);
        }
        else {
            string tmp1,tmp2;
            tmp1=wxStringToString(word->GetValue());
            tmp2=wxStringToString(definition->GetValue());
            updateFavourite({tmp1,tmp2});
            //addWordFavorite(favor,tmp1,tmp2);
        }
        notFavorite=!notFavorite;
        statusBitmap = notFavorite ? unfavorited_ico : favorited_ico;
        m_favourite->SetBitmapLabel(statusBitmap);
        m_favourite->SetSize(wxSize(30,30));
        panel->Layout();
        resetSizer(mainPart,panelt,sizer2t,myAppFont2t,targett);
        resetSizerr(mainParr,panelr,sizer2r,myAppFont2r,targetr);
        sizer2t->Layout();
        //subpanel->build(favouriteList);
    });

    sizer2->AddStretchSpacer();
    sizer2->Add(m_remove, 0, wxRIGHT);
    sizer2->AddSpacer(24);
    sizer2->Add(m_edit, 0, wxRIGHT);
    sizer2->AddSpacer(24);
    sizer2->Add(m_favourite, 0, wxRIGHT, 50);

    wxBoxSizer* sizer5 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer6 = new wxBoxSizer(wxHORIZONTAL);

    wxBitmap unDataSet_ico = wxBitmap("dataset_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap DataSet_ico = wxBitmap("dataset_clicked.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* m_dataset = new wxBitmapButton(panel, wxID_ANY, unDataSet_ico, wxDefaultPosition, wxSize(50, 50));

    wxChoice* chooseDataSet = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    wxArrayString dataSets;
    dataSets.Add("Eng - Vie");
    dataSets.Add("Vie - Eng");
    dataSets.Add("Eng - Eng");
    //dataSets.Add("Emoji - Vie");
    //dataSets.Add("Emoji - Eng");
    //dataSets.Add("Eng slangs");
    //dataSets.Add("Vie slangs");
    dataSets.Add("Slangs");
    dataSets.Add("Emoji");
    chooseDataSet->Set(dataSets);

    chooseDataSet->SetSelection(0);

    chooseDataSet->Bind(wxEVT_CHOICE, [=](wxCommandEvent& event){
        static bool notDataSet = true;
        wxBitmap statusBitmap = notDataSet ? DataSet_ico : unDataSet_ico;
        m_dataset->SetBitmapLabel(statusBitmap);
        m_dataset->SetSize(wxSize(30, 30));
        panel->Layout();
        notDataSet = !notDataSet;

        wxString selectedText = chooseDataSet->GetStringSelection();
        if (selectedText=="Eng - Vie") cmd=1;
        else if (selectedText=="Vie - Eng") cmd=2;
        else if (selectedText=="Eng - Eng") cmd=3;
        else if (selectedText=="Slangs") cmd=4;
        else if (selectedText=="Emoji") cmd=5;
        else if (selectedText=="Eng slangs") cmd=6;
        else if (selectedText=="Vie slangs") cmd=7;
        saveCurrentDataSet(data1);
        curDataSet=cmd;
        setStartSlot(getCurrentStartSlot());
        data1.loadFromFile(getPath(cmd));
        //wxLogMessage("Selected: %s", selectedText);
        //wxLogMessage("Load data1 set "+selectedText);
    });

    wxBitmap unwotd_ico = wxBitmap("wotd_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap wotd_ico = wxBitmap("wotd_clicked.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* m_wordOfDay = new wxBitmapButton(panel, wxID_ANY, unwotd_ico, wxDefaultPosition, wxSize(50, 50));

    m_wordOfDay->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
                pSound(tadaSound);
            static bool notWotd = true;
            wxBitmap statusBitmap = notWotd ? wotd_ico : unwotd_ico;
            m_wordOfDay->SetBitmapLabel(statusBitmap);
            m_wordOfDay->SetSize(wxSize(50, 50));
            panel->Layout();
            notWotd = !notWotd;

             pair<string,string> searchResult=getRandomWord(data1);
        curDef=stringToWxString(searchResult.second);
        curWord=stringToWxString(searchResult.first);
        word->ChangeValue(curWord);
        definition->ChangeValue(curDef);
    });

    sizer5->Add(m_wordOfDay, 0, wxRIGHT, 26);
    sizer5->AddSpacer(5);

    sizer6->Add(chooseDataSet, 0, wxRIGHT, 5);
    sizer6->Add(m_dataset, 0, wxRIGHT, 26);

    // sizer3->Add(sizer2, 0);
    // sizer3->AddSpacer(300);
    // // sizer4->Add(sizer3, 0);

    all_sizer->AddSpacer(35);
    all_sizer->Add(sizer, 0, wxLEFT, 50);
    all_sizer->AddSpacer(60);
    all_sizer->Add(sizer2, 0, wxEXPAND | wxLEFT, 50);
    all_sizer->Add(definition, 0, wxLEFT, 50);
    all_sizer->Add(sizer5, 0, wxALIGN_RIGHT);
    all_sizer->Add(sizer6, 0, wxALIGN_RIGHT);
    all_sizer->AddSpacer(22);
    panel->SetSizer(all_sizer);

    return panel;
}

wxPanel *CreateAddPage(wxBookCtrlBase *parent)
{
     wxPanel *panel = new wxPanel(parent);
    wxFont myAppFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    wxFont myAppFont2(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    wxFont subTextFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    panel->SetBackgroundColour(wxColour(249, 246, 246));

    wxScrolledWindow* lowpanel = new wxScrolledWindow(panel);
    /*
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create the subpanel and add it to the sizer

    wxPanel* scPanel=new wxPanel(panel);
    scPanel->SetSize(wxSize(3000,5000));
    scPanel->SetPosition(wxPoint(100,100));
    scPanel->SetBackgroundColour(wxColour(100,100,100));

    subpanel = new MyPanel(scPanel);
    sizer->Add(subpanel, 1, wxEXPAND);

    // Set the sizer for the main panel
    //scPanel->SetSizer(sizer);

    // Fit the main panel to the frame size
    sizer->Fit(scPanel);

    subpanel->build(favouriteList);
    subpanel->Layout();
    */
    wxBoxSizer* biggest = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* textArea = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* mergerScreen = new wxBoxSizer(wxHORIZONTAL);

    wxPanel* infoPanel = new wxPanel;
    infoPanel->SetBackgroundColour(wxColour(100,100,150));
    infoPanel->SetSizer(textArea);

    wxTextCtrl* infoText= new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    infoText->SetId(wxID_ANY);
    infoText->SetValue(wxEmptyString);
    infoText->SetPosition(wxDefaultPosition);
    infoText->SetSize(wxDefaultSize);
    /*
    wxTextAttr infoTextAttr;
    //infoTextAttr.SetTextColour(wxColor());
    infoTextAttr.SetFont();
    infoText->SetDefaultStyle(wxTE_PROCESS_ENTER|wxTE_READONLY|wxTE_MULTILINE);
    */

    // search area
    wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);

    wxSearchCtrl* searchBar = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, 25), wxTE_PROCESS_ENTER|wxTE_LEFT);
    searchBar->SetBackgroundColour(wxColour(200, 210, 209));
    searchBar->SetForegroundColour(wxColour(73, 86, 111));

    wxWindowListNode* firstChild = searchBar->GetChildren().GetFirst();

    if (firstChild) {
        wxTextCtrl* textCtrl = wxDynamicCast(firstChild->GetData(), wxTextCtrl);
        if (textCtrl) {
            textCtrl->SetFont(myAppFont);
            textCtrl->SetForegroundColour(wxColour(142, 159, 157));
        }
        else {
            wxLogMessage("No data1");
        }
    }
    else {
        wxLogMessage("No firstChild");
    }

    wxBitmap search_ig = wxBitmap("search-25.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* searchButton = new wxBitmapButton(panel, wxID_ANY, search_ig, wxDefaultPosition, wxSize(25,25));

    searchButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event){
        wxString searchText = searchBar->GetValue();
        pSound(clickSound);
        //wxMessageBox("Searching for: " + searchText);
        searchHistory(searchText,infoText);
    });
    sizer1->Add(searchBar, 0, wxLEFT, 5);
    sizer1->Add(searchButton, 0, wxLEFT);

    // result area, đoạn này chỉnh màu chưa đc :)
    wxPanel* base = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    base->SetBackgroundColour(wxColour(238, 238, 238));
    sizer1->Add(base);

    // ------------------------------------------------------------------ create one word item
    wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);
    lowpanel->SetVirtualSize(wxSize(200, 800));
    lowpanel->SetScrollRate(0, 10);
    lowpanel->SetSizer(sizer2);
    lowpanel->ShowScrollbars(wxSHOW_SB_DEFAULT,wxSHOW_SB_DEFAULT);
    mainParr=panel;
    panelr=lowpanel;
    sizer2r=sizer2;
    myAppFont2r=myAppFont2;
    targetr=infoText;
    constructSr(panel,lowpanel,sizer2,myAppFont2,infoText);
    /*
    wxBoxSizer* wordInfo = new wxBoxSizer(wxVERTICAL);
    wxPanel* line1 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(530, 50));
    line1->SetBackgroundColour(wxColour(142, 159, 157));

    wxStaticText* wordName = new wxStaticText(line1, wxID_ANY,"Word number 1");
    //wxStaticText* wordDef = new wxStaticText(line1, wxID_ANY, "Definition goes here...");
    wordName->SetFont(myAppFont2);
   // wordDef->SetFont(subTextFont);
    wordName->SetForegroundColour(wxColour(73, 86, 111));
    //wordDef->SetForegroundColour(wxColour(73, 86, 111));
    // wordName->SetForegroundColour(wxColour(242, 224, 195));
    // wordDef->SetForegroundColour(wxColour(242, 224, 195));

    // chưa tìm đc cách bind cả wordInfo với event
    line1->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event){
        wxMessageBox(wxString::Format("Chose word: %s", wordName->GetLabel()), wxT("Message"));
    });

    wxBitmap favorited_ico = wxBitmap("favorited.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* removeFromFav = new wxBitmapButton(line1, wxID_ANY, favorited_ico, wxDefaultPosition, wxSize(30,30));

    wxBoxSizer* itemSizer = new wxBoxSizer(wxHORIZONTAL);

    wordInfo->Add(wordName, 20, wxALIGN_CENTRE, 5);
    //wordInfo->Add(wordDef, 0, wxLEFT, 5);
    itemSizer->Add(wordInfo, 20, wxALIGN_CENTRE, 5);
    itemSizer->AddStretchSpacer(1);
    itemSizer->Add(removeFromFav, 0, wxRIGHT|wxCENTRE);
    line1->SetSizer(itemSizer);
    sizer2->Add(line1);
    */
    // ------------------------------------------------------------------ create one word item

    //panel->GetSizer()->Detach(infoText);

    biggest->Add(sizer1, 0, wxEXPAND);
    biggest->AddSpacer(5);
    biggest->Add(lowpanel, wxEXPAND, wxEXPAND);
    mergerScreen->Add(biggest,0,wxEXPAND);
    //textArea->Add(infoText,0,wxEXPAND);
    //mergerScreen->Add(textArea,wxEXPAND,wxEXPAND);
    mergerScreen->Add(infoText,wxEXPAND,wxEXPAND);


    panel->SetSizer(mergerScreen);
    return panel;
    //wxPanel *panel = new wxPanel(parent);
    /*

    wxTextCtrl* keyword = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(800,40));
    keyword->SetHint("Type your new word here");
    keyword->SetForegroundColour(wxColour("#49566f"));
    keyword->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
    keyword->SetBackgroundColour(wxColour("#c8d2d1"));

    wxTextCtrl* pronounciation = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(400, 40));
    pronounciation->SetHint("Type your pronounciation here");
    pronounciation->SetForegroundColour(wxColour("#49566f"));
    pronounciation->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
    pronounciation->SetBackgroundColour(wxColour("#eeeeee"));

    wxTextCtrl* wordType = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(400, 40));
    wordType->SetHint("Type your word type here");
    wordType->SetForegroundColour(wxColour("#49566f"));
    wordType->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
    wordType->SetBackgroundColour(wxColour("#eeeeee"));

    wxTextCtrl* meaning = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(1000, 200), wxTE_MULTILINE);
    meaning->SetHelpText("Type your definition here");
    meaning->SetForegroundColour(wxColour("#f0dec2"));
    meaning->SetBackgroundColour(wxColour("#eeeeee"));
    meaning->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));

    wxButton* add = new wxButton(panel, wxID_OK, "Add");
    add->SetMinSize(wxSize(80, 40));
    add->SetForegroundColour(wxColour("#f0dec2"));
    add->SetBackgroundColour(wxColour("#49566f"));
    add->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(keyword,0,wxLEFT|wxTOP,10);
    sizer->Add(pronounciation,0, wxLEFT|wxTOP, 10);
    sizer->Add(wordType, 0,wxLEFT| wxTOP,10);
    sizer->Add(meaning,0,wxLEFT|wxTOP,10);
    sizer->Add(add,0, wxALIGN_RIGHT|wxTOP,10);
    panel->SetSizer(sizer);
    */
    return panel;
}

void resetSizer(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target) {
    // Clear and detach each item in the sizer
    while (!sizer2->IsEmpty())
    {
        wxSizerItem* item = sizer2->GetItem(size_t(0));
        wxWindow* window = item->GetWindow();

        sizer2->Detach(0);
        delete window;
        //window->Destroy();
    }

    // Clear the sizer itself
    sizer2->Clear();
    //dictionary->Refresh();
    //dictionary->Update();
    //sizer2->Clear();
    panel->SetSizer(sizer2);
    //mainPar->Layout();
    //sizer2->Layout();
    //sizer2->SetOrientation(wxVERTICAL);
    //cout<<sizer2->m_totalProportion;
    //wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);
    //sizer2=sizer3;
    //wxBookCtrlBase* parent=dynamic_cast<wxBookCtrlBase*>(dictionary->m_sizerFrame->GetItem(size_t(0)));
    //wxPanel* page = FavoriteList(parent);
    //parent->RemovePage(2);
    //wxBitmap fav("favorite_unclicked.png", wxBITMAP_TYPE_ANY);
    //parent->InsertPage(2, page, wxEmptyString, false, 2);
    //dictionary->RecreateBook(2);
    //cout<<"Help me\n";
    constructSc(mainPar,panel,sizer2,myAppFont2,target);
    sizer2->Layout();
    mainPar->Layout();
    //sizer2->Hide(false);
    //mainPar->Layout();
    //sizer2->Layout();
    //panel->Layout();
}

void constructSc(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target) {
    for (int i=0;i<favouriteList.size();i++) {
    //cout<<i<<'\n';
    wxBoxSizer* wordInfo = new wxBoxSizer(wxVERTICAL);
    wxPanel* line1 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(530, 50));
    line1->SetBackgroundColour(wxColour(142, 159, 157));

    wxStaticText* wordName = new wxStaticText(line1, wxID_ANY,stringToWxString(favouriteList[i].first));
    int* clientValue= new int;
    *clientValue=i;
    line1->SetClientData(clientValue);
    //wxStaticText* wordDef = new wxStaticText(line1, wxID_ANY, "Definition goes here...");
    wordName->SetFont(myAppFont2);
   // wordDef->SetFont(subTextFont);
    wordName->SetForegroundColour(wxColour(73, 86, 111));
    //wordDef->SetForegroundColour(wxColour(73, 86, 111));
    // wordName->SetForegroundColour(wxColour(242, 224, 195));
    // wordDef->SetForegroundColour(wxColour(242, 224, 195));

    // chưa tìm đc cách bind cả wordInfo với event
    line1->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event){
            pSound(clickSound);
        //wxMessageBox(wxString::Format("Chose word: %s", intToString(static_cast<int*>(line1->GetClientData())), wxT("Message")));
        int pos=*static_cast<int*>(line1->GetClientData());
        target->SetValue(stringToWxString(favouriteList[pos].first+"\n"+favouriteList[pos].second));
    });

    wxBitmap favorited_ico = wxBitmap("favorited.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* removeFromFav = new wxBitmapButton(line1, wxID_ANY, favorited_ico, wxDefaultPosition, wxSize(30,30));
    removeFromFav->SetClientData(clientValue);

    removeFromFav->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event){pSound(delSound);
        int pos=*static_cast<int*>(removeFromFav->GetClientData());
        removeFavourite(pos);
        resetSizer(mainPar,panel,sizer2,myAppFont2,target);
        /*
        // Clear and detach each item in the sizer
        while (sizer2->IsEmpty())
        {
            wxSizerItem* item = sizer2->GetItem(size_t(0));
            wxWindow* window = item->GetWindow();

            sizer2->Detach(0);
            window->Destroy();
        }

        // Clear the sizer itself
        sizer2->Clear();
        //dictionary->Refresh();
        //dictionary->Update();
        //sizer2->Clear();
        panel->SetSizer(sizer2);
        //mainPar->Layout();
        //sizer2->Layout();
        //sizer2->SetOrientation(wxVERTICAL);
        //cout<<sizer2->m_totalProportion;
        //wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);
        //sizer2=sizer3;
        //wxBookCtrlBase* parent=dynamic_cast<wxBookCtrlBase*>(dictionary->m_sizerFrame->GetItem(size_t(0)));
        //wxPanel* page = FavoriteList(parent);
        //parent->RemovePage(2);
        //wxBitmap fav("favorite_unclicked.png", wxBITMAP_TYPE_ANY);
        //parent->InsertPage(2, page, wxEmptyString, false, 2);
        //dictionary->RecreateBook(2);
        //cout<<"Help me\n";
        constructSc(mainPar,panel,sizer2,myAppFont2,target);
        sizer2->Layout();
        mainPar->Layout();
        //mainPar->Layout();
        //sizer2->Layout();
        //panel->Layout();
        */
        if (isFavourite(wxStringToString(word->GetValue()))) {
            notFavorite=false;
        }
        else {
            notFavorite=true;
        }
        wxBitmap statusBitmap = notFavorite ? unfavorited_ico : favorited_ico;
        m_favourite->SetBitmapLabel(statusBitmap);
        m_favourite->SetSize(wxSize(30,30));
    });

    wxBoxSizer* itemSizer = new wxBoxSizer(wxHORIZONTAL);

    wordInfo->Add(wordName, 20, wxALIGN_CENTRE, 5);
    //wordInfo->Add(wordDef, 0, wxLEFT, 5);
    itemSizer->Add(wordInfo, 20, wxALIGN_CENTRE, 5);
    itemSizer->AddStretchSpacer(1);
    itemSizer->Add(removeFromFav, 0, wxRIGHT|wxCENTRE, 20);
    //wxSizerItem* itemToRemove = itemSizer->GetItem(removeFromFav);
    //wxPoint currentPosition = itemToRemove->GetPosition();
    //int newX = currentPosition.x + 20;
    //int newY = currentPosition.y;
    //itemToRemove->SetItemPosition(wxPoint(newX, newY));
    line1->SetSizer(itemSizer);
    sizer2->Add(line1);
    }
    //cout<<"Done\n";
}


void resetSizerr(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target) {
    // Clear and detach each item in the sizer
    while (!sizer2->IsEmpty())
    {
        wxSizerItem* item = sizer2->GetItem(size_t(0));
        wxWindow* window = item->GetWindow();

        sizer2->Detach(0);
        delete window;
        //window->Destroy();
    }

    // Clear the sizer itself
    sizer2->Clear();
    //dictionary->Refresh();
    //dictionary->Update();
    //sizer2->Clear();
    panel->SetSizer(sizer2);
    //mainPar->Layout();
    //sizer2->Layout();
    //sizer2->SetOrientation(wxVERTICAL);
    //cout<<sizer2->m_totalProportion;
    //wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);
    //sizer2=sizer3;
    //wxBookCtrlBase* parent=dynamic_cast<wxBookCtrlBase*>(dictionary->m_sizerFrame->GetItem(size_t(0)));
    //wxPanel* page = FavoriteList(parent);
    //parent->RemovePage(2);
    //wxBitmap fav("favorite_unclicked.png", wxBITMAP_TYPE_ANY);
    //parent->InsertPage(2, page, wxEmptyString, false, 2);
    //dictionary->RecreateBook(2);
    //cout<<"Help me\n";
    constructSr(mainPar,panel,sizer2,myAppFont2,target);
    sizer2->Layout();
    mainPar->Layout();
    //sizer2->Hide(false);
    //mainPar->Layout();
    //sizer2->Layout();
    //panel->Layout();
}

void constructSr(wxPanel* mainPar,wxScrolledWindow* panel,wxBoxSizer* sizer2,wxFont myAppFont2,wxTextCtrl* target) {
    for (int i=0;i<historyList.size();i++) {
    //cout<<historyList.size()<<"00000000\n";
    //cout<<i<<'\n';
    wxBoxSizer* wordInfo = new wxBoxSizer(wxVERTICAL);
    wxPanel* line1 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(530, 50));
    line1->SetBackgroundColour(wxColour(142, 159, 157));

    wxStaticText* wordName = new wxStaticText(line1, wxID_ANY,stringToWxString(historyList[i].first));
    int* clientValue= new int;
    *clientValue=i;
    line1->SetClientData(clientValue);
    //wxStaticText* wordDef = new wxStaticText(line1, wxID_ANY, "Definition goes here...");
    wordName->SetFont(myAppFont2);
   // wordDef->SetFont(subTextFont);
    wordName->SetForegroundColour(wxColour(73, 86, 111));
    //wordDef->SetForegroundColour(wxColour(73, 86, 111));
    // wordName->SetForegroundColour(wxColour(242, 224, 195));
    // wordDef->SetForegroundColour(wxColour(242, 224, 195));

    // chưa tìm đc cách bind cả wordInfo với event
    line1->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event){
        pSound(clickSound);
        //wxMessageBox(wxString::Format("Chose word: %s", intToString(static_cast<int*>(line1->GetClientData())), wxT("Message")));
        int pos=*static_cast<int*>(line1->GetClientData());
        target->SetValue(stringToWxString(historyList[pos].first+"\n"+historyList[pos].second));
    });

    wxBitmap favorited_ico = wxBitmap("favorited.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* removeFromFav = new wxBitmapButton(line1, wxID_ANY, favorited_ico, wxDefaultPosition, wxSize(30,30));
    removeFromFav->SetClientData(clientValue);

    removeFromFav->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event){
        pSound(delSound);
        int pos=*static_cast<int*>(removeFromFav->GetClientData());
        removeHistory(pos);
        resetSizerr(mainPar,panel,sizer2,myAppFont2,target);
        /*
        // Clear and detach each item in the sizer
        while (sizer2->IsEmpty())
        {
            wxSizerItem* item = sizer2->GetItem(size_t(0));
            wxWindow* window = item->GetWindow();

            sizer2->Detach(0);
            window->Destroy();
        }

        // Clear the sizer itself
        sizer2->Clear();
        //dictionary->Refresh();
        //dictionary->Update();
        //sizer2->Clear();
        panel->SetSizer(sizer2);
        //mainPar->Layout();
        //sizer2->Layout();
        //sizer2->SetOrientation(wxVERTICAL);
        //cout<<sizer2->m_totalProportion;
        //wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);
        //sizer2=sizer3;
        //wxBookCtrlBase* parent=dynamic_cast<wxBookCtrlBase*>(dictionary->m_sizerFrame->GetItem(size_t(0)));
        //wxPanel* page = FavoriteList(parent);
        //parent->RemovePage(2);
        //wxBitmap fav("favorite_unclicked.png", wxBITMAP_TYPE_ANY);
        //parent->InsertPage(2, page, wxEmptyString, false, 2);
        //dictionary->RecreateBook(2);
        //cout<<"Help me\n";
        constructSc(mainPar,panel,sizer2,myAppFont2,target);
        sizer2->Layout();
        mainPar->Layout();
        //mainPar->Layout();
        //sizer2->Layout();
        //panel->Layout();
        */
    });

    wxBoxSizer* itemSizer = new wxBoxSizer(wxHORIZONTAL);

    wordInfo->Add(wordName, 20, wxALIGN_CENTRE, 5);
    //wordInfo->Add(wordDef, 0, wxLEFT, 5);
    itemSizer->Add(wordInfo, 20, wxALIGN_CENTRE, 5);
    itemSizer->AddStretchSpacer(1);
    itemSizer->Add(removeFromFav, 0, wxRIGHT|wxCENTRE, 20);
    //wxSizerItem* itemToRemove = itemSizer->GetItem(removeFromFav);
    //wxPoint currentPosition = itemToRemove->GetPosition();
    //int newX = currentPosition.x + 20;
    //int newY = currentPosition.y;
    //itemToRemove->SetItemPosition(wxPoint(newX, newY));
    line1->SetSizer(itemSizer);
    sizer2->Add(line1);
    }
    //cout<<"Done\n";
}

wxPanel *FavoriteList(wxBookCtrlBase *parent)
{
    // general setup
    wxPanel *panel = new wxPanel(parent);
    wxFont myAppFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    wxFont myAppFont2(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    wxFont subTextFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    panel->SetBackgroundColour(wxColour(249, 246, 246));

    wxScrolledWindow* lowpanel = new wxScrolledWindow(panel);
    /*
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create the subpanel and add it to the sizer

    wxPanel* scPanel=new wxPanel(panel);
    scPanel->SetSize(wxSize(3000,5000));
    scPanel->SetPosition(wxPoint(100,100));
    scPanel->SetBackgroundColour(wxColour(100,100,100));

    subpanel = new MyPanel(scPanel);
    sizer->Add(subpanel, 1, wxEXPAND);

    // Set the sizer for the main panel
    //scPanel->SetSizer(sizer);

    // Fit the main panel to the frame size
    sizer->Fit(scPanel);

    subpanel->build(favouriteList);
    subpanel->Layout();
    */
    wxBoxSizer* biggest = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* textArea = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* mergerScreen = new wxBoxSizer(wxHORIZONTAL);

    wxPanel* infoPanel = new wxPanel;
    infoPanel->SetBackgroundColour(wxColour(100,100,150));
    infoPanel->SetSizer(textArea);

    wxTextCtrl* infoText= new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    infoText->SetId(wxID_ANY);
    infoText->SetValue(wxEmptyString);
    infoText->SetPosition(wxDefaultPosition);
    infoText->SetSize(wxDefaultSize);
    /*
    wxTextAttr infoTextAttr;
    //infoTextAttr.SetTextColour(wxColor());
    infoTextAttr.SetFont();
    infoText->SetDefaultStyle(wxTE_PROCESS_ENTER|wxTE_READONLY|wxTE_MULTILINE);
    */

    // search area
    wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);

    wxSearchCtrl* searchBar = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, 25), wxTE_PROCESS_ENTER|wxTE_LEFT);
    searchBar->SetBackgroundColour(wxColour(200, 210, 209));

    wxWindowListNode* firstChild = searchBar->GetChildren().GetFirst();

    if (firstChild) {
        wxTextCtrl* textCtrl = wxDynamicCast(firstChild->GetData(), wxTextCtrl);
        if (textCtrl) {
            textCtrl->SetFont(myAppFont);
            textCtrl->SetForegroundColour(wxColour(142, 159, 157));
        }
        else {
            wxLogMessage("No data1");
        }
    }
    else {
        wxLogMessage("No firstChild");
    }

    wxBitmap search_ig = wxBitmap("search-25.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* searchButton = new wxBitmapButton(panel, wxID_ANY, search_ig, wxDefaultPosition, wxSize(25,25));

    searchButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event){
        wxString searchText = searchBar->GetValue();
        pSound(clickSound);
        //wxMessageBox("Searching for: " + searchText);
        searchFav(searchText,infoText);
    });
    sizer1->Add(searchBar, 0, wxLEFT, 5);
    sizer1->Add(searchButton, 0, wxLEFT);

    // result area, đoạn này chỉnh màu chưa đc :)
    wxPanel* base = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    base->SetBackgroundColour(wxColour(238, 238, 238));
    sizer1->Add(base);

    // ------------------------------------------------------------------ create one word item
    wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);
    lowpanel->SetVirtualSize(wxSize(200, 800));
    lowpanel->SetScrollRate(0, 10);
    lowpanel->SetSizer(sizer2);
    lowpanel->ShowScrollbars(wxSHOW_SB_DEFAULT,wxSHOW_SB_DEFAULT);
    mainPart=panel;
    panelt=lowpanel;
    sizer2t=sizer2;
    myAppFont2t=myAppFont2;
    targett=infoText;
    constructSc(panel,lowpanel,sizer2,myAppFont2,infoText);
    /*
    wxBoxSizer* wordInfo = new wxBoxSizer(wxVERTICAL);
    wxPanel* line1 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(530, 50));
    line1->SetBackgroundColour(wxColour(142, 159, 157));

    wxStaticText* wordName = new wxStaticText(line1, wxID_ANY,"Word number 1");
    //wxStaticText* wordDef = new wxStaticText(line1, wxID_ANY, "Definition goes here...");
    wordName->SetFont(myAppFont2);
   // wordDef->SetFont(subTextFont);
    wordName->SetForegroundColour(wxColour(73, 86, 111));
    //wordDef->SetForegroundColour(wxColour(73, 86, 111));
    // wordName->SetForegroundColour(wxColour(242, 224, 195));
    // wordDef->SetForegroundColour(wxColour(242, 224, 195));

    // chưa tìm đc cách bind cả wordInfo với event
    line1->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event){
        wxMessageBox(wxString::Format("Chose word: %s", wordName->GetLabel()), wxT("Message"));
    });

    wxBitmap favorited_ico = wxBitmap("favorited.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* removeFromFav = new wxBitmapButton(line1, wxID_ANY, favorited_ico, wxDefaultPosition, wxSize(30,30));

    wxBoxSizer* itemSizer = new wxBoxSizer(wxHORIZONTAL);

    wordInfo->Add(wordName, 20, wxALIGN_CENTRE, 5);
    //wordInfo->Add(wordDef, 0, wxLEFT, 5);
    itemSizer->Add(wordInfo, 20, wxALIGN_CENTRE, 5);
    itemSizer->AddStretchSpacer(1);
    itemSizer->Add(removeFromFav, 0, wxRIGHT|wxCENTRE);
    line1->SetSizer(itemSizer);
    sizer2->Add(line1);
    */
    // ------------------------------------------------------------------ create one word item

    //panel->GetSizer()->Detach(infoText);

    biggest->Add(sizer1, 0, wxEXPAND);
    biggest->AddSpacer(5);
    biggest->Add(lowpanel, wxEXPAND, wxEXPAND);
    mergerScreen->Add(biggest,0,wxEXPAND);
    //textArea->Add(infoText,0,wxEXPAND);
    //mergerScreen->Add(textArea,wxEXPAND,wxEXPAND);
    mergerScreen->Add(infoText,wxEXPAND,wxEXPAND);


    panel->SetSizer(mergerScreen);
    return panel;
}

string ans;
wxButton* questionButton;
wxButton* answerButton[5];
wxButton* refreshButton;
wxColor ButtonColour;

wxStaticText* ScoreText;

void makeGame(wxButton* _q,wxButton* _a[],string &_ans) {
    pair<string,string> p[5];
    int idx=rand()%4+1;
    for (int i=1;i<=4;i++) {
        p[i]=getRandomWord(data1,5);
        //p[i].first=standardize(p[i].first,500,5);
        //p[i].second=standardize(p[i].second,500,5);
    }
    _q->SetLabel(stringToWxString(p[idx].first));
    _a[1]->SetLabel(stringToWxString(p[1].second));
    _a[2]->SetLabel(stringToWxString(p[2].second));
    _a[3]->SetLabel(stringToWxString(p[3].second));
    _a[4]->SetLabel(stringToWxString(p[4].second));
    _ans=wxStringToString(stringToWxString(p[idx].second));
}

void makeGame() {
    for (int i=1;i<=4;i++) {
            //answerLabel[i]->Enable(false);
        //answerLabel[i]->SetBackgroundColour(ButtonColour);
        answerButton[i]->SetBackgroundColour(ButtonColour);
    }
    questionButton->SetBackgroundColour(ButtonColour);
    pair<string,string> p[5];
    int idx=rand()%4+1;
    for (int i=1;i<=4;i++) {
        p[i]=getRandomWord(data1,5);
        //p[i].first=standardize(p[i].first,500,5);
        //p[i].second=standardize(p[i].second,500,5);
    }
    questionButton->SetLabel(stringToWxString(p[idx].first));
    answerButton[1]->SetLabel(stringToWxString(p[1].second));
    answerButton[2]->SetLabel(stringToWxString(p[2].second));
    answerButton[3]->SetLabel(stringToWxString(p[3].second));
    answerButton[4]->SetLabel(stringToWxString(p[4].second));
    ans=wxStringToString(stringToWxString(p[idx].second));
}


void makeGameInv(wxButton* _q,wxButton* _a[],string &_ans) {
    pair<string,string> p[5];
    int idx=rand()%4+1;
    for (int i=1;i<=4;i++) {
        p[i]=getRandomWord(data1,5);
        swap(p[i].first,p[i].second);
    }
    questionButton->SetLabel(stringToWxString(p[idx].first));
    answerButton[1]->SetLabel(stringToWxString(p[1].second));
    answerButton[2]->SetLabel(stringToWxString(p[2].second));
    answerButton[3]->SetLabel(stringToWxString(p[3].second));
    answerButton[4]->SetLabel(stringToWxString(p[4].second));
    ans=wxStringToString(stringToWxString(p[idx].second));
}


void makeGameInv() {
    for (int i=1;i<=4;i++) {
            //answerLabel[i]->Enable(false);
        //answerLabel[i]->SetBackgroundColour(ButtonColour);
        answerButton[i]->SetBackgroundColour(ButtonColour);
    }
    questionButton->SetBackgroundColour(ButtonColour);
    pair<string,string> p[5];
    int idx=rand()%4+1;
    for (int i=1;i<=4;i++) {
        p[i]=getRandomWord(data1,5);
        swap(p[i].first,p[i].second);
    }
    questionButton->SetLabel(stringToWxString(p[idx].first));
    answerButton[1]->SetLabel(stringToWxString(p[1].second));
    answerButton[2]->SetLabel(stringToWxString(p[2].second));
    answerButton[3]->SetLabel(stringToWxString(p[3].second));
    answerButton[4]->SetLabel(stringToWxString(p[4].second));
    ans=wxStringToString(stringToWxString(p[idx].second));
}

void displayScore(int x) {
    if (x<-5) {
        ScoreText->SetLabel("Streak: Spanish");
    }
    else if (x<=0) {
        ScoreText->SetLabel("Streak: 0");
    }
    else if (x>=20) {
        ScoreText->SetLabel("Streak: Godlike");
    }
    else {
        ScoreText->SetLabel("Streak: "+intToString(x));
    }
}

wxWindow* CreateGamePage(wxBookCtrlBase* parent)
{
    //wxStaticText* questionLabel;
    //wxStaticText* answerLabel[5];

    //if (correctAnswer.Create("sound/correct.ogg")) cout<<"Sound 1 ok!\n";
    //if (wrongAnswer.Create("sound/wrong.ogg")) cout<<"Sound 2 ok!\n";

    mode=1;

    //Fuck all of these panelring fuckery
    //Just die


        // Tạo các thành phần giao diện
        wxPanel* panel = new wxPanel(parent, wxID_ANY);
        panel->SetBackgroundColour(wxColour("#c8d2d1"));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
        panel->SetSizerAndFit(mainSizer);

        ButtonColour=wxColor("#EAFBEA");

        wxSound testSound("sound/correct.ogg");
        /*
        answerLabel[1] = new wxStaticText(panel, wxID_ANY, wxEmptyString,wxPoint(1,1), wxSize(1,1),wxTE_READONLY|wxTE_CENTER|wxTE_MULTILINE);
        answerLabel[1]->SetSize(wxSize(586,130));
        answerLabel[1]->SetPosition(wxPoint(0,195));
        answerLabel[1]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));

        answerLabel[2] = new wxStaticText(panel, wxID_ANY, wxEmptyString,wxPoint(1,1), wxSize(1,1),wxTE_READONLY|wxTE_CENTER|wxTE_MULTILINE);
        answerLabel[2]->SetSize(wxSize(586,130));
        answerLabel[2]->SetPosition(wxPoint(586,195));
        answerLabel[2]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));

        answerLabel[3] = new wxStaticText(panel, wxID_ANY, wxEmptyString,wxPoint(1,1), wxSize(1,1),wxTE_READONLY|wxTE_CENTER|wxTE_MULTILINE);
        answerLabel[3]->SetSize(wxSize(586,130));
        answerLabel[3]->SetPosition(wxPoint(0,325));
        answerLabel[3]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));

        answerLabel[4] = new wxStaticText(panel, wxID_ANY, wxEmptyString,wxPoint(1,1), wxSize(1,1),wxTE_READONLY|wxTE_CENTER|wxTE_MULTILINE);
        answerLabel[4]->SetSize(wxSize(586,130));
        answerLabel[4]->SetPosition(wxPoint(586,325));
        answerLabel[4]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));

        questionLabel = new wxStaticText(panel, wxID_ANY, wxEmptyString,wxPoint(1,1), wxSize(1,1),wxTE_READONLY|wxTE_CENTER|wxTE_MULTILINE);
        questionLabel->SetSize(wxSize(1172,130));
        questionLabel->SetPosition(wxPoint(0,65));
        questionLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        questionLabel->SetBackgroundColour(ButtonColour);
        */

        answerButton[1] = new wxButton(panel, wxID_ANY);
        answerButton[1]->SetSize(wxSize(586,130));
        answerButton[1]->SetPosition(wxPoint(0,195));
        answerButton[1]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL|wxALIGN_CENTER|wxST_ELLIPSIZE_END, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        //answerButton[1]->SetMaxLines(5);

        answerButton[2] = new wxButton(panel, wxID_ANY);
        answerButton[2]->SetSize(wxSize(586,130));
        answerButton[2]->SetPosition(wxPoint(586,195));
        answerButton[2]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL|wxALIGN_CENTER|wxST_ELLIPSIZE_END, wxFONTWEIGHT_BOLD, false, "Montserrat"));

        answerButton[3] = new wxButton(panel, wxID_ANY);
        answerButton[3]->SetSize(wxSize(586,130));
        answerButton[3]->SetPosition(wxPoint(0,325));
        answerButton[3]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL|wxALIGN_CENTER|wxST_ELLIPSIZE_END, wxFONTWEIGHT_BOLD, false, "Montserrat"));

        answerButton[4] = new wxButton(panel, wxID_ANY);
        answerButton[4]->SetSize(wxSize(586,130));
        answerButton[4]->SetPosition(wxPoint(586,325));
        answerButton[4]->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL|wxALIGN_CENTER|wxST_ELLIPSIZE_END, wxFONTWEIGHT_BOLD, false, "Montserrat"));

        questionButton = new wxButton(panel, wxID_ANY);
        questionButton->SetSize(wxSize(1172,130));
        questionButton->SetPosition(wxPoint(0,65));
        questionButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL|wxALIGN_CENTER|wxST_ELLIPSIZE_END, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        /*
        for (int i=1;i<=4;i++) {
            //answerLabel[i]->Enable(false);
            answerLabel[i]->SetBackgroundColour(ButtonColour);
            answerButton[i]->SetBackgroundColour(ButtonColour);
        }
        questionButton->SetBackgroundColour(ButtonColour);
        */
        //questionButton->Enable(false);

        ScoreText = new wxStaticText(panel, wxID_ANY, wxEmptyString,wxPoint(1,1), wxSize(1,1),wxTE_READONLY|wxTE_CENTER|wxTE_MULTILINE);
        ScoreText->SetSize(wxSize(60,500));
        ScoreText->SetPosition(wxPoint(10,10));
        ScoreText->SetFont(wxFont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        point=0;
        displayScore(point);

        if (mode==1) {
            makeGame();
        }
        else {
            makeGameInv();
        }


        //lambdaFunc();
        //Stay away from lambda function for a healthy life

        answerButton[1]->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
        {
            {
                string tmp=wxStringToString(answerButton[1]->GetLabel());
                if (tmp==ans) {
                    answerButton[1]->SetBackgroundColour(wxColour("#49be25"));
                    point++;
                    pSound(correctAnswer);
                }
                else {
                    answerButton[1]->SetBackgroundColour(wxColour("#be4d25"));
                    point =0;
                    pSound(wrongAnswer);
                }
                displayScore(point);
                if (mode==1) {
                    makeGame();
                }
                else {
                    makeGameInv();
                }
                //wxSleep(2);
                //lambdaFunc();
            }
        });

        answerButton[2]->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
        {
            {
                string tmp=wxStringToString(answerButton[2]->GetLabel());
                if (tmp==ans) {
                    answerButton[2]->SetBackgroundColour(wxColour("#49be25"));
                    point++;
                    pSound(correctAnswer);
                }
                else {
                    answerButton[2]->SetBackgroundColour(wxColour("#be4d25"));
                    point =0;
                    pSound(wrongAnswer);
                }
                displayScore(point);
                if (mode==1) {
                    makeGame();
                }
                else {
                    makeGameInv();
                }
                //wxSleep(2);
                //lambdaFunc();
            }
        });

        answerButton[3]->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
        {
            {
                string tmp=wxStringToString(answerButton[3]->GetLabel());
                if (tmp==ans) {
                    answerButton[3]->SetBackgroundColour(wxColour("#49be25"));
                    point++;
                    pSound(correctAnswer);
                }
                else {
                    answerButton[3]->SetBackgroundColour(wxColour("#be4d25"));
                    point =0;
                    pSound(wrongAnswer);
                }
                displayScore(point);
                if (mode==1) {
                    makeGame();
                }
                else {
                    makeGameInv();
                }
                //wxSleep(2);
                //lambdaFunc();
            }
        });

        answerButton[4]->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
        {
            {
                string tmp=wxStringToString(answerButton[4]->GetLabel());
                if (tmp==ans) {
                    answerButton[4]->SetBackgroundColour(wxColour("#49be25"));
                    point++;
                    pSound(correctAnswer);
                }
                else {
                    answerButton[4]->SetBackgroundColour(wxColour("#be4d25"));
                    point =0;
                    pSound(wrongAnswer);
                }
                displayScore(point);
                if (mode==1) {
                    makeGame();
                }
                else {
                    makeGameInv();
                }
                //wxSleep(2);
                //lambdaFunc();
            }
        });

        testSound.Play(wxSOUND_LOOP|wxSOUND_ASYNC);

        questionButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
        {
            {
                pSound(clickSound);
                if (mode==2) mode=1;
                else mode=2;
                point=0;
                displayScore(point);
                if (mode==1) {
                    makeGame();
                }
                else {
                    makeGameInv();
                }
            }
        });

        //1172 455
        //0 65
        //1172/2=586
        //390 below

    /*
        // Panel bên trái để chọn chế độ chơi
        wxPanel* modePanel = new wxPanel(panel, wxID_ANY);
        wxBoxSizer* modeSizer = new wxBoxSizer(wxVERTICAL);
        modePanel->SetSizerAndFit(modeSizer);


        wxStaticText* gameModeText = new wxStaticText(modePanel, wxID_ANY, "choose mode     ");
        gameModeText->SetFont(wxFont(34, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        gameModeText->SetForegroundColour(wxColour("#49566f"));
        modeSizer->Add(gameModeText, 0, wxALIGN_CENTER | wxTOP, 60);

        wxButton* guessWordbutton = new wxButton(modePanel, wxID_ANY, "guess word from definition");
        guessWordbutton->SetForegroundColour(wxColour("#49566f"));
        guessWordbutton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        guessWordbutton->SetBackgroundColour(wxColour("#f2e0c3"));
        modeSizer->Add(guessWordbutton, 0, wxALIGN_LEFT  | wxTOP, 30);

        wxButton* guessdefinition = new wxButton(modePanel, wxID_ANY, "guess definition from word");
        guessdefinition->SetForegroundColour(wxColour("#49566f"));
        guessdefinition->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        guessdefinition->SetBackgroundColour(wxColour("#f2e0c3"));
        modeSizer->Add(guessdefinition, 0, wxALIGN_LEFT  | wxTOP, 15);


        // Panel bên phải để hiển thị câu hỏi và đáp án
        wxPanel* gamePanel = new wxPanel(panel, wxID_ANY);
        wxBoxSizer* gameSizer = new wxBoxSizer(wxVERTICAL);
        gamePanel->SetSizer(gameSizer);

        refreshButton = new wxButton(gamePanel, wxID_ANY, "Refresh");
        refreshButton->SetForegroundColour(wxColour("#49566f"));
        refreshButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat"));
        refreshButton->SetBackgroundColour(wxColour("#f2e0c3"));
        refreshButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
            {
                {
                    wxMessageBox("Game has been reset.");
                }
            });

        questionLabel = new wxStaticText(gamePanel, wxID_ANY, "Question");
        gameSizer->Add(questionLabel, 0, wxALIGN_CENTER | wxTOP, 80);
        questionLabel->SetForegroundColour(wxColour("#49566f"));
        questionLabel->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));


        answerButton1 = new wxButton(gamePanel, wxID_ANY, "Answer 1");
        answerButton1->SetForegroundColour(wxColour("#49566f"));
        answerButton1->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        answerButton1->SetBackgroundColour(wxColour("#f2e0c3"));
        answerButton1->SetSize(wxSize(300, 30));
        //wxButton (wxWindow *parent, wxWindowID id, const wxString &label=wxEmptyString,
        //const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize,
        //long style=0, const wxValidator &validator=wxDefaultValidator,
        //const wxString &name=wxButtonNameStr)


        //answerButton1 = new wxButton(gamePanel, wxID_ANY, "Answer 1",wxDefaultPosition,wxDefaultSize);

        answerButton2 = new wxButton(gamePanel, wxID_ANY, "Answer 2");
        answerButton2->SetForegroundColour(wxColour("#49566f"));
        answerButton2->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        answerButton2->SetBackgroundColour(wxColour("#f2e0c3"));

        answerButton3 = new wxButton(gamePanel, wxID_ANY, "Answer 3");
        answerButton3->SetForegroundColour(wxColour("#49566f"));
        answerButton3->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        answerButton3->SetBackgroundColour(wxColour("#f2e0c3"));

        answerButton4 = new wxButton(gamePanel, wxID_ANY, "Answer 4");
        answerButton4->SetForegroundColour(wxColour("#49566f"));
        answerButton4->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));
        answerButton4->SetBackgroundColour(wxColour("#f2e0c3"));

        wxBoxSizer* refreshSizer = new wxBoxSizer(wxHORIZONTAL);

        refreshSizer->Add(refreshButton, 0, wxALIGN_LEFT | wxTOP, 10);

        gameSizer->Add(answerButton1, 0, wxALIGN_CENTER | wxALL, 10);
        gameSizer->Add(answerButton2, 0, wxALIGN_CENTER | wxALL, 10);
        gameSizer->Add(answerButton3, 0, wxALIGN_CENTER | wxALL, 10);
        gameSizer->Add(answerButton4, 0, wxALIGN_CENTER | wxALL, 10);

        gameSizer->Add(refreshSizer, 1, wxEXPAND);

        mainSizer->Add(modePanel, 1, wxEXPAND);
        mainSizer->Add(gamePanel, 2, wxEXPAND);


        guessWordbutton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
            {
                pair<string,string> p[5];
                int idx=rand()%4+1;
                for (int i=1;i<=4;i++) {
                    p[i]=getRandomWord(data1);
                }
                questionLabel->SetLabel("What is the definition of '"+p[idx].first+"'?");
                answerButton1->SetLabel(p[1].second);
                answerButton2->SetLabel(p[2].second);
                answerButton3->SetLabel(p[3].second);
                answerButton4->SetLabel(p[4].second);

                cout<<p[1].first<<' '<<p[1].second<<'\n';
                cout<<p[2].first<<' '<<p[2].second<<'\n';
                cout<<p[3].first<<' '<<p[3].second<<'\n';
                cout<<p[4].first<<' '<<p[4].second<<'\n';

                // Kết nối sự kiện chọn đáp án
                answerButton1->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }

                    });

                answerButton2->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }
                    });
                answerButton3->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }
                    });
                answerButton4->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }
                    });
            });
        guessdefinition->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
            {
                questionLabel->SetLabel("What is the word for 'a sweet, red fruit'?");
                answerButton1->SetLabel("Orange");
                answerButton2->SetLabel("Banana");
                answerButton3->SetLabel("Strawberry");
                answerButton4->SetLabel("Watermelon");

                // Kết nối sự kiện chọn đáp án
                answerButton1->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }
                    });

                answerButton2->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }
                    });
                answerButton3->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }
                    });
                answerButton4->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                    {
                        wxButton* answerButton = dynamic_cast<wxButton*>(event.GetEventObject());
                        if (answerButton) {
                            wxString answer = answerButton->GetLabel();
                            wxMessageBox("Your answer: " + answer, "Answer", wxOK | wxICON_INFORMATION);
                        }
                    });
            });
    */
        return panel;
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

    parent->SetSize(wxSize(70,680));

    wxWindow *page = DictionaryPage(parent);
    parent->InsertPage( 0, page, wxEmptyString, false, GetIconIndex(parent) );

    page = CreateAddPage(parent);
    parent->AddPage( page, wxEmptyString, false, GetIconIndex(parent) );

    page = FavoriteList(parent);
    parent->AddPage( page, wxEmptyString, false, GetIconIndex(parent) );

    page = CreateGamePage(parent);
    parent->AddPage( page, wxEmptyString, false, GetIconIndex(parent) );

    parent->SetSelection(0);
}

wxWindow *CreatePage(wxBookCtrlBase *parent, const wxString&pageName)
{
    if ( pageName == DICTIONARY ) {
        return DictionaryPage(parent);
        wxMessageBox("aaaaaaaaaaaaaaaaaaaaaxxxxxxxxaa");
    }
    if ( pageName == FAVOURITE_LIST ) {
        //pSound("click.wav");
        wxMessageBox("aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbb");
        return FavoriteList(parent);
    }
    if ( pageName == ADD_NEW_WORD ) {
        //pSound("click.wav");
        wxMessageBox("aaaaaaaaaaaaaaaaaaaaaasssssssa");
        return CreateAddPage(parent);
    }
    if ( pageName == GAME ) {
        //pSound("click.wav");
        wxMessageBox("aaaaaaaaaaaaaaaaaaaaaaa");
        return CreateGamePage(parent);
    }
    wxFAIL_MSG( "unknown page name" );

    return NULL;
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, MyFrame::OnNotebook)
EVT_NOTEBOOK_PAGE_CHANGING(wxID_ANY, MyFrame::OnNotebook)
wxEND_EVENT_TABLE()

MyFrame::MyFrame()
: wxFrame(NULL, wxID_ANY, wxString("Dictionary"),wxPoint(wxID_ANY, wxID_ANY), wxSize(1200, 680),
          wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{

    //m_type = Type_Notebook;
    this->SetBackgroundColour(wxColour(73, 86, 111));
    m_panel    = NULL;
    m_bookCtrl = NULL;
    m_chkShowImages = true;

    ::wxInitAllImageHandlers();
    wxBitmap dict("dict_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap add("add_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap fav("favorite_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap game("game_unclicked.png", wxBITMAP_TYPE_ANY);

    m_images.push_back(dict);
    m_images.push_back(add);
    m_images.push_back(fav);
    m_images.push_back(game);

    m_panel = new wxPanel(this);

    m_text = new wxStaticText(m_panel, wxID_ANY, username);
    m_text->SetForegroundColour(*wxYELLOW);

    wxBitmap reset_ico = wxBitmap("reset_unclicked.png", wxBITMAP_TYPE_ANY);
    m_reset = new wxBitmapButton(m_panel, wxID_ANY, reset_ico, wxDefaultPosition, wxSize(25,25));
    m_reset->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        //reset function of Cuong

        //resetAll();

        wxLogMessage("Your data has been reset.");
    });

    wxBitmap logout_ico = wxBitmap("logout_unclicked.png", wxBITMAP_TYPE_ANY);
    m_logout = new wxBitmapButton(m_panel, wxID_ANY, logout_ico, wxDefaultPosition, wxSize(25,25));
    m_logout->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        //reset function of Cuong
        username="username";
        userID=0;
        this->Close();

        FormLogin* login = new FormLogin("Login");
        login->Show(true);
    });

    m_sizerFrame = new wxBoxSizer(wxVERTICAL);
    // m_sizerFrame->Add(m_text, 1, wxEXPAND);
    m_sizerFrame->Add(m_reset,0);
    m_sizerFrame->Add(m_logout,0);

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
#define CASE_NOTEBOOK(x) case Type_Notebook: x; break;
#else
#define CASE_NOTEBOOK(x)
#endif

#define DISPATCH_ON_TYPE(before, aui, after)\
switch ( m_type )                                         \
{                                                      \
CASE_NOTEBOOK(before aui after) \
\
\
default:                                \
wxFAIL_MSG( "unknown book control type" );\
}

void MyFrame::RecreateBook(int idx)
{
    // m_bookCtrl = NULL;

    // DISPATCH_ON_TYPE(m_bookCtrl = new, wxNotebook,
    //                  (m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize));

    // if ( !m_bookCtrl )
    //     return;
    pSound(wrongAnswer);
    wxNotebook* functionBar = new wxNotebook(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT);
    functionBar->SetBackgroundColour(wxColour(73, 86, 111));

    // m_bookCtrl->Hide();

    if ( m_chkShowImages ) {
        functionBar->SetImages(m_images);
    }

    CreateInitialPages(functionBar,idx);

    m_sizerFrame->Insert(0, functionBar, wxSizerFlags(5).Expand());

    // m_sizerFrame->Show(m_bookCtrl);
    m_sizerFrame->Layout();
}


void MyFrame::RecreateBook()
{
    // m_bookCtrl = NULL;

    // DISPATCH_ON_TYPE(m_bookCtrl = new, wxNotebook,
    //                  (m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize));

    // if ( !m_bookCtrl )
    //     return;
    pSound(wrongAnswer);
    wxNotebook* functionBar = new wxNotebook(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT);
    functionBar->SetBackgroundColour(wxColour(73, 86, 111));

    // m_bookCtrl->Hide();

    if ( m_chkShowImages ) {
        functionBar->SetImages(m_images);
    }

    CreateInitialPages(functionBar);

    m_sizerFrame->Insert(0, functionBar, wxSizerFlags(5).Expand());

    // m_sizerFrame->Show(m_bookCtrl);
    m_sizerFrame->Layout();
}

void MyFrame::OnShowImages(wxCommandEvent& event)
{
    return;
    m_chkShowImages = event.IsChecked();
    RecreateBook();
    pSound(clickSound);
    m_sizerFrame->Layout();
}


//replace file path at line 1429
void MyFrame::OnBookCtrl(wxBookCtrlBaseEvent& event)
{
    //return;
    pSound(clickSound);
    static const struct EventInfo
    {
        wxEventType typeChanged,
                    typeChanging;
        const wxString name;
    } events[] =
    {
/*
#if wxUSE_AUI
        {
            wxEVT_NOTEBOOK_PAGE_CHANGED,
            wxEVT_NOTEBOOK_PAGE_CHANGING,
            "wxNotebook"
        },
#endif
*/
    };

    //pSound(clickSound);
    wxString nameEvent,
             nameControl,
             veto;
    const wxEventType eventType = event.GetEventType();
    const wxBookCtrlBase * const
        book = static_cast<wxBookCtrlBase *>(event.GetEventObject());

    for ( size_t n = 0; n < WXSIZEOF(events); n++ )
    {
        const EventInfo& ei = events[n];
        if ( eventType == ei.typeChanged )
        {
            pSound(clickSound);
            //cout<<"Fuck\n";
            nameEvent = "Changed";
        }
        else if ( eventType == ei.typeChanging )
        {
            //pSound(clickSound);
            const int idx = event.GetOldSelection();

            if (idx != wxNOT_FOUND &&
                book){
                //wxMessageBox("aaaaaaaaaaaaaaaaaaaaaaa");
                pSound(clickSound);
                m_tabChangeSound.Play("sound/click.wav", wxSOUND_ASYNC);
            }
            //wxMessageBox("aaaaaaaaaaaaaaaaaaaaaaa");
            nameEvent = "Changing";
        }
        else // skip end of the loop
        {
            //pSound(clickSound);
            continue;
        }

        nameControl = ei.name;
        break;
    }

}
