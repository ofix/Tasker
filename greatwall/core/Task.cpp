#include "Task.h"

Task::Task()
{
}

Task::~Task()
{
}

wxArrayString Task::GetConsoleOutput() const
{
    return m_consoleOutput;
}

void Task::AddCmd(Command *ptrCmd){
    m_cmdList.Append(ptrCmd);
}


bool Task::Execute(){ //执行命令
  CommandList::iterator iter;
  for(iter=m_cmdList.begin(); iter!=m_cmdList.end(); ++iter){
        Command* ptrCmd = (*iter);
        m_ptrCurrntCmd = (*iter);
        ptrCmd->Execute();
  }
}

void Task::GetConsoleLine()
{
    if(m_ptrCurrentCmd){
        return m_ptrCurrentCmd->GetConsoleLine();
    }
    return wxT("");
}
