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
#include "visu.h"
//#include "ui_mainwindow.h"

#include <iostream>
#include <QtWidgets>

#include <QFileDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QInputDialog>

#include <stdio.h>

using namespace std;

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent)

{
    this->setWindowTitle("PanelPlayer");
    this->setFixedSize(200,100);
    this->move(1100,200);



    bouton_openvideo= new QPushButton(this);
    bouton_openvideo->setText("Open source");
    QObject::connect(bouton_openvideo, SIGNAL(clicked()), this, SLOT(openVideo()));

    bouton_openurl= new QPushButton(this);
    bouton_openurl->setText("Open Url");
    bouton_openurl->move(100,0);
    QObject::connect(bouton_openurl, SIGNAL(clicked()), this, SLOT(openUrl()));

    bouton_play =new QPushButton(this);
    bouton_play->setText("Play");
    bouton_play->move(0,50);
    QObject::connect(bouton_play, SIGNAL(clicked()), this, SLOT(play()));

    bouton_pause =new QPushButton(this);
    bouton_pause->setText("Pause");
    bouton_pause->move(100,50);
    QObject::connect(bouton_openvideo, SIGNAL(clicked()), this, SLOT(pause()));

    // Create MLT controller and connect its signals.
    mlt = new MltController (this);


}

MainWindow::~MainWindow ()
{
    delete mlt;
}

void MainWindow::initializeMlt ()
{
    mlt->init ();
    // Load a color producer to clear the video region with black.
    mlt->open ("color:");
    pause ();


}

void MainWindow::openVideo ()
{
    QString filename = QFileDialog::getOpenFileName (this);
    if (!filename.isNull())
    {
        if (!mlt->open (filename.toUtf8().constData())) {

            play();
        }
    }

   //mlt->onWindowResize ();
}

void MainWindow::openUrl ()
{

   QString url = QInputDialog::getText(this, tr("Url Video"),tr("Saississez le chemin de votre video"));
    if (!url.isNull())
    {
        if (!mlt->open (url.toUtf8().constData()))
        {

            play();
        }
    }


   //mlt->onWindowResize ();

}

void MainWindow::play ()
{
    mlt->play ();
    //forceResize ();

}

void MainWindow::pause ()
{
    mlt->pause ();
    //forceResize ();

}

void MainWindow::resizeEvent (QResizeEvent*)
{
    mlt->onWindowResize();
}

void MainWindow::forceResize()
{
    // XXX: this is a hack to force video container to resize
    /*int width = ui->centralWidget->width();
    int height = ui->centralWidget->height();
    ui->centralWidget->resize (width - 1, height - 1);
    ui->centralWidget->resize (width, height);*/

}

