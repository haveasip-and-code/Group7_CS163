
#include "treebook test.hpp"
#include "Main.hpp"
#include "Form Login.hpp"
#include "core.h"
#include "prototype.h"
#include "metadata.h"
#include "trie.h"
#include "databankManager.h"
#include "generalLib.h"
#include "debugCore.h"
#include "initCore.h"
#include "prototype.h"

bool MainApp::OnInit()
{
    //prototypemode();
    if ( !wxApp::OnInit() )
        return false;

    initialize();
    //cout<<"Init Completed\n";

    FormLogin *formLogin = new FormLogin(wxT("Login"));
    formLogin->Show(true);

    return true;
}

wxIMPLEMENT_APP(MainApp);
