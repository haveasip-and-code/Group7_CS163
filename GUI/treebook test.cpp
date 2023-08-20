//
//  treebook test.cpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 31/07/2023.
//

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

wxString curWord;
wxString curDef;

extern int dataSetCnt;
extern int curDataSet;

extern vector<pair<string,string>> favouriteList;
extern vector<pair<string,string>> historyList;

extern TST data;

bool isEditable;

vector<string> inputRegex;

wxPanel *DictionaryPage(wxBookCtrlBase *parent)
{

    wxPanel *panel = new wxPanel(parent);
    wxFont myAppFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");

    panel->SetBackgroundColour(wxColour(248, 247, 245));
    ::wxInitAllImageHandlers();

    wxBoxSizer* all_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    wxChoice* chooseMode = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(110, 25));

    wxArrayString modeChoices;
    modeChoices.Add("By keyword");
    modeChoices.Add("By definition");
    chooseMode->Set(modeChoices);
    chooseMode->SetFont(myAppFont);

    chooseMode->SetSelection(0);
    mode=1;
    cmd=1;

    chooseMode->Bind(wxEVT_CHOICE, [=](wxCommandEvent& event){
        wxString selectedText = chooseMode->GetStringSelection();
        //wxLogMessage("Selected: %s", selectedText);
        if (selectedText=="By keyword") mode=1;
        else mode=2;
    });

    wxSearchCtrl* searchBar = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, 25), wxTE_PROCESS_ENTER|wxTE_LEFT);
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

    wxTextCtrl* word = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(200,-1), wxTE_PROCESS_ENTER|wxTE_READONLY/*|wxTE_CENTER*/);
    word->SetHint("Word");

    wxTextCtrl* definition = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(800,300), wxTE_PROCESS_ENTER|wxTE_READONLY/*|wxTE_CENTER*/|wxTE_MULTILINE);
    //definition->SetScrollbar(wxVERTICAL, 0, 0, 0);
    definition->SetHint("definition");
    definition->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Montserrat"));


    isEditable=false;
    word->SetEditable(isEditable);
    definition->SetEditable(isEditable);

    wxBitmap search_ig = wxBitmap("search-25.png", wxBITMAP_TYPE_ANY);

    wxBitmapButton* searchButton = new wxBitmapButton(panel, wxID_ANY, search_ig, wxDefaultPosition, wxSize(25,25));
    searchButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        wxString searchText = searchBar->GetValue();
        //wxMessageBox("Searching for: " + searchText);
        //wxMessageBox(getPath(1));
        string tmp=wxStringToString(searchText);
        //string testStr="make";
        //cout<<data.get(testStr)->val<<' '<<tmp<<'\n';
        if (mode==1) {
            pair<string,string> searchResult=getWordDefAlways(data,tmp);
            curDef=stringToWxString(searchResult.second);
            curWord=stringToWxString(searchResult.first);
            //cout<<curDef<<' '<<curWord<<'\n';
            //wxMessageBox(curWord+" "+curDef);
            //definition->ChangeValue("To hell with wxWidgets");
            word->ChangeValue(curWord);
            definition->ChangeValue(curDef);
        }
        else {
            factor=1;
            deltaPos=0;
            transformDef(tmp,inputRegex);
            cout<<searchDef(cmd,deltaPos,inputRegex,inputRegex.size()/factor);
            pair<string,string> searchResult=retrieveData(curDataSet,searchDef(cmd,deltaPos,inputRegex,inputRegex.size()/factor));
            curDef=stringToWxString(searchResult.second);
            curWord=stringToWxString(searchResult.first);
            //cout<<curDef<<' '<<curWord<<'\n';
            //wxMessageBox(curWord+" "+curDef);
            //definition->ChangeValue("To hell with wxWidgets");
            word->ChangeValue(curWord);
            definition->ChangeValue(curDef);
        }
    });

    sizer->Add(chooseMode, 0, wxLEFT);
    sizer->Add(searchBar, 0);
    sizer->Add(searchButton,0, wxLEFT);

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);

    //wxTextCtrl* pronounciation = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,wxDefaultPosition, wxSize(200,-1), wxTE_READONLY|wxTE_CENTER);
    //pronounciation->SetHint("Pronunciation");
    sizer2->Add(word,0, wxLEFT, 30);
    //sizer2->Add(pronounciation,0, wxLEFT, 10);

    wxBoxSizer* sizer4 = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxBitmap unedit_ico = wxBitmap("edit_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap edit_ico = wxBitmap("edit_clicked.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* m_edit = new wxBitmapButton(panel, wxID_ANY, edit_ico, wxDefaultPosition, wxSize(30,30));
    //wxBitmapButton* m_edit = new wxBitmapButton(panel, wxID_ANY, edit_ico, wxDefaultPosition);
    //m_edit->SetSize(wxSize(30, 30));
    m_edit->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                 {

            static bool notEdit = true;
            wxBitmap statusBitmap = notEdit ? edit_ico : unedit_ico;
            m_edit->SetBitmapLabel(statusBitmap);
            panel->Layout();
            notEdit = !notEdit;
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
            addWord(data,tmp1,tmp2);
            saveCurrentDataSet(data);
            //cout<<tmp1<<' '<<tmp2<<' '<<word->GetValue()<<' '<<definition->GetValue()<<'\n';
        }
        else {

        }
        isEditable=!isEditable;
    });
    wxBitmapButton* m_remove = new wxBitmapButton(panel, wxID_ANY, wxArtProvider::GetBitmap(wxART_DELETE), wxDefaultPosition, wxSize(30,30));
    m_remove->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                   {

        //Function cua Cuong
        //wxLogMessage("This word has been removed!");
        //pronounciation->Clear();
        string tmp1,tmp2;
        tmp1=wxStringToString(word->GetValue());
        tmp2="";
        //cout<<"Yes\n";
        addWord(data,tmp1,tmp2);
        saveCurrentDataSet(data);
        word->Clear();
        definition->Clear();
        word->SetHint("Word");
        definition->SetHint("definition");
    });

    wxBitmap unfavorited_ico = wxBitmap("unfavorited.png", wxBITMAP_TYPE_ANY);
    wxBitmap favorited_ico = wxBitmap("favorited.png", wxBITMAP_TYPE_ANY);

    wxBitmapButton* m_favourite = new wxBitmapButton(panel, wxID_ANY, unfavorited_ico, wxDefaultPosition, wxSize(30,30));
    bool notFavorite = true;
    if (true/*isFavorite(word)*/) {
        notFavorite=false;
    }
    else {
        notFavorite=true;
    }

    m_favourite->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        wxBitmap statusBitmap = notFavorite ? favorited_ico : unfavorited_ico;
        m_favourite->SetBitmapLabel(statusBitmap);
        m_favourite->SetSize(wxSize(30,30));
        panel->Layout();
        //notFavorite = !notFavorite;
        if (notFavorite) {
            string tmp1,tmp2;
            tmp1=wxStringToString(word->GetValue());
            tmp2="";
            //addWordFavorite(favor,tmp1,tmp2);
        }
        else {
            string tmp1,tmp2;
            tmp1=wxStringToString(word->GetValue());
            tmp2=wxStringToString(definition->GetValue());
            //addWordFavorite(favor,tmp1,tmp2);
        }
    });

    sizer3->Add(m_remove,0);

    sizer3->Add(m_edit,0);
    sizer3->Add(m_favourite, 0, wxLEFT, 5);

    wxBoxSizer* sizer5 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* sizer6 = new wxBoxSizer(wxHORIZONTAL);

    wxBitmap unDataSet_ico = wxBitmap("DataSet_unchoose.png", wxBITMAP_TYPE_ANY);
    wxBitmap DataSet_ico = wxBitmap("DataSet_choose.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* m_dataset = new wxBitmapButton(panel, wxID_ANY, unDataSet_ico, wxDefaultPosition, wxSize(50, 50));


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
        else if (selectedText=="Emoji - Vie") cmd=4;
        else if (selectedText=="Emoji - Eng") cmd=5;
        else if (selectedText=="Eng slangs") cmd=6;
        else if (selectedText=="Vie slangs") cmd=7;
        saveCurrentDataSet(data);
        curDataSet=cmd;
        setStartSlot(getCurrentStartSlot());
        data.loadFromFile(getPath(cmd));
        //wxLogMessage("Selected: %s", selectedText);
        //wxLogMessage("Load data set "+selectedText);
    });

    wxBitmap unwotd_ico = wxBitmap("wotd_unclicked.png", wxBITMAP_TYPE_ANY);
    wxBitmap wotd_ico = wxBitmap("wotd_clicked.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* m_wordOfDay = new wxBitmapButton(panel, wxID_ANY, unwotd_ico, wxDefaultPosition, wxSize(50, 50));

    m_wordOfDay->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
            static bool notWotd = true;
            wxBitmap statusBitmap = notWotd ? wotd_ico : unwotd_ico;
            m_wordOfDay->SetBitmapLabel(statusBitmap);
            m_wordOfDay->SetSize(wxSize(50, 50));
            panel->Layout();
            notWotd = !notWotd;

             pair<string,string> searchResult=getRandomWord(data);
        curDef=stringToWxString(searchResult.second);
        curWord=stringToWxString(searchResult.first);
        word->ChangeValue(curWord);
        definition->ChangeValue(curDef);
    });

    sizer5->Add(m_wordOfDay, 0);
    sizer5->AddSpacer(5);

    sizer6->Add(chooseDataSet, 0, wxRIGHT, 5);
    sizer6->Add(m_dataset, 0, wxRIGHT, 5);

    sizer4->Add(sizer2,0);
    sizer4->AddSpacer(300);
    sizer4->Add(sizer3,0);

    all_sizer->Add(sizer,0);
    all_sizer->Add(sizer4,0);
    all_sizer->Add(definition,0);
    all_sizer->Add(sizer5, 0, wxALIGN_RIGHT);
    all_sizer->Add(sizer6, 0, wxALIGN_RIGHT);
    panel->SetSizer(all_sizer);

    return panel;
}

