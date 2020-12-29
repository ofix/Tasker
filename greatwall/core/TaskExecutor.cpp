#include "TaskExecutor.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayTask);

TaskExecutor::TaskExecutor():
    m_percent(-1),
    m_taskCurrent(NULL),
{

}


TaskExecutor::(wxString strTasks):
    m_strTasks(strTasks)
{
    ParseTasksStr(m_strTasks);
}

TaskExecutor::~TaskExecutor()
{

}

bool TaskExecutor::ReadFromFile(strFilePath)
{
    wxTextFile file;
    if(!file.Open(strFilePath)) {
        return false;
    }
    int nLines = file.GetLineCount();
    wxString strCmd;
    bool bMultiLineCmd = false;
    wxString strExecAt = wxT("");
    wxString strOldCmd = wxT("");
    Task task;
    for(int i = 0; i<nLines;) {
        strCmd = wxT("");
        do {
            wxString line = file[i++];
            strExecAt = ParseMetaName(line);
            if(strExecAt != wxT("")){
                break;
            }
            bMultiLineCmd = (line.Right(1) == wxT("\\"));
            strCmd += bMultiLineCmd?line.substr(0,line.Len()-1):line;
        } while(bMultiLineCmd);
        ReplaceCmd(strCmd);//替换标识符
        strCmdArr.Add(strCmd);
        if(strExecAt != wxT("")){
            Task task
        }
    }
    file.Close();
    return true;
}

wxString TaskExecutor::ParseMetaName(wxString strLine)
{
    wxString charFirst = line.Left(1);
    wxString charSecond = line.Mid(1,1);
    wxString charLast = line.Right(1);
    wxString strExecAt = wxt("");
    if(charFirst == wxT("#") && charSecond != wxT("!")) { //任务名称
        size_t nPos = line.find(wxT(":"));
        wxString strMeta = line.Mid(1,nPos);
        if(strMeta == wxT("exec_at")) {
            strExecAt = line.Mid(nPos);
        }
    }
    return strExecAt;
}

void TaskExecutor::ReplaceCmd(wxString& strCmd)
{
    wxDateTime now = wxDateTime::Now();
    wxString strNow = now.Format(wxT("%Y_%m_%d %H_%M_%S"));
    strCmd.Replace(wxT("{date_time}"),strNow,true); //替换所有出现日期的地方
    strCmd.Replace(wxT("cp "),wxT("copy "),false); //替换拷贝命令
    strCmd.Replace(wxT("rm "),wxT("del "),false); //替换删除命令
}

bool TaskExecutor::ParseTasks(wxString& strTasks)
{

    return false;
}

bool TaskExecutor::ExecuteTask(Task& task)
{
   task.
}

wxArrayString TaskExecutor::GetConsoleOutput()
{
    if(m_taskCurrent == NULL) {
        return wxArrayString(wxT(""));
    }
    return GetCurrentTask().GetConsoleOutput();
}

void TaskExecutor::OnTimer()
{
    if(m_taskCurrent == NULL || m_percent == -1 || m_percent == 100) {
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
    if(m_timer.IsRunning()) {
        m_timer.Stop();
        m_process = NULL;
    }
}
