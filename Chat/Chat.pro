TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    networkserver.cpp \
    networkclient.cpp

HEADERS += \
    networkserver.h \
    networkclient.h \
    baseconnection.h

