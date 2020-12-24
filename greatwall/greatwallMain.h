/***************************************************************
 * Name:      greatwallMain.h
 * Purpose:   Defines Application Frame
 * Author:    ofix ()
 * Created:   2020-12-08
 * Copyright: ofix ()
 * License:
 **************************************************************/

#ifndef GREATWALLMAIN_H
#define GREATWALLMAIN_H

//(*Headers(greatwallDialog)
#include <wx/dialog.h>
#include <wx/textctrl.h>
//*)

#include <wx/timer.h>
#include <wx/stream.h>
#include <wx/txtstrm.h>
#include <wx/process.h>

class greatwallDialog: public wxDialog
{
    public:

        greatwallDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~greatwallDialog();
        bool ExecuteGitCommand();
        bool CompressZipFile();
        void OnTimer(wxTimerEvent &event);
        void OnProcessEnd(wxProcessEvent& event);
    private:

        //(*Handlers(greatwallDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        //*)

        //(*Identifiers(greatwallDialog)
        static const long ID_TEXTCTRL_CONSOLE;
        //*)

        //(*Declarations(greatwallDialog)
        wxTextCtrl* m_textCtrlConsole;
        //*)

        wxTimer m_timer;
        wxInputStream* m_in;
        wxOutputStream* m_out;
        wxProcess* m_process;
        #define TIMER_ID 1000
        #define PROCESS_END_ID 1001
        DECLARE_EVENT_TABLE()
};

#endif // GREATWALLMAIN_H
