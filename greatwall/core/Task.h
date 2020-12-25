#ifndef TASK_H
#define TASK_H

#include <wx/arrstr.h>
#include <wx/utils.h>

enum TASK_STATE {
    WAITING=0,
    RUNNING=1,
    EXECUTED=2,
    SUCCESS=3,
    FAILED=4
};

class Task
{
public:
    Task(wxString strCmd,wxString strName);
    void Sync()
    {
        m_sync = true;
    }
    virtual ~Task();
    bool IsSync()
    {
        return m_sync;
    }
    wxExecuteEnv GetEnv()
    {
        return m_env;
    }
    wxString GetCmd() const;
    bool Parse(); //任务解析器
    wxArrayString GetConsoleOutput() const;

protected:
    wxString m_name;      //任务名称
    wxString m_cmdOrigin; //执行的命令
    wxString m_cmdParsed; //解析后的真实命令
    wxExecuteEnv m_env;   //环境变量
    wxArrayString m_consoleOutput; //控制台输出
    bool m_sync;     //是否是同步任务
    int m_status;    //当前任务状态
    int m_executeMilliSeconds; //执行毫秒数
};

#endif // TASK_H
