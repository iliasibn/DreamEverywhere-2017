#include "gui_keyer.h"
#include <iostream>
#include <QLabel>

using namespace std;
KeyerSettings::KeyerSettings(int nb_bmd)
{
    this->setFixedSize(250,300);
    this->move(150,100);
    this->setWindowTitle("Keyer Settings");

    QLabel *label_seuil = new QLabel("Seuil",this);
    label_seuil->move(10,50);

    QLabel *label_tolerance = new QLabel("Tolerance",this);
    label_tolerance->move(10,100);


    mCombo_current_source = new QComboBox(this);
    QStringList *liste = new QStringList();
    liste->push_back("SOURCE0");
    liste->push_back("SOURCE1");
    liste->push_back("SOURCE2");
    liste->push_back("SOURCE3");
    liste->push_back("SOURCE4");
    liste->push_back("SOURCE5");
    liste->push_back("SOURCE6");
    liste->push_back("SOURCE7");
    liste->push_back("SOURCE8");
    liste->push_back("SOURCE9");

    mCombo_current_source->addItems(*liste);
    mCombo_current_source->setMaximumWidth(150);
    mCombo_current_source->setMaximumHeight(50);
    mCombo_current_source->move(110,5);
    mCombo_current_source->show();

    QObject::connect(mCombo_current_source, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_index_changed(int)));
    mCombo_current_source->hide();


    mColor_picker = new QColorDialog(this);
    mColor_picker->move(50,50);
    QColor *white = new QColor();
    white->setRgb(255,255,255);
    mColor_picker->setCurrentColor(*white);
    QObject::connect(mColor_picker, SIGNAL(currentColorChanged(QColor)), this, SLOT(slot_current_color_changed(QColor)));
    mColor_picker->close();

    mBouton_color_picking = new QPushButton("Couleur d'incrustation",this);
    mBouton_color_picking->move(20,150);

    mBouton_color_picking->setMaximumWidth(200);
    mBouton_color_picking->setMinimumWidth(200);
    mBouton_color_picking->show();
    mBouton_color_picking->setDisabled(1);
    QObject::connect(mBouton_color_picking, SIGNAL(clicked()), this, SLOT(slot_color_picking()));


    mSlider_seuil = new QSlider(Qt::Horizontal, this);
    mSlider_seuil->setMaximum(100);
    mSlider_seuil->setMinimum(0);
    mSlider_seuil->setMaximumWidth(200);
    mSlider_seuil->setMinimumWidth(200);
    mSlider_seuil->move(10,70);
    mSlider_seuil->setEnabled(1);
    mSlider_seuil->show();
    QObject::connect(mSlider_seuil, SIGNAL(valueChanged(int)), this, SLOT(save_settings(int)));


    mSlider_tolerance = new QSlider(Qt::Horizontal, this);
    mSlider_tolerance->setMaximum(100);
    mSlider_tolerance->setMinimum(0);
    mSlider_tolerance->move(10,120);
    mSlider_tolerance->setMaximumWidth(200);
    mSlider_tolerance->setMinimumWidth(200);
    mSlider_tolerance->show();
    QObject::connect(mSlider_tolerance, SIGNAL(valueChanged(int)), this, SLOT(save_settings(int)));



    mCombo_mode = new QComboBox(this);
    mCombo_mode->addItem("Luma Key");
    mCombo_mode->addItem("Chroma Key");
    mCombo_mode->setMaximumWidth(200);
    mCombo_mode->setMinimumWidth(200);
    mCombo_mode->move(20,230);

    QObject::connect(mCombo_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_change_mode(int)));


    current=0;

}

KeyerSettings::~KeyerSettings()
{
    mColor_picker->close();
}

void KeyerSettings::fermez_les_ecoutilles()
{
    mColor_picker->hide();
}

void KeyerSettings::slot_current_color_changed(QColor q) //On sauve les paramètres car la couleur a changé
{
    save_settings(0);
}

void KeyerSettings::slot_color_picking() //faire apparaitre ou disparaitre le color picking
{

    if (mColor_picker->isHidden())
    {
        mColor_picker->show();
    }
    else
    {
        mColor_picker->hide();
    }
}

void KeyerSettings::slot_index_changed(int id)

{
    emit keyer_change_source (id);
}

void KeyerSettings::slot_change_mode(int mode)
{
    if (mode == 0)
    {
        mBouton_color_picking->setDisabled(1);
    }else
        mBouton_color_picking->setEnabled(1);


    save_settings(0);
}

void KeyerSettings::change_current(int newSetting, bool mode, int seuil, int tolerance, QColor color) //Le keyer actuel
{

    current = newSetting;
    mCombo_current_source->setCurrentIndex(newSetting);
    mSlider_tolerance->setValue(tolerance);
    mSlider_seuil->setValue(seuil);
    mColor_picker->setCurrentColor(color);
    if (mode)
    {
        mCombo_mode->setCurrentIndex(1);
        mBouton_color_picking->setEnabled(1);
    }
    else
    {
        mCombo_mode->setCurrentIndex(0);
        mBouton_color_picking->setDisabled(1);
    }

    mColor_picker->close();
}

void KeyerSettings::save_settings(int value)
{

    bool mode=true;
    if (mCombo_mode->currentIndex() == 0) //Soit 0 soit 1 (Luma, chroma)
        mode=false;

    emit keyer_changes(current,mode,mSlider_seuil->value(), mSlider_tolerance->value(), mColor_picker->currentColor());

}
