
#include "Main.hpp"
#include "Form Login.hpp"
#include "Dictionary.hpp"

bool MainApp::OnInit()
{
 
    FormLogin *formLogin = new FormLogin(wxT("Login"));
    formLogin->Show(true);

    return true;
}


wxIMPLEMENT_APP(MainApp);
