#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T14:11:41
#
#-------------------------------------------------

 QT       += core gui network

 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

 TARGET = QtChat
 TEMPLATE = app


 SOURCES += main.cpp\
	 mainwindow.cpp \
    clientnetwork.cpp \
    clientwindow.cpp \
    servernetwork.cpp \
    serverwindow.cpp

 HEADERS  += mainwindow.h \
    clientnetwork.h \
    clientwindow.h \
    servernetwork.h \
    serverwindow.h

 FORMS    += mainwindow.ui

 QMAKE_CXXFLAGS += -std=c++0x
