#include "gui_pip.h"
#include <iostream>
#include <QLabel>
#include <QDialog>
#include <stdio.h>
#include <QVBoxLayout>

using namespace std;

Pipsettings::Pipsettings()
{
    this->resize(250,300);
    this->move(150,100);
    this->setWindowTitle("Picture-in-picture Settings");
    this->setStyleSheet("background-color: rgb(150,150,150);}");

    QVBoxLayout * lyt_pip = new QVBoxLayout(this);
    QLabel *label_taille = new QLabel("SIZE",this);
//    label_taille->move(10,50);
    lyt_pip->addWidget(label_taille, 0, Qt::AlignCenter);

    QLabel *label_x = new QLabel("X POS.",this);
   // label_x->move(10,95);

    QLabel *label_y = new QLabel("Y POS.",this);
    //label_y->move(10,140);

    slider_taille = new QSlider(Qt::Horizontal, this);
    slider_taille->setMaximum(100);
    slider_taille->setMinimum(0);
    slider_taille->setMaximumWidth(200);
    slider_taille->setMinimumWidth(200);
   // slider_taille->move(10,70);
    slider_taille->setEnabled(1);
    unif_slider(slider_taille);

lyt_pip->addWidget(slider_taille, 0, Qt::AlignCenter);

    slider_taille->show();
     QObject::connect(slider_taille, SIGNAL(valueChanged(int)), this, SLOT (save_settings_pip(int)));

    slider_x = new QSlider(Qt::Horizontal, this);
    slider_x->setRange (-50,50);
    slider_x->setMaximumWidth(200);
    slider_x->setMinimumWidth(200);
    //slider_x->move(10,115);
    slider_x->setEnabled(1);
    unif_slider(slider_x);
    lyt_pip->addWidget(label_x, 0, Qt::AlignCenter);
    lyt_pip->addWidget(slider_x, 0, Qt::AlignCenter);

    slider_x->show();
    QObject::connect(slider_x, SIGNAL(valueChanged(int)), this, SLOT (save_settings_pip(int)));

    slider_y = new QSlider(Qt::Horizontal, this);
    slider_y->setRange (-50,50);
    slider_y->setMaximumWidth(200);
    slider_y->setMinimumWidth(200);
   // slider_y->move(10,160);
    slider_y->setEnabled(1);
    unif_slider(slider_y);
    lyt_pip->addWidget(label_y, 0, Qt::AlignCenter);
    lyt_pip->addWidget(slider_y, 0, Qt::AlignCenter);
    slider_y->show();
    QObject::connect(slider_y, SIGNAL(valueChanged(int)), this, SLOT (save_settings_pip(int)));

    bouton_switch= new QPushButton(this);
    bouton_switch->setFixedSize(75,75);
    bouton_switch->setText("SWITCH");
    bouton_switch->setCheckable(1);
    bouton_switch->setStyleSheet("QPushButton {background-color: rgb(150,150,150);  "
                                  "border-radius: 7; "
                                  "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC); "
                                  "color: rgb(115,115,115);"
                                  "border-bottom-width: 1px;"
                                  "border-bottom-color: rgb(130,130,130);"
                                  "border-bottom-style: solid; /* just a single line */}"
                                  "QPushButton:checked { border-style: solid; border-width: 5px; border-color: rgb(255,0,0); }");
  //  bouton_switch->move(75,200);
    lyt_pip->addWidget(bouton_switch, 0, Qt::AlignCenter);
    QObject::connect(bouton_switch, SIGNAL(clicked()), this, SLOT(invert_pip()));
}

Pipsettings::~Pipsettings()
{
    this->close();
}

void Pipsettings::save_settings_pip(int value)
{
int a;
if (!modeencour)
a=0;
else a=1;

emit pip_changes(slider_taille->value(), slider_x->value(), slider_y->value(), a);
}

void Pipsettings::unif_slider(QSlider *_slider)
{
  _slider->setStyleSheet(
                  "QSlider::groove {"
                  "border: 0px solid #999999;"
                  "background: rgb(115,115,115);"
                  "border-radius: 3px;"
                  "border-top-width: 1px;"
                  "border-top-color: rgb(80,80,80);"
                  "height:10px; width:180px;"
                  "border-top-style: solid; /* just a single line */}"
                  "QSlider::handle::horizontal {"
                  "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC);"
                  "border-bottom-width: 1px;"
                  "border-bottom-color: rgb(130,130,130);"
                  "border-bottom-style: solid; /* just a single line */"
                  "width:10px;"
                  "border-radius: 3px; margin: 0 0; }");
}

void Pipsettings::invert_pip()
{
    if (!modeencour)
    {
        modeencour = true;
    }
    else {modeencour = false; }
    save_settings_pip(1);

}


