#include "Log.h"
#include <QDebug>
#include <QDateTime>


#define GDW376_PRINT_LOG

namespace Logger
{


Log::Log()
{

}

Log::~Log()
{

}

void Log::LogMsg(const char* msg)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDate = dateTime.date().toString("yyyy-MM-dd ");
    QString strTime=dateTime.time().toString("hh:mm:ss.zzz ");

    QString str = strDate+strTime;
    str.append(msg);
    qDebug() << str;
}
void Log::LogMsgGDW376(const char* msg)
{
    msg = msg;
    #ifdef GDW376_PRINT_LOG
    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDate = dateTime.date().toString("yyyy-MM-dd ");
    QString strTime=dateTime.time().toString("hh:mm:ss.zzz ");

    QString str = strDate+strTime;
    str.append(msg);
    qDebug() << str;

    //qDebug()<<"FILE:"<<__FILE__<<"  LINE:"<<__LINE__<<"  FUNC:"<<__FUNCTION__;

    #endif
}

void Log::LogMsgVFLF(const char* msg, int v, QString f, int l, QString func)
{
#ifdef GDW376_PRINT_LOG
    qDebug() <<msg<<"="<<v;

    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDate = dateTime.date().toString("yyyy-MM-dd ");
    QString strTime=dateTime.time().toString("hh:mm:ss.zzz ");
    QString str = strDate+strTime;
    qDebug()<<"FILE:"<<f<<" LINE:"<<l<<" FUNC:"<<func<<" TIME:"<<str;
#endif
}

void Log::LogMsgVFLF_Error(const char* msg, int v, QString f, int l, QString func)
{
#if 1
    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDate = dateTime.date().toString("yyyy-MM-dd ");
    QString strTime=dateTime.time().toString("hh:mm:ss.zzz ");
    QString str = strDate+strTime;
    //qDebug()<<msg<<"="<<v<<" FILE:"<<f<<" L:"<<l<<" F:"<<func<<" T:"<<str;
    qDebug()<<"------------------"<<v;
    qDebug()<<msg<<"="<<v<<" FILE:"<<f<<" L:"<<l<<" F:"<<func;
#endif
}

void Log::LogMsgError(const char* msg, QString f, int l)
{
#if 1
    qDebug()<<msg<<" FILE:"<<f<<" L:"<<l;
#endif
}
void Log::LogBuffer(QString strHead,UInt8 *buf, int len)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDate = dateTime.date().toString("yyyy-MM-dd ");
    QString strTime=dateTime.time().toString("hh:mm:ss.zzz ");

    QString str = strDate+strTime;
    str.append( strHead);
    for(int i=0;i<len;i++)
    {
        str.append(QString("%1").arg(buf[i],2,16,QChar('0')));
    }
    LogMsgOnNet(str.toAscii());
}

void Log::LogDebug(const char* msg, int v, QString f, int l, QString func)
{
    #if 1
    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDate = dateTime.date().toString("yyyy-MM-dd ");
    QString strTime=dateTime.time().toString("hh:mm:ss.zzz ");
    QString str = strDate+strTime;

    qDebug()<<"";//换行
    //qDebug()<<"debug:"<<msg<<"="<<v<<" F:"<<f<<" L:"<<l<<" FUNC:"<<func<<" T:"<<str;
    #if PRINT_LOG_FILE_LINE_FUNCTION
    qDebug()<<"debug:"<<msg<<"="<<v<<" F:"<<f<<" L:"<<l<<" FUNC:"<<func;
    #else
    qDebug()<<"debug:"<<msg<<"="<<v;
    #endif

    #endif
}

void Log::LogError(const char *msg)
{
    //将错误信息写入文件，再弹出对话框
//    LogMsg(msg);

//    LoggerNotifyEvent* event = new LoggerNotifyEvent(LOGGER_EVENT);
//    event->title = "错误";
//    event->msg = msg;
//    QApplication::postEvent(g_pMainForm,event);
//    QString dirPath = "Log/LogError";
//#ifdef Q_OS_LINUX
//    dirPath = "/home/nvnbc/Log/LogError";
//#endif
//    //下面把日志数据，写进文件LogError.log中
//    WriteFile(dirPath,msg);
//    //上面把日志数据，写进文件LogError.log中
}

void Log::LogInfo(const char *msg)
{
    //将错误信息写入文件
    LogMsg(msg);
    //下面把日志数据，写进文件LogInfo.log中
    QString dirPath = "Log/LogInfo";
#ifdef Q_OS_LINUX
    dirPath = "/home/nvnbc/Log/LogInfo";
#endif
    WriteFile(dirPath,msg);
    //上面把日志数据，写进文件LogInfo.log中
}

void Log::LogMsgOnNet(const char *msg)
{
    //m_pTcpServer->sendMessage(msg);
    LogInfo(msg);
}

void Log::WriteFile(QString logPath,const char* msg)
{
//    //下面把日志数据，写进文件LogInfo.log中
//    QDir dir;
//    QDateTime nowDate = QDateTime::currentDateTime();

//    QString dirPath = "Log";
//#ifdef Q_OS_LINUX
//    dirPath = "/home/nvnbc/Log";
//#endif
//    if(!dir.exists(dirPath))
//    {
//       dir.mkdir(dirPath);
//    }
//    else
//    {
//        if(!dir.exists(logPath))
//        {
//            dir.mkdir(logPath);
//        }
//        else
//        {
//            QDir dirpath(logPath);
//            //检查文件夹内的文件数量，删除一个月以前的历史记录
//            dirpath.setFilter(QDir::Files | QDir::NoSymLinks);
//            QFileInfoList filelist = dirpath.entryInfoList();
//            int file_count = filelist.count();
//            if(file_count > 30)
//            {
//                int temp=file_count;
//                for(int i=0; i<file_count; i++)
//                {
//                    QFileInfo file_info = filelist.at(i);
//                    int year=file_info.fileName().mid(0,4).toInt();
//                    int month=file_info.fileName().mid(5,2).toInt();
//                    int day=file_info.fileName().mid(8,2).toInt();
//                    QDate filedate(year,month,day);
//                    QDate tDate = filedate.addDays(30);
//                    if(tDate<=nowDate.date())
//                    {
//                        QFile file(file_info.filePath());
//                        file.setPermissions(QFile::WriteOwner);
//                        file.remove();
//                        temp--;
//                        if(temp<=30)
//                            break;
//                    }
//                }
//            }
//        }
//    }
//    string dirpath= logPath.append(QString("/")).toStdString();
//    dirpath+=nowDate.toString("yyyy-MM-dd").toStdString()+".log";
//    QFile file(dirpath.c_str());
//    if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
//    {
//        return;
//    }
//    QTextStream in(&file);
//    QTextCodec *utf8 = QTextCodec::codecForName("utf-8");
//    QByteArray encoded = utf8->fromUnicode(msg);
//    QString dateTimeStr=nowDate.toString("HH:mm:ss     :  ");
//    in<<dateTimeStr<<encoded<<"\r\n";
//    file.close();
//    //上面把日志数据，写进文件LogInfo.log中
}
}






