#ifndef LOG_H
#define LOG_H
#include <QString>
#include "Afx.h"
#include "Singleton.h"

#define PRINT_LOG_FILE_LINE_FUNCTION 1

#define DEBUG_INFO __FILE__, __LINE__, __FUNCTION__

namespace Logger
{

class Log
    {
    public:
        Log();
        virtual ~Log();
        static Log& Instance()
        {
            return Singleton<Log>::instance();
        }

        void LogMsg(const char* msg);
        void LogMsgGDW376(const char* msg);//added by YY&YY@
        void LogMsgVFLF(const char* msg, int v, QString f, int l, QString func);//added by YY&YY@
        void LogMsgVFLF_Error(const char* msg, int v, QString f, int l, QString func);//added by YY&YY@
                void LogDebug(const char* msg, int v, QString f, int l, QString func);
        void LogMsgError(const char* msg, QString f, int l);
        //打印报文
        void LogBuffer(QString strHead,UInt8 *buf, int len);
        //打印到网络上
        void LogMsgOnNet(const char* msg);
        //显示错误信息
        void LogError(const char* msg);
        //显示日志信息
        void LogInfo(const char *msg);


    private:


       void WriteFile(QString logPath, const char *msg);

    };
}
#endif // LOG_H
//end of file.