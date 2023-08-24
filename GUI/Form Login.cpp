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
    wxFont myAppFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false, "Montserrat Medium");

    // Try to load the image.
    m_image = wxImage("login5.png", wxBITMAP_TYPE_ANY);
    if ( !m_image.IsOk() )
    {
        return;
    }
    CreateScaledBg();

    wxBoxSizer *screen = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *columnWithItems = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *username_strip = new wxBoxSizer(wxHORIZONTAL);
    m_usernameEntry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 22), wxTE_PROCESS_ENTER);
    m_usernameEntry->SetHint("Username");
    m_usernameEntry->SetFont(myAppFont);
    username_strip->AddStretchSpacer(1);
    username_strip->Add(m_usernameEntry, 0, wxEXPAND | wxRIGHT, 130);

    wxBoxSizer *password_strip = new wxBoxSizer(wxHORIZONTAL);
    m_passwordEntry = new wxTextCtrl(panel, wxID_ANY, wxString(""), wxDefaultPosition, wxSize(250, 22), wxTE_PASSWORD|wxTE_PROCESS_ENTER);
    m_passwordEntry->SetHint("Password");
    m_passwordEntry->SetFont(myAppFont);
    password_strip->AddStretchSpacer(1);
    password_strip->Add(m_passwordEntry, 0, wxEXPAND | wxRIGHT, 130);

    wxBoxSizer *buttonStrip = new wxBoxSizer(wxHORIZONTAL);
    // Add "Sign Up" button
    m_buttonSignUp = new wxButton(panel, BUTTON_SignUp, "Sign Up");
    m_buttonSignUp->SetForegroundColour(wxColour(73, 86, 111));
    m_buttonSignUp->SetFont(myAppFont);
    m_buttonSignUp->SetMinSize(wxSize(-1, 25));
    buttonStrip->Add(m_buttonSignUp, 0, wxRIGHT, 96);

    // Add "Login" button
    m_buttonLogin = new wxButton(panel, BUTTON_Login, wxT("Login"));
    m_buttonLogin->SetForegroundColour(wxColour(73, 86, 111));
    m_buttonLogin->SetFont(myAppFont);
    m_buttonLogin->SetMinSize(wxSize(-1, 25));
    buttonStrip->Add(m_buttonLogin, 0, wxRIGHT, 130);

    // Add "Forget your password?" link
    wxFont hyperlinkFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, true, "Montserrat Medium");

    wxBoxSizer* forgetPassword_strip = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* forgetPasswordLabel = new wxStaticText(panel, wxID_ANY, "Forgot password?", wxDefaultPosition, wxSize(250, 20), wxALIGN_CENTER);
    forgetPasswordLabel->SetBackgroundColour(wxColour(73, 86, 111));
    forgetPasswordLabel->SetForegroundColour(wxColour(249, 246, 246));
    forgetPasswordLabel->SetFont(hyperlinkFont);
    forgetPassword_strip->Add(forgetPasswordLabel, 0, wxRIGHT, 130);

    columnWithItems->AddStretchSpacer(1);
    columnWithItems->Add(username_strip, 0, wxALIGN_RIGHT);
    columnWithItems->AddSpacer(3);
    columnWithItems->Add(password_strip, 0, wxALIGN_RIGHT);
    columnWithItems->AddSpacer(12);
    columnWithItems->Add(buttonStrip, 0, wxALIGN_RIGHT);
    columnWithItems->AddSpacer(25);
    columnWithItems->Add(forgetPassword_strip, 0, wxALIGN_RIGHT);
    columnWithItems->AddStretchSpacer(1);
    screen->AddStretchSpacer(1);
    screen->Add(columnWithItems, 1, wxEXPAND);
    panel->SetSizer(screen);
    // // Center();

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
