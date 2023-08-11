
#include "treebook test.hpp"
#include "Main.hpp"
#include "Form Login.hpp"


bool MainApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    FormLogin *formLogin = new FormLogin(wxT("Login"));
    formLogin->Show(true);

    return true;
}

wxIMPLEMENT_APP(MainApp);
