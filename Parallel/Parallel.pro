TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += main.cpp
LIBS += -pthread
QMAKE_CXXFLAGS += -pthread
QMAKE_CXXFLAGS += -std=c++11

