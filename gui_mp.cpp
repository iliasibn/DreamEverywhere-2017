/*
 * Copyright (c) 2011 Dan Dennedy <dan@dennedy.org>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "gui_mp.h"
#include "ui_gui_mp.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QWidget>
#include "mltcontroller.h"
#include<iostream>
gui_mp::gui_mp (QWidget *parent): m_id(0),video(0)
    //: ui (new Ui::gui_mp)
{
    QVBoxLayout *lay = new QVBoxLayout(this);

    // Create the UI.
  /*  ui->setupUi (this);

    // This is required for SDL embeddding.
    ui->centralWidget->setAttribute (Qt::WA_NativeWindow);

    // These use the icon theme on Linux, with fallbacks to the icons specified in QtDesigner for other platforms.
    ui->actionOpen->setIcon (QIcon::fromTheme ("document-open", ui->actionOpen->icon ()));
    ui->actionPlay->setIcon (QIcon::fromTheme ("media-playback-start", ui->actionPlay->icon ()));
    ui->actionPause->setIcon (QIcon::fromTheme ("media-playback-pause", ui->actionPause->icon ()));

    // Connect UI signals.
    connect (ui->actionOpen, SIGNAL(triggered()), this, SLOT(openVideo()));
    connect (ui->actionPlay, SIGNAL(triggered()), this, SLOT(play()));
    connect (ui->actionPause, SIGNAL(triggered()), this, SLOT(pause()));

*/

    //AJOUT DREAM POUR L'ENTREE DU TIMECODE
    //connect (ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(onLineReturn()));

    // Create MLT controller and connect its signals.
    //mlt = new MltController (ui->centralWidget);
    video = new QDialog();

    mlt = new MltController (video);
    lay->addWidget(video);
    connect (mlt, SIGNAL(frameReceived (void*, unsigned)), this, SLOT(onShowFrame (void*, unsigned)));
    video->show();
    //AJOUT DREAMEVERYWHERE
    //glout = new GLWidget (this);

    fenetre_mp = new QWidget();
    lay->addWidget(fenetre_mp);
    this->setWindowTitle("The super PLayer");
    QVBoxLayout *layoutgl = new QVBoxLayout;
    QGroupBox *controlBox = new QGroupBox;
    bouton_play = new QPushButton("Pause");
    //QPushButton *pause = new QPushButton("pause");
    QLineEdit *timecode = new QLineEdit ;
    currentTime = new QLabel;
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0,0);
    bouton_source = new QComboBox;
    bouton_source->addItem("Ouvrir un fichier local");
    bouton_source->addItem("Ouvrir un fichier sur le réseau");

    //--------------------- Gestion de sources---------------------------------------
    window_reseau = new QWidget;
    QGridLayout *grid = new QGridLayout(window_reseau);
    grid->setSpacing(2);
    QLabel *reseau = new QLabel;
    reseau->setText("Veuillez rentrer l'URL ou l'adresse IP");
    adresse = new QLineEdit;
    QPushButton *valider_adresse = new QPushButton("Valider");
    QPushButton *quitter_windowreseau = new QPushButton("Quitter");
   // QPushButton *Next = new QPushButton("Next");
   // QPushButton *Previous = new QPushButton("Previous");
    grid->addWidget(reseau,0,0,1,2);
    grid->addWidget(adresse,1,0,1,2);
    grid->addWidget(valider_adresse, 2,0);
    grid->addWidget(quitter_windowreseau,2,1);


    //--------------------Creation d'une playlist-----------------------------------

    QVBoxLayout *vbox = new QVBoxLayout;
         //vbox->addWidget();
         vbox->addWidget(bouton_source);
         vbox->addWidget(slider);
         vbox->addWidget(timecode);
         vbox->addWidget(currentTime);
         vbox->addWidget(bouton_play);
         //vbox->addWidget(pause);
         //vbox->addWidget(Next);
       // vbox->addWidget(Previous);
         controlBox->setLayout(vbox);


    //layoutgl->addWidget (glout);

    layoutgl->addWidget(controlBox);

   fenetre_mp->setLayout(layoutgl);
   //fenetre_mp->show();

    //connect(this, SIGNAL(showImageSignal(QImage)),glout,SLOT(showImage(QImage)));
    //

    connect (bouton_play, SIGNAL(clicked()), this, SLOT(play()));
    //connect (pause, SIGNAL(clicked()), this, SLOT(pause()));
    connect(timecode,SIGNAL(textChanged(QString)), this, SLOT(onLineReturn(QString)));
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(onSliderMoved(int)));
    connect(bouton_source, SIGNAL(activated(int)), this, SLOT(slotcombobox(int)) );
    connect(quitter_windowreseau, SIGNAL(clicked(bool)), this, SLOT(quitter_windowreseau()));
    connect(valider_adresse, SIGNAL(clicked(bool)), this, SLOT(valider_adresse()));

    //connect (Next, SIGNAL(clicked()), this, SLOT(next()));
  //  connect (Previous, SIGNAL(clicked()), this, SLOT(previous()));

    //
