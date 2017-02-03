 TEMPLATE = app
LANGUAGE = C++
CONFIG += qt \
    opengl
QT += opengl
QT += widgets
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
    colorwheel.h \
    gui_ingevision.h \
    color_data.h \
    mltcontroller.h \
    gui_mp.h \
    gui_start.h

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
    colorwheel.cpp \
    gui_ingevision.cpp \
    mltcontroller.cpp \
    gui_mp.cpp \
    gui_start.cpp

FORMS    +=


CONFIG+=c++11 link_pkgconfig
PKGCONFIG += mlt++
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    fragment_shader.qrc

FORMS +=

