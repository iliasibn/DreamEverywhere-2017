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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QtWidgets>
#include "mltcontroller.h"
#include<iostream>
MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::MainWindow)
{
    // Create the UI.
    ui->setupUi (this);

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



    //AJOUT DREAM POUR L'ENTREE DU TIMECODE
    //connect (ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(onLineReturn()));

    // Create MLT controller and connect its signals.
    mlt = new MltController (ui->centralWidget);
    connect (mlt, SIGNAL(frameReceived (void*, unsigned)), this, SLOT(onShowFrame (void*, unsigned)));

    //AJOUT DREAMEVERYWHERE
    glout = new GLWidget (this);

    QWidget *window = new QWidget;
    QVBoxLayout *layoutgl = new QVBoxLayout;
    QGroupBox *controlBox = new QGroupBox;
    QPushButton *play = new QPushButton("play");
    QPushButton *pause = new QPushButton("pause");
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
    grid->addWidget(reseau,0,0,1,2);
    grid->addWidget(adresse,1,0,1,2);
    grid->addWidget(valider_adresse, 2,0);
    grid->addWidget(quitter_windowreseau,2,1);


    //--------------------Creation d'une playlist-----------------------------------

    QVBoxLayout *vbox = new QVBoxLayout;
         vbox->addWidget(slider);
         vbox->addWidget(play);
         vbox->addWidget(pause);
         vbox->addWidget(bouton_source);
         vbox->addWidget(timecode);
         vbox->addWidget(currentTime);
         controlBox->setLayout(vbox);


    layoutgl->addWidget (glout);

    layoutgl->addWidget(controlBox);

    window->setLayout(layoutgl);
    window->show();

    connect(this, SIGNAL(showImageSignal(QImage)),glout,SLOT(showImage(QImage)));

    connect (play, SIGNAL(clicked()), this, SLOT(play()));
    connect (pause, SIGNAL(clicked()), this, SLOT(pause()));
    connect(timecode,SIGNAL(textChanged(QString)), this, SLOT(onLineReturn(QString)));
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(onSliderMoved(int)));
    connect(bouton_source, SIGNAL(activated(int)), this, SLOT(slotcombobox(int)) );
    connect(quitter_windowreseau, SIGNAL(clicked(bool)), this, SLOT(quitter_windowreseau()));
    connect(valider_adresse, SIGNAL(clicked(bool)), this, SLOT(valider_adresse()));

    //currentTime->setText(QString().sprintf ("%.3f", mlt->profile()->fps()));

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

MainWindow::~MainWindow ()
{
    delete mlt;
#ifdef Q_WS_MAC
    delete gl;
#endif
    delete glout;
    delete ui;
}

void MainWindow::initializeMlt ()
{
    ui->statusBar->showMessage (tr("Loading plugins..."));

    mlt->init ();
    // Load a color producer to clear the video region with black.
    mlt->open ("color:");
    pause ();

    ui->statusBar->showMessage (tr("Ready"));
}


void MainWindow::slotcombobox(int index)
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

                play();
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

void MainWindow :: quitter_windowreseau()
{
    window_reseau->close();
}

void MainWindow::valider_adresse()
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

void MainWindow::play ()
{
    mlt->play ();
    //mlt->playlistplay();
    forceResize ();
    ui->statusBar->showMessage (tr("Playing"));
}

void MainWindow::pause ()
{
   mlt->pause ();

    forceResize ();
    ui->statusBar->showMessage (tr("Paused"));
}

void MainWindow::resizeEvent (QResizeEvent*)
{
    mlt->onWindowResize();
}

void MainWindow::forceResize()
{
    // XXX: this is a hack to force video container to resize
    int width = ui->centralWidget->width();
    int height = ui->centralWidget->height();
    ui->centralWidget->resize (width - 1, height - 1);
    ui->centralWidget->resize (width, height);
}

void MainWindow::onShowFrame (void* frame, unsigned position)
{
#ifdef Q_WS_MAC
    emit showImageSignal (mlt->getImage (frame));
#endif
    //AJOUT DREAMEVERYWHERE
    emit showImageSignal (mlt->getImage (frame));

    //
    ui->statusBar->showMessage (QString().sprintf ("%.3f", position / mlt->profile()->fps()));
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

void MainWindow::onLineReturn (QString timecode){

//QString timecode = ui->lineEdit->text();

    mlt->setPosition(timecode.toUtf8().constData());


}

void MainWindow::onSliderMoved(int timecode){

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
