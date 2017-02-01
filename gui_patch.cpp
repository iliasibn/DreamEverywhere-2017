#include "gui_patch.h"
#include <QLabel>
#include <QString>
#include <stdio.h>
#include <QMessageBox>

Patch::Patch(int a, string* liste, QWidget* parent) : nb_io(a)
{   
    this->setFixedSize(340,64*nb_io);
    this->move(150,100);
    this->setWindowTitle("Patch - DeckLink I/O");
    this->setStyleSheet("background-color: rgb(150,150,150);}");
QString temp = NULL;
    for (int i = 0; i<nb_io; i++ )
    {
   temp = QString::fromStdString(liste[i]);
   mLabel= new QLabel(temp, this);
   mLabel->move(13,10+i*60);

   mLabel_out = new QLabel ("OUT  ", this);
   mLabel_out->move(15, 40+i*60);
   mLabel_in = new QLabel ("  IN", this);
   mLabel_in->move(110, 40+i*60);
    mSwitcher[i] = new QSlider(Qt::Horizontal, this);
    mSwitcher[i]->setMaximum(2);
    mSwitcher[i]->setMinimum(0);
    mSwitcher[i]->move(50,40+i*60);
    mSwitcher[i]->setSliderPosition(1);
    mSwitcher[i]->setEnabled(1);
    mSwitcher[i]->setStyleSheet(
                  "QSlider::groove {"
                  "border: 0px solid #999999;"
                  "background: rgb(115,115,115);"
                  "border-radius: 3px;"
                  "border-top-width: 1px;"
                  "border-top-color: rgb(80,80,80);"
                  "height:15px; width:50px;"
                  "border-top-style: solid; /* just a single line */}"
                  "QSlider::handle::horizontal {"
                  "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC);"
                  "border-bottom-width: 1px;"
                  "border-bottom-color: rgb(130,130,130);"
                  "border-bottom-style: solid; /* just a single line */"
                  "width:15px;"
                  "border-radius: 3px; margin: 0 0; }");
    mSwitcher[i]->show();
}
    mBouton_conf= new QPushButton(this);
    mBouton_conf->setFixedSize(70,70);
    mBouton_conf->setText("PATCH");
    mBouton_conf->move(180,200);
    mBouton_conf->setCheckable(1);
    mBouton_conf->setStyleSheet("QPushButton {background-color: rgb(193,193,193);  "
                                  "border-radius: 35; "
                                  "color: rgb(115,115,115);}" );
    mBouton_conf->show();

    QObject::connect(mBouton_conf, SIGNAL(clicked()), this, SLOT(patch_done()));

}

void Patch::patch_done()
{
    int c = 0;
    mPatch_info = new int[nb_io];
    for (int i = 0; i<nb_io; i++)
    {
        if (mSwitcher[i]->value() == 0)
            c++;
        mPatch_info[i] = mSwitcher[i]->value();

    }
    if (c <= 1)
    {
    this->hide();
    }
    else
    QMessageBox::information(NULL, "Error", "You can't chose more than one output.");

}

int* Patch::access_patch_information(bool def)
{
    int* a;
    if (!def) {
    return mPatch_info; }

    else
        a[0] = 0;
        for (int i = 1; i<5; i++)
            a[i] = 2;
    return a;

}

Patch::~Patch()
{
delete mPatch_info;
}
