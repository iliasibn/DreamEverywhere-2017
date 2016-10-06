#-------------------------------------------------
#
# Project created by QtCreator 2011-01-14T22:13:15
#
#-------------------------------------------------
#core gui
QT       += core gui widgets

TARGET = BuildOnMe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mltcontroller.cpp \
    visu.cpp

HEADERS  += mainwindow.h \
    mltcontroller.h \
    visu.h

FORMS    +=

mac {
    QT += opengl
    SOURCES += glwidget.cpp
    HEADERS += glwidget.h
}
win32 {
    INCLUDEPATH += include/mlt++ include/mlt
    LIBS += -Llib -lmlt++ -lmlt
} else {
    CONFIG += link_pkgconfig
    PKGCONFIG += mlt++
}

RESOURCES +=
