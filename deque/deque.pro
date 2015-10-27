TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    deque.cpp \
    node.cpp \
    partdata.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    deque.h \
    node.h \
    partdata.h

