TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    perceptron.cpp \
    dataset_t.cpp \
    confusion_matrix.cpp

HEADERS += \
    perceptron.h \
    dataset_t.h \
    confusion_matrix.h

 QMAKE_CXXFLAGS += -std=c++0x
