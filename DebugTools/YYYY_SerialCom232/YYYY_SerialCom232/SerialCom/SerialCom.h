#ifndef SERIALCOM_H
#define SERIALCOM_H

//#include "AtcAfx.h"
#include <QDebug>
#include <QEvent>
#include <QTimer>

#ifdef Q_OS_LINUX
#include "Linux_SerailCom.h"
#endif
#ifdef Q_OS_WIN32
#include "win_qextserialport.h"
#endif

const QEvent::Type CustomEvent_SerialComRcvData = (QEvent::Type)6001;

/*******************************************************************************
 Copyright (c), Shenzhen auto electric power plant Co., Ltd.

 类    名：SerialCom
 版    本：1.0
 功    能：串口类
 描    述：

 历史记录：
 日期         作者      版本   描述
 2016-03-19  zhucw    1.0.0  创建类框架
 2016-03-19  zhucw    1.0.0  完成代码
*******************************************************************************/
class SerialCom:public QObject
{
    Q_OBJECT
public:

#ifdef Q_OS_WIN32
    SerialCom(QString portName, struct PortSettings comSetting);
#endif

#ifdef Q_OS_LINUX
    typedef struct
    {
        int baud;       //波特率
        char parity;    //校验位
        int data_bit;   //数据位
        int stop_bit;   //停止位
    }SerailPortSettings;
    SerialCom(QString portName, SerailPortSettings comSetting);
#endif
    ~SerialCom();

    int Open(int flag=0/*0阻塞 其它非阻塞*/);
    void Close();

    int ReadData(char *data, const int len);
    int WriteData(char* data,const int len);
    void ClearBuf();
    bool IsOpen();


    /***************************************************************************
    函 数 名： GetDefaultSetting
    功    能： 获取默认串口配置
    描    述：
    输入参数： 无
    输出参数： 无
    返 回 值： 无
    作 成 者：zhucw
    作成日期：2016/03/19
    ***************************************************************************/
    #ifdef Q_OS_WIN32
    static struct PortSettings GetDefaultSetting()
    {
        struct PortSettings comSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
        return comSetting;
    }
    #endif

#ifdef Q_OS_LINUX
    static SerailPortSettings GetDefaultSetting()
    {
        SerailPortSettings comSetting = {9600,'N',8,1};
        return comSetting;
    }
#endif

private:

#ifdef Q_OS_LINUX
    Linux_SerailCom *m_pCom; //声明串口对象
    SerailPortSettings m_comSetting;
#endif

#ifdef Q_OS_WIN32
    Win_QextSerialPort *myCom; //声明串口对象
    //串口设置
    struct PortSettings myComSetting;
#endif

    //串口号
    QString myComPortName;
    bool m_bOpend;

private slots:
    void readMyCom();          //声明读串口的槽函数


};

#endif // SERIALCOM_H
