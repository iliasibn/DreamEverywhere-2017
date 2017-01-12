#ifndef SOUND_H
#define SOUND_H

#include <QGLWidget>
#include <iostream>
#include <string>
#include "RtAudio.h"
#include "carte_bmd.h"

#define BASE_RATE 0.005
#define TIME 1.0

typedef signed short MY_TYPE;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0



class Sound : public QObject
{
    Q_OBJECT

public:
    Sound(QWidget *parent = 0);
    ~Sound();


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
#endif // SOUND_H
