#-------------------------------------------------
#
# Project created by QtCreator 2011-01-14T22:13:15
#
#-------------------------------------------------

QT       += core gui widgets opengl

TARGET = BuildOnMe
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mltcontroller.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    mltcontroller.h \
    glwidget.h

FORMS    += mainwindow.ui

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
LIBS+= -lGLU -Llib -lmlt++ -lmlt

RESOURCES += \
    resources.qrc
