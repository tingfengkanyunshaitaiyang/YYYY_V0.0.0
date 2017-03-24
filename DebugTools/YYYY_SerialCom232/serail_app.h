#ifndef SERAIL_APP_H
#define SERAIL_APP_H
#include <QObject>
#include <QSettings>
#include "SerialCom.h"
#include "Afx.h"
#include "Activity.h"



typedef struct TagSerailCfg
{
    //通讯配置
    QString port;   //串口号
    int baud;       //波特率
    char parity;    //校验位
    int data_bit;   //数据位
    int stop_bit;   //停止位
}SerailCfg;

class SerailApp:public QObject
{
    Q_OBJECT
public:
    SerailApp();
    ~SerailApp();
    static SerialCom *m_pSerialCom;

    Activity<SerailApp> tSerailWork;
    void SerailWorkProcess();
};

#endif // SERAIL_APP_H
//end of file.