#-------------------------------------------------
#
# Project created by QtCreator 2011-01-14T22:13:15
#
#-------------------------------------------------

QT       += core gui widgets opengl multimedia

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
<<<<<<< HEAD
LIBS+= -lGLU -Llib -lmlt++ -lmlt
=======
LIBS+= -lGLU -lGL
>>>>>>> 4f2f84c95c7c72d37d3258ede1a89a491fe434e7

RESOURCES += \
    resources.qrc
