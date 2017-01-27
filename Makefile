#############################################################################
# Makefile for building: LoopThroughWithOpenGLCompositing
# Generated by qmake (2.01a) (Qt 4.8.6) on: Thu Jan 19 14:11:59 2017
# Project:  LoopThroughWithOpenGLCompositing.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile LoopThroughWithOpenGLCompositing.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -D_REENTRANT -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -std=c++11 -O2 -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -Iinclude -I/usr/include/mlt++ -I/usr/include/mlt -I/usr/X11R6/include -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/X11R6/lib -L/usr/lib/x86_64-linux-gnu -lGLU -ldl -L/usr/lib/x86_64-linux-gnu -lmlt++ -lmlt -lGL -lQtOpenGL -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		include/DeckLinkAPIDispatch.cpp \
		LoopThroughWithOpenGLCompositing.cpp \
		OpenGLComposite.cpp \
		GLExtensions.cpp \
		gui_keyer.cpp \
		gui_panel.cpp \
		gui_glwindows.cpp \
		gui_pip.cpp \
		gui_patch.cpp \
		mainwindow.cpp \
		mltcontroller.cpp moc_LoopThroughWithOpenGLCompositing.cpp \
		moc_OpenGLComposite.cpp \
		moc_gui_keyer.cpp \
		moc_gui_panel.cpp \
		moc_gui_glwindows.cpp \
		moc_gui_pip.cpp \
		moc_gui_patch.cpp \
		moc_carte_bmd.cpp \
		moc_mainwindow.cpp \
		moc_mltcontroller.cpp
OBJECTS       = main.o \
		DeckLinkAPIDispatch.o \
		LoopThroughWithOpenGLCompositing.o \
		OpenGLComposite.o \
		GLExtensions.o \
		gui_keyer.o \
		gui_panel.o \
		gui_glwindows.o \
		gui_pip.o \
		gui_patch.o \
		mainwindow.o \
		mltcontroller.o \
		moc_LoopThroughWithOpenGLCompositing.o \
		moc_OpenGLComposite.o \
		moc_gui_keyer.o \
		moc_gui_panel.o \
		moc_gui_glwindows.o \
		moc_gui_pip.o \
		moc_gui_patch.o \
		moc_carte_bmd.o \
		moc_mainwindow.o \
		moc_mltcontroller.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/link_pkgconfig.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		LoopThroughWithOpenGLCompositing.pro
QMAKE_TARGET  = LoopThroughWithOpenGLCompositing
DESTDIR       = 
TARGET        = LoopThroughWithOpenGLCompositing

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: LoopThroughWithOpenGLCompositing.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/link_pkgconfig.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile LoopThroughWithOpenGLCompositing.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/link_pkgconfig.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile LoopThroughWithOpenGLCompositing.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/LoopThroughWithOpenGLCompositing1.0.0 || $(MKDIR) .tmp/LoopThroughWithOpenGLCompositing1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/LoopThroughWithOpenGLCompositing1.0.0/ && $(COPY_FILE) --parents include/DeckLinkAPIDispatch.cpp LoopThroughWithOpenGLCompositing.h OpenGLComposite.h GLExtensions.h gui_keyer.h gui_panel.h gui_glwindows.h gui_pip.h gui_patch.h carte_bmd.h info_carte.h mainwindow.h mltcontroller.h .tmp/LoopThroughWithOpenGLCompositing1.0.0/ && $(COPY_FILE) --parents main.cpp include/DeckLinkAPIDispatch.cpp LoopThroughWithOpenGLCompositing.cpp OpenGLComposite.cpp GLExtensions.cpp gui_keyer.cpp gui_panel.cpp gui_glwindows.cpp gui_pip.cpp gui_patch.cpp mainwindow.cpp mltcontroller.cpp .tmp/LoopThroughWithOpenGLCompositing1.0.0/ && $(COPY_FILE) --parents mainwindow.ui mainwindow.ui .tmp/LoopThroughWithOpenGLCompositing1.0.0/ && (cd `dirname .tmp/LoopThroughWithOpenGLCompositing1.0.0` && $(TAR) LoopThroughWithOpenGLCompositing1.0.0.tar LoopThroughWithOpenGLCompositing1.0.0 && $(COMPRESS) LoopThroughWithOpenGLCompositing1.0.0.tar) && $(MOVE) `dirname .tmp/LoopThroughWithOpenGLCompositing1.0.0`/LoopThroughWithOpenGLCompositing1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/LoopThroughWithOpenGLCompositing1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_LoopThroughWithOpenGLCompositing.cpp moc_OpenGLComposite.cpp moc_gui_keyer.cpp moc_gui_panel.cpp moc_gui_glwindows.cpp moc_gui_pip.cpp moc_gui_patch.cpp moc_carte_bmd.cpp moc_mainwindow.cpp moc_mltcontroller.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_LoopThroughWithOpenGLCompositing.cpp moc_OpenGLComposite.cpp moc_gui_keyer.cpp moc_gui_panel.cpp moc_gui_glwindows.cpp moc_gui_pip.cpp moc_gui_patch.cpp moc_carte_bmd.cpp moc_mainwindow.cpp moc_mltcontroller.cpp
moc_LoopThroughWithOpenGLCompositing.cpp: OpenGLComposite.h \
		gui_panel.h \
		gui_keyer.h \
		gui_pip.h \
		carte_bmd.h \
		info_carte.h \
		gui_patch.h \
		mainwindow.h \
		mltcontroller.h \
		LoopThroughWithOpenGLCompositing.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) LoopThroughWithOpenGLCompositing.h -o moc_LoopThroughWithOpenGLCompositing.cpp

