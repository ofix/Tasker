#include "TaskExecutor.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayTask);

TaskExecutor::TaskExecutor():
    m_percent(-1),
    m_taskCurrent(NULL),
{
    //ctor
}

TaskExecutor::~TaskExecutor()
{
    //dtor
}

TaskExecutor(wxString strTasks):
    m_strTasks(strTasks)
{
    ParseTasksStr(m_strTasks);
}

bool TaskExecutor::ParseTasks(wxString& strTasks){
    return false;
}

bool TaskExecutor::ExecuteTask(Task& task)
{
    m_process = new wxProcess(this,PROCESS_END_ID);
    if(task.IsSync()) {
        m_process->Redirect();
    }
    long pid = wxExecute(cmd,wxEXEC_ASYNC,m_process,&task.GetEnv());
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

wxArrayString TaskExecutor::GetConsoleOutput(){
    if(m_taskCurrent == NULL){
        return wxArrayString(wxT(""));
    }
    return GetCurrentTask().GetConsoleOutput();
}

void TaskExecutor::OnTimer()
{
    if(m_taskCurrent == NULL || m_percent == -1 || m_percent == 100){
        m_timer.Stop();
        m_process = NULL;
    }
    if(m_process != NULL && m_process->IsInputAvailable() && m_inputStream->IsOk()) {
        wxTextInputStream tis(*m_in);
        wxString msg;
        msg<<tis.ReadLine()<<wxT("\r\n");
        GetCurrentTask().GetConsoleOutput()->insert(msg);
    }
}

void greatwallDialog::OnProcessEnd(wxProcessEvent& event)
{
    if(m_timer.IsRunning()){
        m_timer.Stop();
        m_process = NULL;
    }
}