#ifdef Q_WS_MAC
    gl = new GLWidget (this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget (gl);
    layout->setMargin (0);
    ui->centralWidget->setLayout (layout);
    connect (this, SIGNAL (showImageSignal (QImage)), gl, SLOT (showImage(QImage)));
#endif
}

gui_mp::~gui_mp ()
{
    delete mlt;
#ifdef Q_WS_MAC
    delete gl;
#endif
    //delete glout;
    //delete ui;
}

void gui_mp::initializeMlt (int i)
{
    //ui->statusBar->showMessage (tr("Loading plugins..."));
m_id = i;
    mlt->init ();
    // Load a color producer to clear the video region with black.
   // mlt->createPlaylist();
    //mlt->open ("color:");
    pause ();
    //ui->statusBar->showMessage (tr("Ready"));
}


void gui_mp::slotcombobox(int index)
{
    QString t = bouton_source->itemText(index) ;

    if (bouton_source->currentText()=="Ouvrir un fichier local")
    {
        QString filename = QFileDialog::getOpenFileName (this);
        if (!filename.isNull())
        {
            if (!mlt->open (filename.toUtf8().constData())) {
    #ifdef Q_WS_MAC
                gl->setImageAspectRatio (mlt->profile()->dar());
    #endif

                mlt->play();
            }
        }
        // If file invalid, then on some platforms the dialog messes up SDL.
        mlt->onWindowResize ();
        slider->setMaximum(mlt->getLength());

    }
    if (bouton_source->currentText()=="Ouvrir un fichier sur le réseau")
    {
        window_reseau->show();
    }
}

void gui_mp :: quitter_windowreseau()
{
    window_reseau->close();
}

void gui_mp::valider_adresse()
{
    QString url = adresse->text();
    if (!url.isNull())
    {
        if (!mlt->open (url.toUtf8().constData()))
        {
            play();
            adresse->clear();
            window_reseau->close();
          // play();

        }
    }
}

void gui_mp::play ()
{
    //mlt->play ();
  /*  if(mlt->isPlaying())
        mlt->play();
    else
        pause();*/
    switch(mlt->isPlaying()){
    case true: mlt->play();
        bouton_play->setText("Pause");
        break;
    case false: mlt->pause();
        bouton_play->setText("Play");
        break;
    }

    forceResize ();
    //ui->statusBar->showMessage (tr("Playing"));
}

void gui_mp::pause ()
{
   mlt->pause ();

    forceResize ();
    //ui->statusBar->showMessage (tr("Paused"));
}

void gui_mp::resizeEvent (QResizeEvent*)
{
    mlt->onWindowResize();
}

void gui_mp::forceResize()
{
    // XXX: this is a hack to force video container to resize
    /*int width = ui->centralWidget->width();
    int height = ui->centralWidget->height();
    ui->centralWidget->resize (width - 1, height - 1);
    ui->centralWidget->resize (width, height);*/

    int width = this->width();
    int height = this->height();
    this->resize (width - 1, height - 1);
   this->resize (width, height);
}



void gui_mp::onShowFrame (void* frame, unsigned position)
{
#ifdef Q_WS_MAC
    emit showImageSignal (mlt->getImage (frame));
    //emit showImageSignal (mlt->getAudio (frame));
#endif
    //AJOUT DREAMEVERYWHERE
   //void* pFrame;
   // fprintf(stderr,"%d bytes\n", mlt->getImage(frame).byteCount());
   //pFrame = mlt->getImage(frame);
 //emit showImageSignal (mlt->getImage(frame), 4);
    emit showImageSignal (mlt->getImage (frame), m_id);
  //emit showImageSignal (&pFrame, 4);

    //mlt->getAudio (frame);
    //
    //ui->statusBar->showMessage (QString().sprintf ("%.3f", position / mlt->profile()->fps()));
    currentTime->setText(QString().sprintf("%.2d:%.2d:%.2d:%.2d / %.2d:%.2d:%.2d:%.2d",
                                           (position / 3600 / 25) % 60,
                                           (position / 60 / 25) % 60,
                                           (position / 25) % 60,
                                            position % 25,
                                           (mlt->getLength() / 3600 / 25) % 60,
                                           (mlt->getLength() / 60 / 25) % 60,
                                           (mlt->getLength() / 25) % 60,
                                            mlt->getLength() % 25));
    //currentTime->setText( toTimeCode(position)+toTimeCode(mlt->getLength()));
    //mlt->m_producer->get_length()
    slider->setValue(position);

}

void gui_mp::onLineReturn (QString timecode){

//QString timecode = ui->lineEdit->text();

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

/*void gui_mp::next()
{
    int index = mlt->nextclip();
    std::cout << index << std::endl;
}*/

/*void gui_mp::previous()
{

}*/
