
 QT       += core gui network

 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerForQtChat

TEMPLATE = app

SOURCES += main.cpp \
    network.cpp

HEADERS += \
    network.h

QMAKE_CXXFLAGS += -std=c++0x
