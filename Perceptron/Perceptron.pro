TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    perceptron.cpp \
    dataset_t.cpp

HEADERS += \
    perceptron.h \
    dataset_t.h

 QMAKE_CXXFLAGS += -std=c++0x
