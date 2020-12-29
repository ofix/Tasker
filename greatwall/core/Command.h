#ifndef COMMAND_H
#define COMMAND_H


class Command
{
    public:
        Command(wxString strCmd,wxString strExecuteDir);
        virtual ~Command();
        bool Execute();
        wxString GetConsoleLine();
        bool IsRunning();
    protected:
        wxString m_strCmd;
        wxString m_strExecuteDir;
        wxProcess m_process;
        bool m_bRunning;
    private:
};

#endif // COMMAND_H
