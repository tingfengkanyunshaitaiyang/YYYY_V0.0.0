#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T14:04:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YYYY_SerialCom232
TEMPLATE = app




SOURCES += main.cpp\
        dialog.cpp \
    serail_app.cpp \
    SerialCom/SerialCom.cpp \
    YYYY_LIB/Log.cpp


HEADERS  += dialog.h \
    serail_app.h \
    SerialCom/SerialCom.h \
    YYYY_LIB/Afx.h \
    YYYY_LIB/Activity.h \
    YYYY_LIB/call_once.h \
    YYYY_LIB/Log.h \
    YYYY_LIB/Singleton.h



unix:{
HEADERS += SerialCom/Linux_SerailCom.h
SOURCES += SerialCom/Linux_SerailCom.cpp

}

win32:{
HEADERS += SerialCom/win_qextserialport.h \
    SerialCom/qextserialbase.h \
    SerialCom/qextserialport.h
SOURCES += SerialCom/win_qextserialport.cpp \
    SerialCom/qextserialbase.cpp \
    SerialCom/qextserialport.cpp
}

INCLUDEPATH += SerialCom/ \
                app/ \
                YYYY_LIB/ \
#end of file.