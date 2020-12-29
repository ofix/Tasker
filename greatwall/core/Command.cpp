#include "Command.h"

Command::Command(wxString strCmd,wxString strExecuteDir):
    m_strCmd(strCmd),m_strExecuteDir(strExecuteDir),m_bRunning(false)
{
    //ctor
}

Command::~Command()
{
    //dtor
}

bool Command::Execute(bool bSync){
    m_bRunning = true;
    m_process = new wxProcess(this,PROCESS_END_ID);
    if(bSync) {
        m_process->Redirect();
    }
    wxExecuteEnv env;
    env.cwd = m_strExecuteDir;
    long pid = wxExecute(cmd,wxEXEC_ASYNC,m_process,&env);
    if( !pid ) {
        delete m_process;
        return false;
    }
    m_process->SetPid(pid);

    wxLogVerbose("PID of the new process: %ld", m_process->GetPid());
    m_outputStream = m_process->GetOutputStream();
    if (!m_outputStream) {
        wxLogError("Failed to connect to child stdin");
        return false;
    }

    m_inputStream = m_process->GetInputStream();
    if (!m_inputStream) {
        wxLogError("Failed to connect to child stdout");
        return false;
    }
    m_process->SetNextHandler(this);
    return true;
}

wxString Command::GetConsoleLine()
{
    if(m_process->IsInputAvailable() && m_inputStream->IsOk()) {
        wxTextInputStream tis(*m_in);
        wxString msg;
        msg<<tis.ReadLine()<<wxT("\r\n");
        return msg;
    }
    return wxT("");
}

void Command::OnProcessEnd(wxProcessEvent& event)
{
   m_bRunning = false;
}

bool Command::IsRunning(){
    return m_bRunning;
}


