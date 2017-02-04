#include "gui_keyer.h"
#include <iostream>
#include <QLabel>

using namespace std;
KeyerSettings::KeyerSettings(QWidget* parent, int nb_bmd)
{
    //this->setFixedSize(250,300);
    this->move(150,100);
    this->setWindowTitle("Keyer Settings");
    this->setStyleSheet("background-color: rgb(150,150,150);}");

    QVBoxLayout * lyt_key = new QVBoxLayout(this);

    QLabel *label_seuil = new QLabel("THRESHOLD",this);
    //label_seuil->move(10,50);

    QLabel *label_tolerance = new QLabel("TOLERANCE",this);
    //label_tolerance->move(10,100);


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
  //  mCombo_current_source->setMaximumWidth(150);
   // mCombo_current_source->setMaximumHeight(50);
   // mCombo_current_source->move(110,5);
    mCombo_current_source->show();

    QObject::connect(mCombo_current_source, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_index_changed(int)));
    mCombo_current_source->hide();


    mColor_picker = new QColorDialog(this);
    //mColor_picker->move(50,50);
    QColor *white = new QColor();
    white->setRgb(255,255,255);
    mColor_picker->setCurrentColor(*white);
    QObject::connect(mColor_picker, SIGNAL(currentColorChanged(QColor)), this, SLOT(slot_current_color_changed(QColor)));
    mColor_picker->close();

    mBouton_color_picking = new QPushButton("Couleur d'incrustation",this);
  //  mBouton_color_picking->move(20,150);

  //  mBouton_color_picking->setMaximumWidth(200);
 //   mBouton_color_picking->setMinimumWidth(200);
    mBouton_color_picking->show();
    mBouton_color_picking->setDisabled(1);
    mBouton_color_picking->setStyleSheet("QPushButton {background-color: rgb(150,150,150);  "
                                  "border-radius: 7; "
                                  "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC); "
                                  "color: rgb(115,115,115);"
                                  "border-bottom-width: 1px;"
                                  "border-bottom-color: rgb(130,130,130);"
                                  "border-bottom-style: solid; /* just a single line */}");
    QObject::connect(mBouton_color_picking, SIGNAL(clicked()), this, SLOT(slot_color_picking()));


    mSlider_seuil = new QSlider(Qt::Horizontal, this);
    mSlider_seuil->setMaximum(100);
    mSlider_seuil->setMinimum(0);
   // mSlider_seuil->setMaximumWidth(200);
   // mSlider_seuil->setMinimumWidth(200);
    //mSlider_seuil->move(10,70);
    mSlider_seuil->setEnabled(1);
    mSlider_seuil->show();
    unif_slider(mSlider_seuil);
    QObject::connect(mSlider_seuil, SIGNAL(valueChanged(int)), this, SLOT(save_settings(int)));


    mSlider_tolerance = new QSlider(Qt::Horizontal, this);
    mSlider_tolerance->setMaximum(100);
    mSlider_tolerance->setMinimum(0);
   // mSlider_tolerance->move(10,120);
  //  mSlider_tolerance->setMaximumWidth(200);
   // mSlider_tolerance->setMinimumWidth(200);
    mSlider_tolerance->show();
     unif_slider(mSlider_tolerance);
    QObject::connect(mSlider_tolerance, SIGNAL(valueChanged(int)), this, SLOT(save_settings(int)));



    mCombo_mode = new QComboBox(this);
    mCombo_mode->addItem("Luma Key");
    mCombo_mode->addItem("Chroma Key");
 //   mCombo_mode->setMaximumWidth(200);
   // mCombo_mode->setMinimumWidth(200);
   // mCombo_mode->move(20,230);
   mCombo_mode->setStyleSheet("QComboBox {border-radius: 3; "
                                  "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 1.0 #E6E6E6, stop: 1.0 #DCDCDC); "
                                  "color: rgb(115,115,115);"
                                    "border-bottom-width: 1px;"
                                    "border-bottom-color: rgb(130,130,130);"
                                    "border-bottom-style: solid; /* just a single line */}"
                                    "QComboBox::drop-down {color: rgb(115,115,115); bottom: 0px; image: url(/home/guillaume/Documents/DreamEverywhere-2017/stylesheet_img/drop_down.png);}"
                                    /* Indicator will shine through the label text if you don't make it hidden. */
                                    "QComboBox::item:selected {border: 3px solid transparent; font-weight: bold;}"
                                    /* Indicator will shine through the label text if you don't make it hidden. */
                                    "QComboBox::item {background-color: rgb(220,220,220);}"
                                    /* Indicator will shine through the label text if you don't make it hidden. */
                                    "QComboBox::indicator{"
                                        "background-color:transparent;"
                                        "selection-background-color:transparent;"
                                        "color:transparent;"
                                        "selection-color:transparent;}");
    QObject::connect(mCombo_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_change_mode(int)));


    current=0;

    lyt_key->addWidget(label_seuil);
    lyt_key->addWidget(mSlider_seuil);
    lyt_key->addWidget(label_tolerance);
    lyt_key->addWidget(mSlider_tolerance);
    lyt_key->addWidget(mBouton_color_picking);
    lyt_key->addWidget(mCombo_mode);

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

void KeyerSettings::unif_slider(QSlider *_slider)
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

void KeyerSettings::closeEvent(QCloseEvent* event)
{
    emit dialogClosed();
    this->close();
}
