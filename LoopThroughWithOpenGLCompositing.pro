 TEMPLATE = app
LANGUAGE = C++
CONFIG += qt \
    opengl
QT += opengl
INCLUDEPATH = ./include

LIBS += -lGLU
LIBS += -ldl
HEADERS = ./include/DeckLinkAPIDispatch.cpp \
    LoopThroughWithOpenGLCompositing.h \
    OpenGLComposite.h \
    GLExtensions.h \
    gui_keyer.h \
    gui_panel.h \
    gui_glwindows.h \
    gui_pip.h \
    gui_patch.h \
    carte_bmd.h \
    info_carte.h \
    mainwindow.h \
    mltcontroller.h
SOURCES = main.cpp \
    ./include/DeckLinkAPIDispatch.cpp \
    LoopThroughWithOpenGLCompositing.cpp \
    OpenGLComposite.cpp \
    GLExtensions.cpp \
    loader.cpp \
    gui_keyer.cpp \
    gui_panel.cpp \
    gui_glwindows.cpp \
    gui_pip.cpp \
    gui_patch.cpp \
    carte_bmd.cpp \
    OpenGLDessin.cpp \
    mainwindow.cpp \
    mltcontroller.cpp

FORMS    += mainwindow.ui

CONFIG+=c++11 link_pkgconfig
PKGCONFIG += mlt++
QMAKE_CXXFLAGS += -std=c++11

FORMS += \
    mainwindow.ui
