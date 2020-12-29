#ifndef TASK_H
#define TASK_H

#include <wx/arrstr.h>
#include <wx/utils.h>
#include <wx/list.h>
#include "Command.h"

enum TASK_STATE {
    WAITING=0,
    RUNNING=1,
    EXECUTED=2,
    SUCCESS=3,
    FAILED=4
};

WX_DECLARE_LIST(Command,CommandList);
WX_DEFINE_LIST(CommandList);

class Task
{
public:
    Task();
    virtual ~Task();
    void AddCmd(Command* ptrCmd);
    bool Execute();
    wxArrayString GetConsoleOutput() const;

protected:
    Command* m_ptrCurrentCmd;
    CommandList m_cmdList;          //所有需要执行的命令
    wxArrayString m_consoleOutput;  //控制台输出
    int m_status;                   //当前任务状态
    int m_executeMilliSeconds;      //执行毫秒数
};

#endif // TASK_H
