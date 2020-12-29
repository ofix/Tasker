/***************************************************************
 * Name:      greatwallMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    ofix ()
 * Created:   2020-12-08
 * Copyright: ofix ()
 * License:
 **************************************************************/

#include "greatwallMain.h"
#include <wx/msgdlg.h>
#include <wx/utils.h>
#include <wx/log.h>
#include "core/Task.h"
#include "core/TaskExecutor.h"

//(*InternalHeaders(greatwallDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f ) {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(greatwallDialog)
const long greatwallDialog::ID_TEXTCTRL_CONSOLE = wxNewId();
//*)

BEGIN_EVENT_TABLE(greatwallDialog,wxDialog)
    //(*EventTable(greatwallDialog)
    //*)
    EVT_TIMER(TIMER_ID,greatwallDialog::OnTimer )
    EVT_END_PROCESS(PROCESS_END_ID,greatwallDialog::OnProcessEnd)
END_EVENT_TABLE()

greatwallDialog::greatwallDialog(wxWindow* parent,wxWindowID id):m_timer(this,TIMER_ID )
{
    //(*Initialize(greatwallDialog)
    Create(parent, id, _("wxWidgets app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(480,480));
    m_textCtrlConsole = new wxTextCtrl(this, ID_TEXTCTRL_CONSOLE, _("Text"), wxPoint(8,32), wxSize(464,312), wxTE_PROCESS_ENTER|wxTE_MULTILINE|wxVSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_CONSOLE"));

    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&greatwallDialog::OnInit);
    //*)

}

greatwallDialog::~greatwallDialog()
{
    //(*Destroy(greatwallDialog)
    //*)
}

bool greatwallDialog::ExecuteGitCommand()
{
    wxString cmd = wxT("git status");
    wxArrayString result;
    wxExecuteEnv env;
    env.cwd = wxT("E:/work_root/bmc_webui");
    int code = wxExecute(cmd,result,wxEXEC_SYNC,&env);
    wxLogDebug(wxT("Result Code = %d "),code);
    for(wxArrayString::const_iterator iter = result.begin(); iter != result.end(); iter++) {
        wxLogDebug(wxT("%s"),(*iter).c_str());
    }
    return true;
}

bool greatwallDialog::ExecuteTasks()
{
    TaskExecutor executor;
    Task task(wxT("E:/work_root/c_projects/greatwall/7-Zip/7z a -bsp1 -r E:/GwGuard/gwsoft_#date_time#.zip ./gwsoft \
                       -xr!runtime\\* -xr!application\\admin\\view_src"),"compress gwsoft");
    wxExecuteEnv env;
    env.cwd = wxT("E:/work_root/");
    task.SetEnv(env);
    executor.AddTask(task);
    wxExecuteEnv env;
    env.cwd = wxT("E:/GwGuard")
    Task task(wxT("cp gwsoft_#date_time#.zip "))

    return true;
}

bool greatwallDialog::CompressZipFile()
{
    wxString cmd = wxT("E:/work_root/c_projects/greatwall/7-Zip/7z a -bsp1 -r gwsoft_20201225.zip ./gwsoft \
                       -xr!runtime\\* -xr!application\\admin\\view_src");

    m_process = new wxProcess(this,PROCESS_END_ID);
    m_process->Redirect();
    wxExecuteEnv env;
    env.cwd = wxT("E:/work_root/");
    long pid = wxExecute(cmd,wxEXEC_ASYNC,m_process,&env);
    if( !pid ) {
        delete m_process;
        return false;
    }
    m_process->SetPid(pid);

    wxLogVerbose("PID of the new process: %ld", m_process->GetPid());
    m_out = m_process->GetOutputStream();
    if (!m_out) {
        wxLogError("Failed to connect to child stdin");
        return false;
    }

    m_in = m_process->GetInputStream();
    if (!m_in) {
        wxLogError("Failed to connect to child stdout");
        return false;
    }
    m_process->SetNextHandler(this);
    m_textCtrlConsole->Clear();
    m_timer.Start(20);
    return true;
}

void greatwallDialog::OnInit(wxInitDialogEvent& event)
{
    //ExecuteGitCommand();
    CompressZipFile();
}

void greatwallDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void greatwallDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void greatwallDialog::OnTimer(wxTimerEvent &event )
{
    if(m_process != NULL && m_process->IsInputAvailable() && m_in->IsOk()) {
        wxTextInputStream tis(*m_in);
        wxString msg;
        msg<<tis.ReadLine()<<wxT("\r\n");
        m_textCtrlConsole->AppendText(msg);
    }
}

void greatwallDialog::OnProcessEnd(wxProcessEvent& event)
{
    if(m_timer.IsRunning()){
        m_timer.Stop();
        m_process = NULL;
    }
}

