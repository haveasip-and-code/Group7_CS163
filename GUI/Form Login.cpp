//
//  Form Login.cpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 23/07/2023.
//

#include "Form Login.hpp"
#include "treebook test.hpp"

FormLogin::FormLogin(const wxString& title)
: wxFrame((wxFrame *) NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY), wxSize(1200, 680),
wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    panel = new wxPanel(this, wxID_ANY);

    ::wxInitAllImageHandlers();

    // Try to load the image.
    m_image = wxImage("login5.png", wxBITMAP_TYPE_ANY);
    if ( !m_image.IsOk() )
    {
        return;
    }
    CreateScaledBg();
    
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    m_usernameEntry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30), wxTE_PROCESS_ENTER);
    m_usernameEntry->SetHint("Username");
    //m_usernameEntry->SetBackgroundStyle( wxBG_STYLE_COLOUR );
    m_usernameEntry->SetBackgroundColour(wxColour(242, 225, 195) );

    wxFont myAppFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false, "Montserrat");
    m_usernameEntry->SetFont(myAppFont);

    hbox1->AddStretchSpacer(1);
    hbox1->Add(m_usernameEntry, 0, wxALIGN_CENTRE | wxTOP, 50);
    
    
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    m_passwordEntry = new wxTextCtrl(panel, wxID_ANY, wxString(""), wxDefaultPosition, wxSize(300, 30), wxTE_PASSWORD|wxTE_PROCESS_ENTER);
    m_passwordEntry->SetHint("Password");
    m_passwordEntry->SetFont(myAppFont);
    hbox2->AddStretchSpacer(1);
    hbox2->Add(m_passwordEntry, 0, wxALIGN_CENTER|wxBOTTOM|wxTOP, 5);

    wxBoxSizer *vbox_middle = new wxBoxSizer(wxVERTICAL);
    vbox_middle->AddStretchSpacer(1);
    vbox_middle->Add(hbox1, 0, wxALIGN_CENTER_HORIZONTAL);
    vbox_middle->Add(hbox2, 0, wxALIGN_CENTER_HORIZONTAL);
    
    wxBoxSizer *vbox_above_middle = new wxBoxSizer(wxHORIZONTAL);
    vbox_above_middle->AddStretchSpacer(1);
    
    // Add "Sign Up" button
    wxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    m_buttonSignUp = new wxButton(panel, BUTTON_SignUp, "Sign Up");
    m_buttonSignUp->SetFont(myAppFont);
    hbox3->Add(m_buttonSignUp, 0, wxRIGHT, 130);

    m_buttonLogin = new wxButton(panel, BUTTON_Login, wxT("Login"));
    m_buttonLogin->SetFont(myAppFont);
    m_buttonLogin->SetForegroundColour(*wxRED);
    hbox3->Add(m_buttonLogin, 0);
    
    vbox_middle->Add(hbox3, 0, wxALIGN_CENTER|wxTOP, 5);
    
    // Add "Forget your password?" link
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* forgetPasswordLabel = new wxStaticText(panel, wxID_ANY, "Forget your password?");
    forgetPasswordLabel->SetForegroundColour(wxColour(255, 255, 255));
    wxFont forgetPassFont(13, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true, "Montserrat");
    forgetPasswordLabel->SetFont(forgetPassFont);
    hbox4->Add(forgetPasswordLabel);
    vbox_middle->Add(hbox4, 0, wxALIGN_CENTER | wxTOP, 20);

    vbox_above_middle->Add(vbox_middle, 0, wxALIGN_CENTER_VERTICAL);
    vbox->Add(vbox_above_middle, 1, wxEXPAND | wxRIGHT , 130);

    panel->SetSizer(vbox);
    Center();
    
    panel->Bind(wxEVT_PAINT, &FormLogin::OnImagePanelPaint, this);
    forgetPasswordLabel->Bind(wxEVT_LEFT_DOWN, &FormLogin::OnForgetPassword, this);
    m_buttonLogin->Bind(wxEVT_BUTTON, &FormLogin::OnLogin, this);
    m_buttonSignUp->Bind(wxEVT_BUTTON, &FormLogin::OnSignUp, this);
}