wxPanel *CreateAddPage(wxBookCtrlBase *parent)
{
    wxPanel *panel = new wxPanel(parent);

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
    return panel;
}

wxPanel *FavoriteList(wxBookCtrlBase *parent)
{
    // general setup
    wxPanel *panel = new wxPanel(parent);
    wxFont myAppFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    wxFont subTextFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Montserrat Medium");
    panel->SetBackgroundColour(wxColour(249, 246, 246));

    wxBoxSizer* biggest = new wxBoxSizer(wxVERTICAL);

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
            wxLogMessage("No data");
        }
    }
    else {
        wxLogMessage("No firstChild");
    }

    wxBitmap search_ig = wxBitmap("search-25.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* searchButton = new wxBitmapButton(panel, wxID_ANY, search_ig, wxDefaultPosition, wxSize(25,25));

    searchButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event){
        wxString searchText = searchBar->GetValue();
        wxMessageBox("Searching for: " + searchText);
    });

    sizer1->Add(searchBar, 0, wxLEFT, 5);
    sizer1->Add(searchButton, 0, wxLEFT);

    // result area, đoạn này chỉnh màu chưa đc :)
    wxPanel* base = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    base->SetBackgroundColour(wxColour(238, 238, 238));
    sizer1->Add(base);

    // ------------------------------------------------------------------ create one word item
    wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* wordInfo = new wxBoxSizer(wxVERTICAL);
    wxPanel* line1 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(530, 50));
    // line1->SetBackgroundColour(wxColour(142, 159, 157));

    wxStaticText* wordName = new wxStaticText(line1, wxID_ANY, "Word number 1");
    wxStaticText* wordDef = new wxStaticText(line1, wxID_ANY, "Definition goes here...");
    wordName->SetFont(myAppFont);
    wordDef->SetFont(subTextFont);
    wordName->SetForegroundColour(wxColour(73, 86, 111));
    wordDef->SetForegroundColour(wxColour(73, 86, 111));
    // wordName->SetForegroundColour(wxColour(242, 224, 195));
    // wordDef->SetForegroundColour(wxColour(242, 224, 195));

    // chưa tìm đc cách bind cả wordInfo với event
    line1->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event){
        wxMessageBox(wxString::Format("Chose word: %s", wordName->GetLabel()), wxT("Message"));
    });

    wxBitmap favorited_ico = wxBitmap("favorited.png", wxBITMAP_TYPE_ANY);
    wxBitmapButton* removeFromFav = new wxBitmapButton(line1, wxID_ANY, favorited_ico, wxDefaultPosition, wxSize(30,30));

    wxBoxSizer* itemSizer = new wxBoxSizer(wxHORIZONTAL);

    wordInfo->Add(wordName, 0, wxLEFT, 5);
    wordInfo->Add(wordDef, 0, wxLEFT, 5);
    itemSizer->Add(wordInfo, 0, wxLEFT, 5);
    itemSizer->AddStretchSpacer(1);
    itemSizer->Add(removeFromFav, 0, wxRIGHT);
    line1->SetSizer(itemSizer);
    sizer2->Add(line1);
    // ------------------------------------------------------------------ create one word item

    biggest->Add(sizer1, 0, wxEXPAND);
    biggest->AddSpacer(5);
    biggest->Add(sizer2, 0, wxEXPAND);
    panel->SetSizer(biggest);

    return panel;
}

