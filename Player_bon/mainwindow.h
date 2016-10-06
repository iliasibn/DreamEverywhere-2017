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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include <QtWidgets>
#include <QMainWindow>
#include "mltcontroller.h"
#include <QPushButton>
#include <QInputDialog>




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton     *bouton_openvideo;
    QPushButton     *bouton_openurl;
    QPushButton     *bouton_play;
    QPushButton     *bouton_pause;
    ~MainWindow();
    void initializeMlt ();

private:
    void resizeEvent (QResizeEvent* event);
    void forceResize ();


       MltController* mlt;

signals:
    void showImageSignal(QImage);

public slots:
    void openVideo ();
    void openUrl();
    void play ();
    void pause ();



};

#endif // MAINWINDOW_H
