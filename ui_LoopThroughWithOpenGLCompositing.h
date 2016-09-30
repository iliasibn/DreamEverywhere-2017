/********************************************************************************
** Form generated from reading UI file 'LoopThroughWithOpenGLCompositing.ui'
**
** Created: Fri Nov 23 12:16:12 2012
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOOPTHROUGHWITHOPENGLCOMPOSITING_H
#define UI_LOOPTHROUGHWITHOPENGLCOMPOSITING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoopThroughWithOpenGLCompositingDialog
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *LoopThroughWithOpenGLCompositingDialog)
    {
        if (LoopThroughWithOpenGLCompositingDialog->objectName().isEmpty())
            LoopThroughWithOpenGLCompositingDialog->setObjectName(QString::fromUtf8("LoopThroughWithOpenGLCompositingDialog"));
        LoopThroughWithOpenGLCompositingDialog->resize(720, 486);
        verticalLayout = new QVBoxLayout(LoopThroughWithOpenGLCompositingDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        retranslateUi(LoopThroughWithOpenGLCompositingDialog);

        QMetaObject::connectSlotsByName(LoopThroughWithOpenGLCompositingDialog);
    } // setupUi

    void retranslateUi(QDialog *LoopThroughWithOpenGLCompositingDialog)
    {
        LoopThroughWithOpenGLCompositingDialog->setWindowTitle(QApplication::translate("LoopThroughWithOpenGLCompositingDialog", "OpenGL LoopThrough Preview", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoopThroughWithOpenGLCompositingDialog: public Ui_LoopThroughWithOpenGLCompositingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOOPTHROUGHWITHOPENGLCOMPOSITING_H
