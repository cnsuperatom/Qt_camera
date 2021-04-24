#-------------------------------------------------
#
# Project created by QtCreator 2020-11-07T16:37:16
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer
CONFIG   += qaxcontainer

TARGET = EloamCamera
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    EloamCamera.cpp \
    eloamcomlib.cpp \
    FileLog.cpp \
    QUtilityBox.cpp

HEADERS  += MainWindow.h \
    EloamCamera.h \
    eloamcomlib.h \
    FileLog.h \
    QUtilityBox.h

FORMS    += MainWindow.ui \
    EloamCamera.ui
