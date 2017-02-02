#include "gui_start.h"
#include <QCloseEvent>

gui_start::gui_start(QWidget* parent):m_frameDuration(40), m_width(1920), m_height(1080)
{
    this->setWindowTitle("Bienvenue - DreamEverywhere");
    this->setStyleSheet("background-color: rgb(150,150,150);}");

QGridLayout* main_grid = new QGridLayout(this);

QLabel *_format = new QLabel("Format de sortie");
main_grid->addWidget(_format,0,0,1,1);
m_comboFmt = new QComboBox(this);
m_comboFmt->addItem("1920x1080 25p");
main_grid->addWidget(m_comboFmt,0,1,1,2);

QLabel *_bmd = new QLabel("BlackMagic Decklink");
main_grid->addWidget(_bmd,1,0,1,1);
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
          "border-top-style: solid; /* just a single line */}"
          "QSlider::handle::horizontal {"
          "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC);"
          "border-bottom-width: 1px;"
          "border-bottom-color: rgb(130,130,130);"
          "border-bottom-style: solid; /* just a single line */"
          "width:15px;"
          "border-radius: 3px; margin: 0 0; }");
main_grid->addWidget(m_sliderBMD,1,1,1,1);

QLabel *_mp = new QLabel("Media Player");
main_grid->addWidget(_mp,2,0,1,1);
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
          "border-top-style: solid; /* just a single line */}"
          "QSlider::handle::horizontal {"
          "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #E6E6E6, stop: 1.0 #DCDCDC);"
          "border-bottom-width: 1px;"
          "border-bottom-color: rgb(130,130,130);"
          "border-bottom-style: solid; /* just a single line */"
          "width:15px;"
          "border-radius: 3px; margin: 0 0; }");
main_grid->addWidget(m_sliderMP,2,1,1,1);

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
main_grid->addWidget(m_startButton,1,2,2,1, Qt::AlignCenter);
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