void FormLogin::OnSignUp(wxCommandEvent& event)
{
    wxDialog signUpdlg(this, wxID_ANY, "Creating an account");
    int newX =850; // Replace this with the desired X-coordinate
    int newY = 200; // Replace this with the desired Y-coordinate
    signUpdlg.Move(newX, newY);
    wxBoxSizer* signUp_box = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* username_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* password_box = new wxBoxSizer(wxHORIZONTAL);
    
    new_username = new wxStaticText(&signUpdlg, wxID_ANY, "Username:", wxDefaultPosition, wxSize(70, -1));
    username_box->Add(new_username, 0, wxRIGHT,5);
    
    m_newUsernameEntry = new wxTextCtrl(&signUpdlg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, -1));
    username_box->Add(m_newUsernameEntry, 1);
    
    new_password = new wxStaticText(&signUpdlg, wxID_ANY, "Password:", wxDefaultPosition, wxSize(70, -1));
    password_box->Add(new_password, 0, wxTOP|wxRIGHT, 5);
    m_newPasswordEntry = new wxTextCtrl(&signUpdlg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, -1));
    password_box->Add(m_newPasswordEntry, wxTOP, 5);
    
    signUp_box->Add(username_box, 0,  wxEXPAND|wxLEFT|wxRIGHT, 10);
    signUp_box->Add(password_box, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);
    
    wxButton* createAcc = new wxButton(&signUpdlg, wxID_OK, "Create A New Account");
    signUp_box->Add(createAcc, 0, wxALIGN_CENTER | wxALL, 10);
    //createAcc->Bind(wxEVT_BUTTON, &FormLogin::OnCreateAccount);

    
    signUpdlg.SetSizerAndFit(signUp_box);
    int result = signUpdlg.ShowModal();
    if (result == wxID_OK)
    {
        // Get the username entered by the user
        username = m_newUsernameEntry->GetValue();
        password = m_newPasswordEntry->GetValue();
        if (!username.empty() && !password.empty()) {
            // Create account function here
            
            // Show the retrieved password in a message box
            wxMessageBox("", "Account created!", wxOK | wxICON_INFORMATION, this);
        }
    }
}

wxString FormLogin::GetPasswordFromUsername(const wxString& username){
    ifstream account("new account");
    string result;
    getline(account, result, '\n');
    getline(account,result, '\n');
    return result;
}

void FormLogin::OnForgetPassword(wxMouseEvent& event)
{
    // Create a new dialog for getting back the password
    wxDialog retrievedlg(this, wxID_ANY, "Getting back your password");
    int newX =900; // Replace this with the desired X-coordinate
    int newY = 200; // Replace this with the desired Y-coordinate
    retrievedlg.Move(newX, newY);
    // Create sizers for the dialog
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);

    // Add a label for the username
    wxStaticText* usernameLabel = new wxStaticText(&retrievedlg, wxID_ANY, "Username:");
    hbox1->Add(usernameLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

    // Add an entry to type in the username
    wxTextCtrl* usernameEntry = new wxTextCtrl(&retrievedlg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1));
    hbox1->Add(usernameEntry, 1, wxALIGN_CENTER_VERTICAL);

    vbox->Add(hbox1, 0, wxEXPAND | wxALL, 10);

    // Add a button for retrieving the password
    wxButton* getPasswordButton = new wxButton(&retrievedlg, wxID_OK, "Get Password");
    vbox->Add(getPasswordButton, 0, wxALIGN_CENTER | wxALL, 10);
    
    retrievedlg.SetSizerAndFit(vbox);
    int result = retrievedlg.ShowModal();
    
        // Show the dialog and wait for user input
        if (result == wxID_OK)
        {
            retrieveUser = usernameEntry->GetValue();
            if (!retrieveUser.empty()) {
            // Custom function to check and retrieve the password based on the username
            retrievedPass = FormLogin::GetPasswordFromUsername(username);
            
            // Show the retrieved password in a message box
            wxMessageBox("Your password is: " + retrievedPass, "Password Retrieval", wxOK | wxICON_INFORMATION, this);
        }
        }
}

void FormLogin::CreateScaledBg()
{
    wxSize sz = panel->GetSize();
    m_scaledBg = wxBitmap(m_image.Scale(sz.GetWidth(), sz.GetHeight(),
                          wxIMAGE_QUALITY_NORMAL));
}

void FormLogin::OnImagePanelPaint(wxPaintEvent&)
{
    if (panel->GetSize() != m_scaledBg.GetSize() )
    {
        CreateScaledBg();
    }

    wxPaintDC dc(panel);
    dc.DrawBitmap(m_scaledBg,0,0);
}

void FormLogin::OnQuit(wxCommandEvent& event)
{
    Close(true);
}
 
void FormLogin::OnLogin(wxCommandEvent& event)
{
    wxString username = m_usernameEntry->GetValue();
    wxString password = m_passwordEntry->GetValue();
 
    if (username.empty() || password.empty()) {
        wxMessageBox(wxT("Username or password must not empty"), wxT("Warning!"), wxICON_WARNING);
    }
    
    else {
        bool isLoggedIn = true;
        if (isLoggedIn)
        {
            this->Close();
            
            MyFrame* dictionary = new MyFrame();
            int width, height;
            dictionary->GetSize(& width, & height);
            dictionary->SetSize(wxDefaultCoord, wxDefaultCoord, width, height);
            dictionary->Show(true);
        }
        else
            wxMessageBox("Login failed. Please try again.", "Login Error", wxOK | wxICON_ERROR, this);
    }
}

FormLogin::~FormLogin() {}
 
BEGIN_EVENT_TABLE(FormLogin, wxFrame)
EVT_BUTTON(wxID_EXIT, FormLogin::OnQuit)
EVT_BUTTON(BUTTON_Login, FormLogin::OnLogin)
END_EVENT_TABLE()
