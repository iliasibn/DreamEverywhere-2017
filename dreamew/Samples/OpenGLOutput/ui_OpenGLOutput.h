/********************************************************************************
** Form generated from reading UI file 'OpenGLOutput.ui'
**
** Created: Mon Mar 23 17:57:32 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLOUTPUT_H
#define UI_OPENGLOUTPUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGLOutputDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *previewContainer;

    void setupUi(QDialog *OpenGLOutputDialog)
    {
        if (OpenGLOutputDialog->objectName().isEmpty())
            OpenGLOutputDialog->setObjectName(QString::fromUtf8("OpenGLOutputDialog"));
        OpenGLOutputDialog->resize(720, 486);
        verticalLayout = new QVBoxLayout(OpenGLOutputDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        previewContainer = new QWidget(OpenGLOutputDialog);
        previewContainer->setObjectName(QString::fromUtf8("previewContainer"));

        verticalLayout->addWidget(previewContainer);


        retranslateUi(OpenGLOutputDialog);

        QMetaObject::connectSlotsByName(OpenGLOutputDialog);
    } // setupUi

    void retranslateUi(QDialog *OpenGLOutputDialog)
    {
        OpenGLOutputDialog->setWindowTitle(QApplication::translate("OpenGLOutputDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        previewContainer->setStyleSheet(QApplication::translate("OpenGLOutputDialog", "background-color: #000", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OpenGLOutputDialog: public Ui_OpenGLOutputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLOUTPUT_H
