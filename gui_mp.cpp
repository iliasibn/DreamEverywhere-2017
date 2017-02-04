/*
 * Interface graphique du Player
 *
 */
#include "gui_mp.h"
//#include "ui_gui_mp.h"
#include "mltcontroller.h"

#include <QtWidgets>
#include<iostream>

/*----------------- CONSTRUCTEUR INTERFACE GRAPHIQUE PLAYER -------------
 * m_id est le numéro de la source dans le panel
 * video est un QDialog donc c'est la page qui s'ouvre au click depuis l'interface
 * Est-ce que video player à besoin de rester parent ?
 */
gui_mp::gui_mp (QWidget *parent): m_id(0),video(0) {

    video = new QDialog(); //Fenetre de dialogue

    mlt = new MltController (video); // Création d'un player avec la fenetre comme parent

    bouton_play = new QPushButton("Pause"); //Bouton de contrôle de lecture

    currentTime = new QLabel; // affichage du temps actuel de la vidéo

    slider = new QSlider(Qt::Horizontal); // Barre de défilement de la vidéo

    bouton_open = new QPushButton("Open"); // Choix de la source "Open"


    QVBoxLayout *layout = new QVBoxLayout(this); //organisation verticale des controles

    QLineEdit *timecode = new QLineEdit("00:00:00:00"); // barre d'édition pour entrer un timecode


    this->setWindowTitle("Video Player"); // Nom de la fenetre
    this->setFixedSize(200,200);

    //video->show(); //Affichage de la fenetre de vidéo

    slider->setRange(0,0); // initialisation de la barre de slide avant qu'elle ne soit éditée


    //layout->addWidget(video);
    layout->addWidget(bouton_open);
    layout->addWidget(slider);
    layout->addWidget(currentTime);
    layout->addWidget(bouton_play);
    layout->addWidget(timecode);

    this->setLayout(layout);

    connect (mlt, SIGNAL(frameReceived (void*, unsigned)), this, SLOT(onShowFrame (void*, unsigned)));
    connect (bouton_play, SIGNAL(clicked()), this, SLOT(play()));
    connect(timecode,SIGNAL(textChanged(QString)), this, SLOT(onLineReturn(QString)));
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(onSliderMoved(int)));
    connect(bouton_open, SIGNAL(clicked()), this, SLOT(slotOpen()));

}

gui_mp::~gui_mp ()
{
    delete mlt;
#ifdef Q_WS_MAC
    delete gl;
#endif
}

void gui_mp::initializeMlt (int i) {

    m_id = i;
    mlt->init ();
    pause ();
}

void gui_mp::slotOpen()
{
    QString filename = QFileDialog::getOpenFileName (this);
    if (!filename.isNull()) {
        if (!mlt->open (filename.toUtf8().constData())) {
        #ifdef Q_WS_MAC
            gl->setImageAspectRatio (mlt->profile()->dar());
        #endif
        mlt->play();
        }
    }
    mlt->onWindowResize ();
    slider->setMaximum(mlt->getLength());
}

void gui_mp::play ()
{
    if(mlt->isPlaying()){
        mlt->play();
        bouton_play->setText("Pause");
    }
    else {
        mlt->pause();
        bouton_play->setText("Play");
    };

    forceResize ();
}

void gui_mp::pause ()
{
   mlt->pause ();

    forceResize ();
}

void gui_mp::resizeEvent (QResizeEvent*)
{
    mlt->onWindowResize();
}

void gui_mp::forceResize()
{
    int width = this->width();
    int height = this->height();
    this->resize (width - 1, height - 1);
   this->resize (width, height);
}

void gui_mp::onShowFrame (void* frame, unsigned position)
{
#ifdef Q_WS_MAC
    emit showImageSignal (mlt->getImage (frame));
#endif

    emit showImageSignal (mlt->getImage (frame), m_id);

    currentTime->setText(QString().sprintf("%.2d:%.2d:%.2d:%.2d / %.2d:%.2d:%.2d:%.2d",
                                           (position / 3600 / 25) % 60,
                                           (position / 60 / 25) % 60,
                                           (position / 25) % 60,
                                            position % 25,
                                           (mlt->getLength() / 3600 / 25) % 60,
                                           (mlt->getLength() / 60 / 25) % 60,
                                           (mlt->getLength() / 25) % 60,
                                            mlt->getLength() % 25));

    slider->setValue(position);

}

void gui_mp::onLineReturn (QString timecode){

    mlt->setPosition(timecode.toUtf8().constData());
}

void gui_mp::onSliderMoved(int timecode){

    char* value = new char;

    sprintf(value, "%d",timecode);

    mlt->setPosition(value);
    currentTime->setText(QString().sprintf("%.2d:%.2d:%.2d:%.2d / %.2d:%.2d:%.2d:%.2d",
                                           (timecode / 3600 / 25) % 60,
                                           (timecode / 60 / 25) % 60,
                                           (timecode / 25) % 60,
                                            timecode % 25,
                                           (mlt->getLength() / 3600 / 25) % 60,
                                           (mlt->getLength() / 60 / 25) % 60,
                                           (mlt->getLength() / 25) % 60,
                                            mlt->getLength() % 25));
}
