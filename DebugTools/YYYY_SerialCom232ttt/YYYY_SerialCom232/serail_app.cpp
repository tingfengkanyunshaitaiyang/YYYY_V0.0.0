#include "serail_app.h"
#include "Log.h"

using namespace Logger;



SerialCom* SerailApp::m_pSerialCom = NULL;


void SerailApp::SerailWorkProcess()
{
    while(1)
    {
        Logger::Log::Instance().LogDebug("SerailWorkProcess go!", 0, DEBUG_INFO);
        tSerailWork.msleep(1000);
    }
}


//使用这个自定义线程类 ThreadLib::Activity<SerailApp> tSerailWork; 必须在构造时初始化，否则编译不过。
SerailApp::SerailApp()
    :tSerailWork(this, &SerailApp::SerailWorkProcess)
{
    QString iniPath = "SerailCfg.ini";
    SerailCfg m_icreaderCfg;
#ifdef Q_OS_LINUX
    iniPath = "./SerailCfg.ini";
#endif
    QSettings ini(iniPath, QSettings::IniFormat);
    //通讯配置
    m_icreaderCfg.port = ini.value("/COM/port").toString();
    m_icreaderCfg.baud = ini.value("/COM/baud").toInt();
    QString strTmp = ini.value("/COM/parity").toString();
    if(strTmp.length()==0)
    {
         m_icreaderCfg.parity = 'N';
    }
    else
    {
        m_icreaderCfg.parity = strTmp.toAscii()[0];
    }
    m_icreaderCfg.data_bit = ini.value("/COM/data_bit").toInt();
    m_icreaderCfg.stop_bit = ini.value("/COM/stop_bit").toInt();


#ifdef Q_OS_WIN32
    struct PortSettings comSetting;
    //comSetting.BaudRate = BAUD2400;
    comSetting.BaudRate = BAUD115200;
    comSetting.DataBits = DATA_8;
    comSetting.Parity = PAR_EVEN;
    comSetting.StopBits = STOP_1;
    comSetting.FlowControl =FLOW_OFF;
    comSetting.Timeout_Millisec = 500;
    m_icreaderCfg.port = "COM3";
    m_pSerialCom = new SerialCom(m_icreaderCfg.port, comSetting);
    m_pSerialCom->setParent(this);
#endif
#ifdef Q_OS_LINUX
    SerialCom::SerailPortSettings comSetting;
    comSetting.baud = m_icreaderCfg.baud;
    comSetting.parity = m_icreaderCfg.parity;
    comSetting.data_bit = m_icreaderCfg.data_bit;
    comSetting.stop_bit = m_icreaderCfg.stop_bit;
    m_pSerialCom = new SerialCom(m_icreaderCfg.port,comSetting);
#endif

    Logger::Log::Instance().LogDebug("8888888888888888", 0, DEBUG_INFO);

    m_pSerialCom->Open(1);
    tSerailWork.start();
}

SerailApp::~SerailApp()
{
    m_pSerialCom->Close();
    delete m_pSerialCom;
    m_pSerialCom = NULL;
}
//end of file.