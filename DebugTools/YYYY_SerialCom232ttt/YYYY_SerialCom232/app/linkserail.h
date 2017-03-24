#ifndef LINKSERAIL_H
#define LINKSERAIL_H

#include <QDebug>
#include "SerialCom.h"

class LinkSerail:public QObject
{
public:
    LinkSerail();
    ~LinkSerail();
    static SerialCom *m_pSerialCom;
};

#endif // LINKSERAIL_H