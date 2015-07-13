QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Perceptron
TEMPLATE = app

LIBS += -pthread
QMAKE_CXXFLAGS += -pthread
QT += widgets
SOURCES += main.cpp \
    perceptron.cpp \
    dataset_t.cpp \
    confusion_matrix.cpp \
    mainwindow.cpp

HEADERS += \
    perceptron.h \
    dataset_t.h \
    confusion_matrix.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

 QMAKE_CXXFLAGS += -std=c++11
