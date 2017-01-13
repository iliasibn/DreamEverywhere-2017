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
    Sound();
    ~Sound();


    static void ErrorCallback(RtAudioError::Type type, const std::string &errorText);

    static int saw(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
               double streamTime, RtAudioStreamStatus status, void *userData);
    static int duplex(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
               double streamTime, RtAudioStreamStatus status, void *userData);

    int searchforinput();
    void startaudiostream(void *AudioBuffer,unsigned int _sampleRate);

    bool flag;
    int num;
    unsigned int sampleRate;

    RtAudio *audio;
    RtAudio::StreamParameters output;
    RtAudio::StreamParameters input;

private slots :


private:


};
#endif // SOUND_H
