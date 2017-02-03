#include "gui_patch.h"
#include <QLabel>
#include <QString>
#include <stdio.h>
#include <QMessageBox>

Patch::Patch(int a, string* liste) : nb_io(a)
{   
    this->setFixedSize(640,64*nb_io);
    this->move(150,100);
    this->setWindowTitle("Patch - DeckLink I/O");
    this->setStyleSheet("QWidget {background-image: url(./leo_2.png) }");
QString temp = NULL;
    for (int i = 0; i<nb_io; i++ )
    {
    temp = QString::fromStdString(liste[i]);
   mLabel= new QLabel(temp, this);
   mLabel->move(13,10+i*60);

   mLabel_out = new QLabel ("OUT", this);
   mLabel_out->move(5, 40+i*60);
   mLabel_in = new QLabel ("IN", this);
   mLabel_in->move(100, 40+i*60);
    mSwitcher[i] = new QSlider(Qt::Horizontal, this);
    mSwitcher[i]->setMaximum(2);
    mSwitcher[i]->setMinimum(0);
    mSwitcher[i]->setMaximumWidth(60);
    mSwitcher[i]->setMinimumWidth(60);
    mSwitcher[i]->move(40,40+i*60);
    mSwitcher[i]->setSliderPosition(1);
    mSwitcher[i]->setEnabled(1);
    mSwitcher[i]->show();
}
    mBouton_conf= new QPushButton(this);
    mBouton_conf->setFixedSize(70,50);
    mBouton_conf->setText("PATCH");
    mBouton_conf->move(160,200);
    mBouton_conf->setCheckable(1);
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
    if (!def) {
        return mPatch_info; }

    else {
        int *a = new int[5];
        a[0] = 0;
        for (int i = 1; i<5; i++)
            a[i] = 2;
        return a;
    }

}

Patch::~Patch()
{

}
