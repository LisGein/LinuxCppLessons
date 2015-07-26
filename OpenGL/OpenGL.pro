#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T22:50:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    datamodel.cpp \
    point_t.cpp \
    matrix.cpp

HEADERS  += mainwindow.h \
    datamodel.h \
    point_t.h \
    matrix.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
