#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>             //! QGLWidget pour la création de Widgets gérés en OpenGL dans le GPU
#include <iostream>
#include "DeckLinkAPI.h"
#include "RtAudio.h"

#define BASE_RATE 0.005
#define TIME 1.0

typedef signed short MY_TYPE;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0

typedef struct {
int mNbr_io = 0, mNbr_i = 0, mNbr_o = 0;
std::string mNom;} INFO_CARTE;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


    static void ErrorCallback(RtAudioError::Type type, const std::string &errorText);

    static int saw(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
               double streamTime, RtAudioStreamStatus status, void *userData);
    static int duplex(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
               double streamTime, RtAudioStreamStatus status, void *userData);

    int searchforinput();
    void startaudiostream(int signal);

    bool flag;
    int num;

private slots :


private:
RtAudio *audio;
RtAudio::StreamParameters output;
RtAudio::StreamParameters input;

// DeckLink
QVector<IDeckLinkInput*>				vec_mDLInput;    //Vecteur d'interfaces vers les entrées physiques
QVector<IDeckLinkOutput*>				vec_mDLOutput;   //Vecteur d'interfaces vers les sorties physiques
BMDTimeValue							mFrameDuration;
BMDTimeScale							mFrameTimescale;
unsigned								mFrameWidth;
unsigned								mFrameHeight;
INFO_CARTE*                             mLocal;         // Pointeur vers les informations de la carte E/S BMD
};


#endif // MAINWINDOW_H
