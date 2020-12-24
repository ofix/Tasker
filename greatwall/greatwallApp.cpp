/***************************************************************
 * Name:      greatwallApp.cpp
 * Purpose:   Code for Application Class
 * Author:    ofix ()
 * Created:   2020-12-08
 * Copyright: ofix ()
 * License:
 **************************************************************/

#include "greatwallApp.h"

//(*AppHeaders
#include "greatwallMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(greatwallApp);

bool greatwallApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	greatwallDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
