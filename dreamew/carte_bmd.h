
#ifndef CARTE_BMD_H
#define CARTE_BMD_H

#include "DeckLinkAPI.h"         //! L'API DeckLink pour les cartes BlackMagic
#include <QGLWidget>             //! QGLWidget pour la création de Widgets gérés en OpenGL dans le GPU
#include <iostream>
#include <string>
#include "info_carte.h"

using namespace std;

class PlaybackDelegate;           //! Le Delegate permettant de recevoir les signaux liés à la lecture sur carte BMD
class CaptureDelegate;           //! Le Delegate permettant de recevoir les signaux liés à l'entrée

//////////////////////////////////////////////////////////////
// Classe représentant un ensemble d'interfaces BlackMagic
//////////////////////////////////////////////////////////////

class carte_bmd : public QObject
{
    Q_OBJECT

public:

    carte_bmd(QWidget *_parent,  INFO_CARTE*);
    ~carte_bmd();


    /*
     * On initialise les cartes Blackmagic. On fait le lien entre les interfaces physique et logicielles
     * @param : un pointeur vers les DATA de sortie et entrées pour OpenGL
     *
    */
    bool Init_DL(void**);

    /*
     * On liste toute les interfaces DeckLink Blackmagic disponibles
     * @return : false si tout ne s'est pas bien passé, true si tout s'est bien passé
    */
    string* list_DL_IO();

    /*
     * On liste toute les interfaces DeckLink Blackmagic disponibles
     * @return : 0 si tout ne s'est pas bien passé, 1 si tout s'est bien passé
    */
    int check_DL_IO();

    /*
     * On liste toute les interfaces DeckLink Blackmagic disponibles
     * @return : false si tout ne s'est pas bien passé, true si tout s'est bien passé
    */
    bool start_DL();

    /*
     * On liste toute les interfaces DeckLink Blackmagic disponibles
     * @return : false si tout ne s'est pas bien passé, true si tout s'est bien passé
    */
    bool stop_DL();

    /*
     * On récupère les informations de patch rentrées à l'utilisateur
    */
    void get_patch_DL(int*);

    /*
     * On écrit sur la carte de sortie le contenu du buffer OpenGL, récupéré grâce à une référence vers le pointeur des données du buffer
     * @return : false si tout ne s'est pas bien passé, true si tout s'est bien passé
    */
    bool writetoDLcard();

    /*
     * On re-patch les E/S physiques et virtuelles
     * @return : false si tout ne s'est pas bien passé, true si tout s'est bien passé
    */
    bool repatch_DL(INFO_CARTE*, void**);

    void writeNextAudioSamples();

    /*
     * Accesseurs
    */
    int         access_height();
    int         access_width();
    int         access_duration();
    int         access_nbinput();

    bool                                    mBMD_PLAYBACK;

private:


    void*						audioBuffer;
    uint32_t					audioBufferSampleLength;
    uint32_t					audioSamplesPerFrame;
    uint32_t					audioChannelCount;
    BMDAudioSampleRate			audioSampleRate;
    uint32_t					audioSampleDepth;
    uint32_t					totalAudioSecondsScheduled;
    uint32_t					framesPerSecond;
    long                        SampleFrameCount;
    BMDAudioSampleRate              _audioSampleRate = bmdAudioSampleRate48kHz;
    BMDAudioSampleType              _audioSampleType = bmdAudioSampleType32bitInteger;
    BMDAudioFormat                  _audioFormat     = bmdAudioFormatPCM;
    BMDAudioConnection              _audioConnection = bmdAudioConnectionAnalog;

    /*
     * On effectue l'initialisation pour les entrées
     * @return : false si tout ne s'est pas bien passé, true si tout s'est bien passé
    */
    bool Init_DL_input();

    /*
     * On effectue l'initialisation pour les sorties
     * @return : false si tout ne s'est pas bien passé, true si tout s'est bien passé
    */
    bool Init_DL_output(void**);

    IDeckLinkMutableVideoFrame*            mOutFrame;                       // Buffer de lecture utilisé par la fonction writetoDLcard()
    void**                                 mInFrame;                        // Buffer de capture utilisé par la fonction writetoDLcard()
    string*                                m_IO;                            // Liste des interfaces Blackmagic en chaine de caractère
    int*                                   mListe;                          // Liste des interfaces Blackmagic en entier


private slots :
     void VideoFrameArrived(IDeckLinkVideoInputFrame* _inputFrame, bool _hasNoInputSource);
     void AudioPacketStreamArrived(void* _audioBytes, long _SampleFrameCount);

signals:
    void emitVideoFrame(void**, int);

private:

    //Qt
    QWidget*								mParent;

    // DeckLink
    QVector<CaptureDelegate*>				mCaptureDelegate;//Objet qui recoit la vidéo et emit un signal
    PlaybackDelegate*                       playerDelegate;//Objet qui recoit le signal

    QVector<IDeckLinkOutput*>				vec_mDLOutput;   //Vecteur d'interfaces vers les sorties physiques

    QVector<IDeckLinkInput*>				vec_mDLInput;    //Vecteur d'interfaces vers les entrées physiques
    BMDTimeValue							mFrameDuration;
    BMDTimeScale							mFrameTimescale;
    unsigned								mFrameWidth;
    unsigned								mFrameHeight;
    INFO_CARTE*                             mLocal;         // Pointeur vers les informations de la carte E/S BMD
};


////////////////////////////////////////////
// Capture Delegate Class
////////////////////////////////////////////

class CaptureDelegate : public QObject, public IDeckLinkInputCallback
{
    Q_OBJECT
public:

    CaptureDelegate () { }

    // IUnknown needs only a dummy implementation
    virtual HRESULT	STDMETHODCALLTYPE	QueryInterface (REFIID /*iid*/, LPVOID* /*ppv*/)	{return E_NOINTERFACE;}
    virtual ULONG	STDMETHODCALLTYPE	AddRef ()											{return 1;}
    virtual ULONG	STDMETHODCALLTYPE	Release ()											{return 1;}

    virtual HRESULT STDMETHODCALLTYPE	VideoInputFrameArrived(IDeckLinkVideoInputFrame *videoFrame, IDeckLinkAudioInputPacket *audioPacket);
    virtual HRESULT	STDMETHODCALLTYPE	VideoInputFormatChanged(BMDVideoInputFormatChangedEvents notificationEvents, IDeckLinkDisplayMode *newDisplayMode, BMDDetectedVideoInputFormatFlags detectedSignalFlags);

signals:
    void captureFrameArrived(IDeckLinkVideoInputFrame *videoFrame, bool hasNoInputSource);
    void captureAudioPacketArrived(void* audioBytes,long SampleFrameCount);
};

////////////////////////////////////////////
// Playout Delegate Class
////////////////////////////////////////////

class PlaybackDelegate : public IDeckLinkAudioOutputCallback
{
    QAtomicInt					mRefCount;
    carte_bmd*                  mController;
    IDeckLinkOutput*			mDeckLinkOutput;

public:
    PlaybackDelegate (carte_bmd* owner, IDeckLinkOutput* deckLinkOutput);

    // IUnknown
    virtual HRESULT		QueryInterface (REFIID, LPVOID *);
    virtual ULONG		AddRef ();
    virtual ULONG		Release ();

    virtual HRESULT		ScheduledPlaybackHasStopped ();
    virtual HRESULT		RenderAudioSamples (bool preroll);
};

void	FillSine (void* audioBuffer, uint32_t samplesToWrite, uint32_t channels, uint32_t sampleDepth);

#endif // CARTE_BMD_H
