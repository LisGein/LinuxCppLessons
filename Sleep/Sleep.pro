#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T19:55:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sleep
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataalternativereality.cpp \
    labyrinth.cpp \
    cell_labyrinth.cpp

HEADERS  += mainwindow.h \
    dataalternativereality.h \
    labyrinth.h \
    cell_labyrinth.h

FORMS    += mainwindow.ui \
    dataalternativereality.ui
QMAKE_CXXFLAGS += -std=c++11
