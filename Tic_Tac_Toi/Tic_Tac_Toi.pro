TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    networkclient.cpp \
    game.cpp \
    networkserver.cpp \
    point_t.cpp \
    baseconnection.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    networkclient.h \
    game.h \
    networkserver.h \
    point_t.h \
    baseconnection.h
