#include "Task.h"

Task::Task(wxString strCmd,wxString strName):
    m_cmd(strCmd),m_name(strName)
{
    m_sync = true;
}

Task::~Task()
{
    //dtor
}

wxString Task::GetCmd() const
{
    return m_cmd;
}

wxArrayString GetConsoleOutput() const
{
    return m_consoleOutput;
}
