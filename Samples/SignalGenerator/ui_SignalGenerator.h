/********************************************************************************
** Form generated from reading UI file 'SignalGenerator.ui'
**
** Created: Mon Mar 23 17:18:03 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNALGENERATOR_H
#define UI_SIGNALGENERATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignalGeneratorDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *outputSignalPopup;
    QLabel *label_2;
    QComboBox *audioChannelPopup;
    QLabel *label_3;
    QComboBox *audioSampleDepthPopup;
    QLabel *label_4;
    QComboBox *videoFormatPopup;
    QWidget *previewContainer;
    QPushButton *startButton;

    void setupUi(QDialog *SignalGeneratorDialog)
    {
        if (SignalGeneratorDialog->objectName().isEmpty())
            SignalGeneratorDialog->setObjectName(QString::fromUtf8("SignalGeneratorDialog"));
        SignalGeneratorDialog->resize(600, 215);
        SignalGeneratorDialog->setMinimumSize(QSize(600, 215));
        SignalGeneratorDialog->setMaximumSize(QSize(16000, 16000));
        gridLayout = new QGridLayout(SignalGeneratorDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(SignalGeneratorDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setMinimumSize(QSize(311, 150));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(9, 9, 9, 9);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        outputSignalPopup = new QComboBox(groupBox);
        outputSignalPopup->setObjectName(QString::fromUtf8("outputSignalPopup"));
        outputSignalPopup->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, outputSignalPopup);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        audioChannelPopup = new QComboBox(groupBox);
        audioChannelPopup->setObjectName(QString::fromUtf8("audioChannelPopup"));
        audioChannelPopup->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(1, QFormLayout::FieldRole, audioChannelPopup);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        audioSampleDepthPopup = new QComboBox(groupBox);
        audioSampleDepthPopup->setObjectName(QString::fromUtf8("audioSampleDepthPopup"));
        audioSampleDepthPopup->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(2, QFormLayout::FieldRole, audioSampleDepthPopup);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        videoFormatPopup = new QComboBox(groupBox);
        videoFormatPopup->setObjectName(QString::fromUtf8("videoFormatPopup"));
        videoFormatPopup->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(3, QFormLayout::FieldRole, videoFormatPopup);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        previewContainer = new QWidget(SignalGeneratorDialog);
        previewContainer->setObjectName(QString::fromUtf8("previewContainer"));
        previewContainer->setMinimumSize(QSize(241, 151));
        previewContainer->setAutoFillBackground(false);

        gridLayout->addWidget(previewContainer, 0, 1, 1, 1);

        startButton = new QPushButton(SignalGeneratorDialog);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setMinimumSize(QSize(91, 32));
        startButton->setMaximumSize(QSize(91, 32));

        gridLayout->addWidget(startButton, 1, 0, 1, 1);


        retranslateUi(SignalGeneratorDialog);

        QMetaObject::connectSlotsByName(SignalGeneratorDialog);
    } // setupUi

    void retranslateUi(QDialog *SignalGeneratorDialog)
    {
        SignalGeneratorDialog->setWindowTitle(QApplication::translate("SignalGeneratorDialog", "Signal Generator", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SignalGeneratorDialog", "Properties", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SignalGeneratorDialog", "Output Signal:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SignalGeneratorDialog", "Audio Channels:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SignalGeneratorDialog", "Audio Depth:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SignalGeneratorDialog", "Video Format:", 0, QApplication::UnicodeUTF8));
        previewContainer->setStyleSheet(QApplication::translate("SignalGeneratorDialog", "background-color: #000", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("SignalGeneratorDialog", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SignalGeneratorDialog: public Ui_SignalGeneratorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNALGENERATOR_H