string ans;
wxButton* questionButton;
wxButton* answerButton[5];
wxButton* refreshButton;

void makeGame(wxButton* _q,wxButton* _a[],string &_ans) {
    pair<string,string> p[5];
    int idx=rand()%4+1;
    for (int i=1;i<=4;i++) {
        p[i]=getRandomWord(data,5);
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
    pair<string,string> p[5];
    int idx=rand()%4+1;
    for (int i=1;i<=4;i++) {
        p[i]=getRandomWord(data,5);
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
        p[i]=getRandomWord(data,5);
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
    pair<string,string> p[5];
    int idx=rand()%4+1;
    for (int i=1;i<=4;i++) {
        p[i]=getRandomWord(data,5);
        swap(p[i].first,p[i].second);
    }
    questionButton->SetLabel(stringToWxString(p[idx].first));
    answerButton[1]->SetLabel(stringToWxString(p[1].second));
    answerButton[2]->SetLabel(stringToWxString(p[2].second));
    answerButton[3]->SetLabel(stringToWxString(p[3].second));
    answerButton[4]->SetLabel(stringToWxString(p[4].second));
    ans=wxStringToString(stringToWxString(p[idx].second));
}

wxWindow* CreateGamePage(wxBookCtrlBase* parent)
{
    //wxStaticText* questionLabel;
    //wxStaticText* answerLabel[5];

    int mode=1;

    //Fuck all of these panelring fuckery
    //Just die


        // Tạo các thành phần giao diện
        wxPanel* panel = new wxPanel(parent, wxID_ANY);
        panel->SetBackgroundColour(wxColour("#c8d2d1"));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
        panel->SetSizerAndFit(mainSizer);

        wxColor ButtonColour("#EAFBEA");
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

                }
                else {
                    answerButton[1]->SetBackgroundColour(wxColour("#be4d25"));
                }
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
                }
                else {
                    answerButton[2]->SetBackgroundColour(wxColour("#be4d25"));
                }
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

                }
                else {
                    answerButton[3]->SetBackgroundColour(wxColour("#be4d25"));
                }
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

                }
                else {
                    answerButton[4]->SetBackgroundColour(wxColour("#be4d25"));
                }
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
                    p[i]=getRandomWord(data);
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

    parent->SetSize(wxSize(100,400));

    wxWindow *page = DictionaryPage(parent);
    parent->InsertPage( 0, page, DICTIONARY, false, GetIconIndex(parent) );

    page = CreateAddPage(parent);
    parent->AddPage( page, ADD_NEW_WORD, false, GetIconIndex(parent) );

    page = FavoriteList(parent);
    parent->AddPage( page, FAVOURITE_LIST, false, GetIconIndex(parent) );

    page = CreateGamePage(parent);
    parent->AddPage( page, GAME, false, GetIconIndex(parent) );

    parent->SetSelection(0);
}

