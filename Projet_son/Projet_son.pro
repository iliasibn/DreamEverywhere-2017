#-------------------------------------------------
#
# Project created by QtCreator 2017-01-11T14:48:12
#
#-------------------------------------------------

QT       += core gui
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_son
TEMPLATE = app
INCLUDEPATH = ./include
SOURCES += main.cpp\
        mainwindow.cpp


HEADERS  += mainwindow.h

unix|win32: LIBS += -lrtaudio
