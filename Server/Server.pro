#-------------------------------------------------
#
# Project created by QtCreator 2015-07-01T05:22:40
#
#-------------------------------------------------
QT       += core network

QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServer
TEMPLATE = app
CONFIG   += console

SOURCES += main.cpp \
    stringserver.cpp \
    chatserver.cpp \
    address.cpp

HEADERS  += \
    stringserver.h \
    chatserver.h \
    address.h

FORMS    +=

INCLUDEPATH += ./include

QMAKE_CXXFLAGS += -std=c++0x
