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

#include <QMainWindow>
#include <QWidget>
//#include <QtMultimedia>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include "mltcontroller.h"
#include <QDialog>

#ifdef Q_WS_MAC
#   include "glwidget.h"
#endif

namespace Ui {
    class gui_mp;
}

class gui_mp : public QDialog
{
    Q_OBJECT

public:
    explicit gui_mp(QWidget* parent = NULL);
    ~gui_mp();
    void initializeMlt (int);
    QString toTimeCode(unsigned position);
    QWidget *fenetre_mp;

private:
    void resizeEvent (QResizeEvent* event);
    void forceResize ();

  //  Ui::gui_mp* ui;
    MltController* mlt;
    //GLWidget* glout;

    QLabel *currentTime;
    QSlider *slider ;
    QPushButton  *bouton_play;
    QPushButton *bouton_open;
    //QWidget *window_reseau;
    //QLineEdit *adresse;
    int m_id;
    QDialog *video;


    #ifdef Q_WS_MAC
    GLWidget* gl;
    static void on_frame_show(mlt_consumer, gui_mp*, mlt_frame);
#endif

signals:
    void showImageSignal(void*, int);

public slots:

    void play ();
    void pause ();
   // void next();
  //  void previous();
    void onShowFrame (void* frame, unsigned position);
    void onLineReturn(QString timecode);
    void onSliderMoved(int timecode);
    void slotOpen();
    //void quitter_windowreseau();
    //void valider_adresse();

};

#endif // MAINWINDOW_H
