TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    unique_ptr.cpp \
    auto_ptr.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    unique_ptr.h \
    auto_ptr.h

CONFIG += c++11
