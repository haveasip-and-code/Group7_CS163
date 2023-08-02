//
//  Form Login.hpp
//  wxWidets 1st proj
//
//  Created by Nguyễn Bạch Trường Giang on 23/07/2023.
//

#ifndef Form_Login_hpp
#define Form_Login_hpp

#include <stdio.h>
#include "wx/wx.h"
#include "wx/custombgwin.h"
#include <wx/dcclient.h>
#include <fstream>
#include <string>
using namespace std;

class FormLogin : public wxFrame
{
public:
    FormLogin(const wxString& title);
 
    // Destructor
    virtual ~FormLogin();
 
private:
    wxPanel* panel;
    wxTextCtrl* m_usernameEntry;
    wxTextCtrl* m_passwordEntry;
    wxButton* m_buttonLogin;
    wxButton* m_buttonSignUp;
    wxMessageDialog *dlg;
    wxImage m_image;
    wxBitmap m_scaledBg;
    wxStaticText* new_username;
    wxStaticText* new_password;
    wxTextCtrl* m_newUsernameEntry;
    wxTextCtrl* m_newPasswordEntry;
    wxDialog* signUpdlg;
    wxDialog* retrievedlg;
    wxString username;
    wxString password;
    wxString retrievedPass;
    wxString retrieveUser;
    
private:
    void OnQuit(wxCommandEvent& event);
    void OnLogin(wxCommandEvent& event);
    void OnImagePanelPaint(wxPaintEvent&);
    void CreateScaledBg();
    void OnForgetPassword(wxMouseEvent& event);
    wxString GetPasswordFromUsername(const wxString& username);
    void OnSignUp(wxCommandEvent& event);
    
private:
    DECLARE_EVENT_TABLE()
 
    enum
    {
        BUTTON_CreateAcc = wxID_HIGHEST +3,
        BUTTON_RetrievePass = wxID_HIGHEST+4,
        BUTTON_SignUp = wxID_HIGHEST + 2,
        BUTTON_Login = wxID_HIGHEST + 1,
    };
};
#endif /* Form_Login_hpp */
