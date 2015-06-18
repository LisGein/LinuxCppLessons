TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    perceptron.cpp

HEADERS += \
    perceptron.h

 QMAKE_CXXFLAGS += -std=c++0x