moc_OpenGLComposite.cpp: OpenGLComposite.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) OpenGLComposite.h -o moc_OpenGLComposite.cpp

moc_gui_keyer.cpp: gui_keyer.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) gui_keyer.h -o moc_gui_keyer.cpp

moc_gui_panel.cpp: gui_keyer.h \
		gui_pip.h \
		gui_panel.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) gui_panel.h -o moc_gui_panel.cpp

moc_gui_glwindows.cpp: gui_glwindows.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) gui_glwindows.h -o moc_gui_glwindows.cpp

moc_gui_pip.cpp: gui_pip.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) gui_pip.h -o moc_gui_pip.cpp

moc_gui_patch.cpp: gui_patch.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) gui_patch.h -o moc_gui_patch.cpp

moc_carte_bmd.cpp: info_carte.h \
		carte_bmd.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) carte_bmd.h -o moc_carte_bmd.cpp

moc_mainwindow.cpp: mltcontroller.h \
		mainwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_mltcontroller.cpp: mltcontroller.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mltcontroller.h -o moc_mltcontroller.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_mainwindow.h: mainwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp LoopThroughWithOpenGLCompositing.h \
		OpenGLComposite.h \
		gui_panel.h \
		gui_keyer.h \
		gui_pip.h \
		carte_bmd.h \
		info_carte.h \
		gui_patch.h \
		mainwindow.h \
		mltcontroller.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

DeckLinkAPIDispatch.o: include/DeckLinkAPIDispatch.cpp include/DeckLinkAPI.h \
		include/LinuxCOM.h \
		include/DeckLinkAPITypes.h \
		include/DeckLinkAPIModes.h \
		include/DeckLinkAPIDiscovery.h \
		include/DeckLinkAPIConfiguration.h \
		include/DeckLinkAPIDeckControl.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o DeckLinkAPIDispatch.o include/DeckLinkAPIDispatch.cpp

LoopThroughWithOpenGLCompositing.o: LoopThroughWithOpenGLCompositing.cpp LoopThroughWithOpenGLCompositing.h \
		OpenGLComposite.h \
		gui_panel.h \
		gui_keyer.h \
		gui_pip.h \
		carte_bmd.h \
		info_carte.h \
		gui_patch.h \
		mainwindow.h \
		mltcontroller.h \
		gui_glwindows.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LoopThroughWithOpenGLCompositing.o LoopThroughWithOpenGLCompositing.cpp

OpenGLComposite.o: OpenGLComposite.cpp OpenGLComposite.h \
		GLExtensions.h \
		OpenGLDessin.cpp \
		carte_bmd.cpp \
		carte_bmd.h \
		info_carte.h \
		LoopThroughWithOpenGLCompositing.h \
		gui_panel.h \
		gui_keyer.h \
		gui_pip.h \
		gui_patch.h \
		mainwindow.h \
		mltcontroller.h \
		loader.cpp \
		gui_glwindows.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o OpenGLComposite.o OpenGLComposite.cpp

GLExtensions.o: GLExtensions.cpp GLExtensions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GLExtensions.o GLExtensions.cpp

gui_keyer.o: gui_keyer.cpp gui_keyer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gui_keyer.o gui_keyer.cpp

gui_panel.o: gui_panel.cpp gui_panel.h \
		gui_keyer.h \
		gui_pip.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gui_panel.o gui_panel.cpp

gui_glwindows.o: gui_glwindows.cpp gui_glwindows.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gui_glwindows.o gui_glwindows.cpp

gui_pip.o: gui_pip.cpp gui_pip.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gui_pip.o gui_pip.cpp

gui_patch.o: gui_patch.cpp gui_patch.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gui_patch.o gui_patch.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		mltcontroller.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

mltcontroller.o: mltcontroller.cpp mltcontroller.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mltcontroller.o mltcontroller.cpp

moc_LoopThroughWithOpenGLCompositing.o: moc_LoopThroughWithOpenGLCompositing.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_LoopThroughWithOpenGLCompositing.o moc_LoopThroughWithOpenGLCompositing.cpp

moc_OpenGLComposite.o: moc_OpenGLComposite.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_OpenGLComposite.o moc_OpenGLComposite.cpp

moc_gui_keyer.o: moc_gui_keyer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gui_keyer.o moc_gui_keyer.cpp

moc_gui_panel.o: moc_gui_panel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gui_panel.o moc_gui_panel.cpp

moc_gui_glwindows.o: moc_gui_glwindows.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gui_glwindows.o moc_gui_glwindows.cpp

moc_gui_pip.o: moc_gui_pip.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gui_pip.o moc_gui_pip.cpp

moc_gui_patch.o: moc_gui_patch.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gui_patch.o moc_gui_patch.cpp

moc_carte_bmd.o: moc_carte_bmd.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_carte_bmd.o moc_carte_bmd.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_mltcontroller.o: moc_mltcontroller.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mltcontroller.o moc_mltcontroller.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