wxWindow *CreatePage(wxBookCtrlBase *parent, const wxString&pageName)
{
    if ( pageName == DICTIONARY )
        return DictionaryPage(parent);

    if ( pageName == FAVOURITE_LIST )
        return FavoriteList(parent);

    if ( pageName == ADD_NEW_WORD )
        return CreateAddPage(parent);

    if ( pageName == GAME )
        return CreateGamePage(parent);

    wxFAIL_MSG( "unknown page name" );

    return NULL;
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_ANY, MyFrame::OnAuiNotebook)
EVT_AUINOTEBOOK_PAGE_CHANGING(wxID_ANY, MyFrame::OnAuiNotebook)
wxEND_EVENT_TABLE()

MyFrame::MyFrame()
: wxFrame(NULL, wxID_ANY, wxString("Dictionary"),wxPoint(wxID_ANY, wxID_ANY), wxSize(1200, 680),
          wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{

    m_type = Type_AuiNotebook;
    this->SetBackgroundColour(wxColour(73,86,111));
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

    m_text = new wxStaticText(m_panel, wxID_ANY, "Username");
    m_text->SetForegroundColour(*wxGREEN);
    wxBitmap reset_ico = wxBitmap("reset_unclicked.png", wxBITMAP_TYPE_ANY);
    m_reset = new wxBitmapButton(m_panel, wxID_ANY, reset_ico, wxDefaultPosition, wxSize(25,25));
    m_reset->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        //reset function of Cuong

        wxLogMessage("Your data has been reset");
    });

    wxBitmap logout_ico = wxBitmap("logout_unclicked.png", wxBITMAP_TYPE_ANY);
    m_logout = new wxBitmapButton(m_panel, wxID_ANY, logout_ico, wxDefaultPosition, wxSize(25,25));
    m_logout->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event)
                       {
        //reset function of Cuong

        this->Close();

        FormLogin* login = new FormLogin("Login");
        login->Show(true);
    });

    m_sizerFrame = new wxBoxSizer(wxVERTICAL);
    m_sizerFrame->Add(m_text, 1, wxEXPAND);
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
}
