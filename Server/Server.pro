TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    networkclient.cpp \
    games.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    networkclient.h \
    games.h
