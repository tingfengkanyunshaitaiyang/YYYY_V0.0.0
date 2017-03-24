#include "SerialCom.h"
#include <QApplication>
#include <QTime>

#ifdef Q_OS_WIN32
SerialCom::SerialCom(QString portName, struct PortSettings comSetting)
    :myCom(NULL),
    m_bOpend(false)
{
    myComPortName = portName;
    myComSetting = comSetting;
}
#endif

#ifdef Q_OS_LINUX
SerialCom::SerialCom(QString portName, SerailPortSettings comSetting)
    :m_pCom(NULL),
    m_bOpend(false)
{
    myComPortName = portName;
    m_comSetting = comSetting;

    m_pCom = new Linux_SerailCom();
}
#endif

SerialCom::~SerialCom()
{
#ifdef Q_OS_LINUX
    m_pCom->Close();
    delete m_pCom;
    m_pCom = NULL;
#endif

#ifdef Q_OS_WIN32
    myCom->close();
    delete myCom;
    myCom = NULL;
#endif

}

bool SerialCom::IsOpen()
{
    return m_bOpend;
}

int SerialCom::Open(int flag)
{
    char *portName = (char*)(myComPortName.toStdString().c_str());
#ifdef Q_OS_LINUX
    if(m_pCom->Open(portName,
                   m_comSetting.baud,
                   m_comSetting.parity,
                   m_comSetting.data_bit,
                   m_comSetting.stop_bit,flag)<0)
    {
        qDebug()<<QString("Open %1 failed").arg(myComPortName);
        m_bOpend = false;
        return -1;
    }
    else
    {
        qDebug()<<QString("Open %1 success").arg(myComPortName);
        m_bOpend = true;
        return 1;
    }
#endif

#ifdef Q_OS_WIN32
    myCom = new Win_QextSerialPort(myComPortName,QextSerialBase::EventDriven);

    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    myCom->open(QIODevice::ReadWrite);

    myCom->setBaudRate(myComSetting.BaudRate);
    //设置波特率
    myCom->setDataBits(myComSetting.DataBits);
    //设置数据位
    myCom->setParity(myComSetting.Parity);
    //设置奇偶校验
    myCom->setStopBits(myComSetting.StopBits);
    //设置停止位
    myCom->setFlowControl(myComSetting.FlowControl); //设置数据流控制，我们使用无数据流控制的默认设置
    myCom->setTimeout(myComSetting.Timeout_Millisec); //设置延时
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作


    return 1;
#endif


}

void SerialCom::Close()
{
#ifdef Q_OS_LINUX
    m_pCom->Close();
#endif

#ifdef Q_OS_WIN326
    myCom->close();
#endif

}

void SerialCom::readMyCom()
{
    QApplication::postEvent(this->parent(), new QEvent(CustomEvent_SerialComRcvData));
}

int SerialCom::ReadData(char *data, const int len)
{
#ifdef Q_OS_LINUX
    if(m_pCom->IsOpen())
    {
        int timeout = 800;//500;
        int rcvLen = 0;
        int flag = 0;
        QDateTime dieTime = QDateTime::currentDateTime().addMSecs(timeout);
        QDateTime timeLine;//每个字节间的接收间隔时间
        do
        {
            char tData[100]={0};
            int tlen = 0;
            tlen = m_pCom->Read(tData,sizeof(tData));
            if(tlen>0)
            {
                flag = 1;
                timeLine = QDateTime::currentDateTime().addMSecs(20);
                memcpy(&data[rcvLen],tData,tlen);
                rcvLen += tlen;
            }
            else
            {
                if(flag==1)
                {
                    if(QDateTime::currentDateTime() > timeLine)
                    {
                        break;
                    }
                    else
                    {
                    }
                }
                else
                {
                }
            }

        }
        while ( QDateTime::currentDateTime() < dieTime );

       return rcvLen;
    }
    else
    {
        this->Open();
    }
#endif

#ifdef Q_OS_WIN32
    if(myCom->isOpen())
    {
        int timeout = 500;
        int rcvLen = 0;
        int flag = 0;
        QDateTime dieTime = QDateTime::currentDateTime().addMSecs(timeout);
        QDateTime timeLine;//每个字节间的接收间隔时间
        do
        {
            char tData[100]={0};
            int tlen = 0;
            tlen = myCom->read(tData,sizeof(tData));

            if(tlen>0)
            {
                flag = 1;
                timeLine = QDateTime::currentDateTime().addMSecs(20);
                memcpy(&data[rcvLen],tData,tlen);
                rcvLen += tlen;
            }
            else
            {
                if(flag==1)
                {
                    if(QDateTime::currentDateTime() > timeLine)
                    {
                        break;
                    }
                }
            }

        }
        while ( QDateTime::currentDateTime() < dieTime );

       return rcvLen;
    }

    return 0;
#endif
}

int SerialCom::WriteData(char *data, const int len)
{
#ifdef Q_OS_LINUX
    if(m_pCom->IsOpen())
    {
        return m_pCom->Write(data,len);
    }
    else
    {
        this->Open();
    }
#endif

#ifdef Q_OS_WIN32
    if(myCom->isOpen())
    {
       return myCom->write(data,len);
    }

    return 0;
#endif
}

void SerialCom::ClearBuf()
{
    char buf[128]={0};

#ifdef Q_OS_LINUX
    if(m_pCom->IsOpen())
    {
       while(m_pCom->Read(buf,sizeof(buf))>0);
    }
    else
    {
       this->Open();
    }

#endif

#ifdef Q_OS_WIN32
    if(myCom->isOpen())
    {
        while(myCom->read(buf,sizeof(buf))>0);
    }
#endif
}
