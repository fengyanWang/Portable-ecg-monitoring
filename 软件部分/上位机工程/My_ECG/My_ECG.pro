#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T08:53:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = My_ECG
TEMPLATE = app


SOURCES += main.cpp\
        myecg.cpp \
    adduser.cpp \
    qextserialbase.cpp \
    qextserialport.cpp \
    win_qextserialport.cpp \
    delateuser.cpp \
    modifyuser.cpp \
    modifyuser_1.cpp \
    logindialog.cpp \
    changepasswd.cpp \
    aboutauthor.cpp

HEADERS  += myecg.h \
    adduser.h \
    qextserialbase.h \
    qextserialport.h \
    win_qextserialport.h \
    delateuser.h \
    modifyuser.h \
    modifyuser_1.h \
    logindialog.h \
    changepasswd.h \
    aboutauthor.h \
    path.h

FORMS    += myecg.ui \
    adduser.ui \
    delateuser.ui \
    modifyuser.ui \
    modifyuser_1.ui \
    logindialog.ui \
    changepasswd.ui \
    aboutauthor.ui

RESOURCES += \
    picture_1.qrc




CONFIG += qwt
DEFINES += QT_DLL QWT_DLL
LIBS += -L"F:\QT5.5.1\qctr\qwt-6.1.3\qwt-6.1.3\lib" -lqwtd
LIBS += -L"F:\QT5.5.1\qctr\qwt-6.1.3\qwt-6.1.3\lib" -lqwt
INCLUDEPATH += F:\QT5.5.1\5.5\mingw492_32\include\QWT
