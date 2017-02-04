/********************************************************************************
** Form generated from reading UI file 'gui_mp.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_MP_H
#define UI_GUI_MP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>



QT_BEGIN_NAMESPACE

class Ui_gui_mp
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionPlay;
    QAction *actionPause;
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *gui_mp)
    {
        if (gui_mp->objectName().isEmpty())
            gui_mp->setObjectName(QString::fromUtf8("gui_mp"));
        gui_mp->resize(854, 604);
        actionOpen = new QAction(gui_mp);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/document-open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionExit = new QAction(gui_mp);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionPlay = new QAction(gui_mp);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/media-playback-start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlay->setIcon(icon1);
        actionPause = new QAction(gui_mp);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/media-playback-pause.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon2);
        centralWidget = new QWidget(gui_mp);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(730, 480, 113, 27));
        gui_mp->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(gui_mp);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 854, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        gui_mp->setMenuBar(menuBar);
        mainToolBar = new QToolBar(gui_mp);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        gui_mp->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(gui_mp);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        gui_mp->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExit);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionPlay);
        mainToolBar->addAction(actionPause);

        retranslateUi(gui_mp);
        QObject::connect(actionExit, SIGNAL(triggered()), gui_mp, SLOT(close()));

        QMetaObject::connectSlotsByName(gui_mp);
    } // setupUi

    void retranslateUi(QMainWindow *gui_mp)
    {
        gui_mp->setWindowTitle(QApplication::translate("gui_mp", "gui_mp", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("gui_mp", "&Open...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("gui_mp", "Open file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("gui_mp", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("gui_mp", "E&xit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("gui_mp", "Quit the application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setShortcut(QApplication::translate("gui_mp", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionPlay->setText(QApplication::translate("gui_mp", "Play", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPlay->setToolTip(QApplication::translate("gui_mp", "Start playback", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPlay->setShortcut(QApplication::translate("gui_mp", "Space", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("gui_mp", "Pause", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPause->setToolTip(QApplication::translate("gui_mp", "Pause playback", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPause->setShortcut(QApplication::translate("gui_mp", "Backspace", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("gui_mp", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gui_mp: public Ui_gui_mp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_MP_H
