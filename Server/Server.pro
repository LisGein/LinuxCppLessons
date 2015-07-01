#-------------------------------------------------
#
# Project created by QtCreator 2015-07-01T05:22:40
#
#-------------------------------------------------
QT       += core network

QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app
CONFIG   += console

SOURCES += main.cpp \
    server.cpp \
    stringserver.cpp

HEADERS  += \
    server.h \
    stringserver.h

FORMS    +=

INCLUDEPATH += ./include
