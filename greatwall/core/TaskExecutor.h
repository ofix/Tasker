#ifndef TASKEXECUTOR_H
#define TASKEXECUTOR_H

#include <wx/dynarray.h>
#include <wx/stream.h>
#include <wx/txtstrm.h>
#include <wx/process.h>

#include "Task.h"
WX_DECLARE_OBJARRAY(Task,ArrayTask);

class TaskExecutor
{
    public:
        TaskExecutor();
        TaskExecutor(wxString strTasks);
        virtual ~TaskExecutor();
        void AddTask(Task task,int index=-1); //添加任务
        bool DeleteTask(Task task);
        bool ParseTasks(wxString& strTasks);
        bool Run(); //开始执行任务
        bool Stop(); //停止当前任务
        void ClearTasks(); //清空任务
        bool SetTasks(wxString strTasks);
        Task GetCurrentTask(); //获取当前正在执行的任务
        void OnTimer(); //定时获取任务控制台输出
        wxArrayString GetConsoleOutput();
    protected:
        bool ExecuteTask(Task& task); //执行下一个任务
    protected:
        wxString m_strTasks; //所有任务的字符串
        ArrayTask m_tasks; //所有的任务列表
        Task m_taskCurrent; //当前正在执行的任务
        bool m_state; //当前状态
        int m_percent; //当前运行进度
        wxProcess m_process; //异步进程
        wxInputStream* m_inputStream;
        wxOutputStream* m_outputStream;
        wxProcess* m_process;
    private:
};

#endif // TASKEXECUTOR_H
