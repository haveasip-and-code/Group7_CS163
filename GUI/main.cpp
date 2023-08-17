
#include "treebook test.hpp"
#include "Main.hpp"
#include "Form Login.hpp"
#include "core.h"
#include "prototype.h"
#include "metadata.h"
#include "trie.h"
#include "databankManager.h"
#include "generalLib.h"


bool MainApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    FormLogin *formLogin = new FormLogin(wxT("Login"));
    formLogin->Show(true);

    return true;
}

wxIMPLEMENT_APP(MainApp);
