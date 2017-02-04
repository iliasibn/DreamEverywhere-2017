#include "gui_start.h"
#include <QCloseEvent>


gui_start::gui_start(QWidget* parent):m_frameDuration(40), m_width(1920), m_height(1080)
{
    this->setWindowTitle("Welcome - DreamEverywhere");
    this->setStyleSheet("background-color: rgb(180,180,180);}");

QGridLayout* main_grid = new QGridLayout(this);

QPixmap *_logo = new QPixmap("/home/guillaume/Documents/DreamEverywhere-2017/stylesheet_img/logo.png");
QLabel *_label = new QLabel(this);
_label->setPixmap(*_logo);
_label->resize(20,20);
main_grid->addWidget(_label,0,0,1,3, Qt::AlignCenter);

QLabel *_format = new QLabel("OUTPUT");
main_grid->addWidget(_format,1,0,1,1);
m_comboFmt = new QComboBox(this);
m_comboFmt->addItem("1920x1080 25p");
main_grid->addWidget(m_comboFmt,1,1,1,2);

QLabel *_bmd = new QLabel("BMD DECKLINK");
main_grid->addWidget(_bmd,2,0,1,1);
m_sliderBMD = new QSlider(Qt::Horizontal, this);
m_sliderBMD->setMaximum(1);
m_sliderBMD->setMinimum(0);
m_sliderBMD->setSliderPosition(0);
m_sliderBMD->setStyleSheet(
          "QSlider::groove {"
          "border: 0px solid #999999;"
          "background: rgb(115,115,115);"
          "border-radius: 3px;"
          "border-top-width: 1px;"
          "border-top-color: rgb(80,80,80);"
          "height:15px; width:30px;"
          "border-top-style: solid;"
          "image: url(/home/guillaume/Documents/DreamEverywhere-2017/stylesheet_img/io.png); /* just a single line */}"
          "QSlider::handle::horizontal {"
          "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC);"
          "border-bottom-width: 1px;"
          "border-bottom-color: rgb(130,130,130);"
          "border-bottom-style: solid; /* just a single line */"
          "width:15px;"
          "border-radius: 3px; margin: 0 0; }");
main_grid->addWidget(m_sliderBMD,2,1,1,1);

QLabel *_mp = new QLabel("MEDIA PLAYER");
main_grid->addWidget(_mp,3,0,1,1);
m_sliderMP = new QSlider(Qt::Horizontal, this);
m_sliderMP->setMaximum(1);
m_sliderMP->setMinimum(0);
m_sliderMP->setSliderPosition(0);
m_sliderMP->setStyleSheet(
          "QSlider::groove {"
          "border: 0px solid #999999;"
          "background: rgb(115,115,115);"
          "border-radius: 3px;"
          "border-top-width: 1px;"
          "border-top-color: rgb(80,80,80);"
          "height:15px; width:30px;"
          "border-top-style: solid;"
          "image: url(/home/guillaume/Documents/DreamEverywhere-2017/stylesheet_img/io.png); /* just a single line */}"
          "QSlider::handle::horizontal {"
          "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC);"
          "border-bottom-width: 1px;"
          "border-bottom-color: rgb(130,130,130);"
          "border-bottom-style: solid; /* just a single line */"
          "width:15px;"
          "border-radius: 3px; margin: 0 0; }");
main_grid->addWidget(m_sliderMP,3,1,1,1);

QLabel *_sub = new QLabel("Version 1.3 - 2017");
_sub->setStyleSheet("font-size : 12px");
main_grid->addWidget(_sub,4,0,1,3,Qt::AlignCenter);

m_startButton = new QPushButton("START",this);
m_startButton->setFixedSize(80,30);
QObject::connect(m_startButton, SIGNAL(pressed()), this, SLOT(slot_startPressed()));
m_startButton->setStyleSheet("QPushButton {background-color: rgb(150,150,150);  "
                              "border-radius: 7; "
                              "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC); "
                              "color: rgb(115,115,115);"
                              "border-bottom-width: 1px;"
                              "border-bottom-color: rgb(130,130,130);"
                              "border-bottom-style: solid; /* just a single line */}");
main_grid->addWidget(m_startButton,2,2,2,1, Qt::AlignCenter);


}

bool gui_start::isBMD(){
return (bool)m_sliderBMD->sliderPosition();
}

bool gui_start::isMP(){
return (bool)m_sliderMP->sliderPosition();
}

void gui_start::getAssets(int _w, int _h, int _fd)
{
    _w = m_width;
    _h = m_height;
    _fd = m_frameDuration;
}

void gui_start::slot_startPressed()
{
    if (m_sliderBMD->sliderPosition() == 0 && m_sliderMP->sliderPosition() == 0)
        QMessageBox::critical(NULL,"Erreur - DreamEverywhere","Sélectionnez au moins un module d'entrée/sortie");
    else
        this->hide();
}

void gui_start::slot_comboChanged(int _a)
{

    switch ( _a ) {
    case 0:
        m_frameDuration = 40;
        m_width = 1920;
        m_height = 1080;
    break;
    }
}

void gui_start::closeEvent(QCloseEvent *event)
{
    //this->slot_startPressed();
    //event->ignore();
    exit(0);
}

gui_start::~gui_start(){

}
