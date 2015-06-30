TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    networkserver.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    networkserver.h
