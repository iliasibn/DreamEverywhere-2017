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


struct InputData {
  MY_TYPE* buffer;
  unsigned long bufferBytes;
  unsigned long totalFrames;
  unsigned long frameCounter;
  unsigned int channels;
};

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

};


#endif // MAINWINDOW_H