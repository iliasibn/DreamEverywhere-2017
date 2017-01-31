#include "gui_pip.h"
#include <iostream>
#include <QLabel>
#include <QDialog>
#include <stdio.h>
using namespace std;

Pipsettings::Pipsettings()
{
    //bool  modeencour = false; // Determine si le PIP est au prog ou en preview (false = pwv true = prg)
    this->setFixedSize(250,300);
    this->move(150,100);
    this->setWindowTitle("Picture-in-picture Settings");

    QLabel *label_taille = new QLabel("Taille",this);
    label_taille->move(10,50);

    QLabel *label_x = new QLabel("Position horizontale",this);
    label_x->move(10,100);

    QLabel *label_y = new QLabel("Position verticale",this);
    label_y->move(10,145);

    slider_taille = new QSlider(Qt::Horizontal, this);
    slider_taille->setMaximum(100);
    slider_taille->setMinimum(0);
    slider_taille->setMaximumWidth(200);
    slider_taille->setMinimumWidth(200);
    slider_taille->move(10,70);
    slider_taille->setEnabled(1);
    slider_taille->show();
     QObject::connect(slider_taille, SIGNAL(valueChanged(int)), this, SLOT (save_settings_pip(int)));

    slider_x = new QSlider(Qt::Horizontal, this);
    slider_x->setRange (-50,50);
    slider_x->setMaximumWidth(200);
    slider_x->setMinimumWidth(200);
    slider_x->move(10,115);
    slider_x->setEnabled(1);
    slider_x->show();
    QObject::connect(slider_x, SIGNAL(valueChanged(int)), this, SLOT (save_settings_pip(int)));

    slider_y = new QSlider(Qt::Horizontal, this);
    slider_y->setRange (-50,50);
    slider_y->setMaximumWidth(200);
    slider_y->setMinimumWidth(200);
    slider_y->move(10,160);
    slider_y->setEnabled(1);
    slider_y->show();
    QObject::connect(slider_y, SIGNAL(valueChanged(int)), this, SLOT (save_settings_pip(int)));


    bouton_switch= new QPushButton(this);
    bouton_switch->setFixedSize(75,75);
    bouton_switch->setText("ON AIR");
    bouton_switch->setCheckable(1);
    bouton_switch->move(75,200);
    bouton_switch->setStyleSheet("background : #008000;");
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

void Pipsettings::invert_pip()
{
    if (!modeencour)
    {
        modeencour = true;
        bouton_switch->setStyleSheet("background : #800000;");
    }
    else {modeencour = false;   bouton_switch->setStyleSheet("background : #008000;");}
    save_settings_pip(1);

}


