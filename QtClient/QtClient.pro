#-------------------------------------------------
#
# Project created by QtCreator 2015-07-01T08:28:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stringclient.cpp \
    registration.cpp \
    insetdialog.cpp

HEADERS  += mainwindow.h \
    stringclient.h \
    registration.h \
    insetdialog.h

FORMS    += mainwindow.ui \
    registration.ui \
    insetdialog.ui

INCLUDEPATH += ../Server/include

QMAKE_CXXFLAGS += -std=c++0x
