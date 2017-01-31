
#ifndef CARTE_BMD_H
#define CARTE_BMD_H

#include "DeckLinkAPI.h"         //! L'API DeckLink pour les cartes BlackMagic
#include <QGLWidget>             //! QGLWidget pour la création de Widgets gérés en OpenGL dans le GPU
#include <iostream>
#include <string>
#include <pthread.h>
#include "info_carte.h"
#include <unistd.h>
#include <fcntl.h>
#include <time.h>



<<<<<<< HEAD
extern "C" {
#include <libavresample/avresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
}

const unsigned long kAudioWaterlevel = 48000 / 4;      /* small */

typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    uint64_t nb_packets;
    int size;
    int abort_request;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} PacketQueue;


PacketQueue audioqueue;
PacketQueue videoqueue;
PacketQueue dataqueue;

=======
#include "libavformat/avformat.h"
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>
#include "libswscale/swscale.h"






typedef struct AVPacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    unsigned long long size;
    int abort_request;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} AVPacketQueue;

static AVPacketQueue queue;
static AVPacket flush_pkt;
>>>>>>> a902e335b697d8d13b0d0e230af17602f5e2277c
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
<<<<<<< HEAD
    void packet_queue_init(PacketQueue *q);
    int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block);;
    int packet_queue_put(PacketQueue *q, AVPacket *pkt);
    void packet_queue_flush(PacketQueue *q);
    void packet_queue_end(PacketQueue *q);
    void *fill_queues(void *unused);

    /*
     * Accesseurs
     */
=======

    /*
     * Accesseurs
    */
>>>>>>> a902e335b697d8d13b0d0e230af17602f5e2277c
    int         access_height();
    int         access_width();
    int         access_duration();
    int         access_nbinput();

    bool                                    mBMD_PLAYBACK;

private:

    AVStream *audio_st, *video_st, *data_st;
    void*						audioBuffer;
    uint32_t					audioBufferSampleLength;
    uint32_t					audioSamplesPerFrame;
    uint32_t					audioChannelCount;
    BMDAudioSampleRate			audioSampleRate;
    uint32_t					audioSampleDepth;
    uint32_t					totalAudioSecondsScheduled;
    uint32_t					framesPerSecond;
    uint32_t                    audioSampleFrameCount;
    long                        SampleFrameCount;
    BMDAudioSampleRate          _audioSampleRate = bmdAudioSampleRate48kHz;
    BMDAudioSampleType          _audioSampleType = bmdAudioSampleType16bitInteger;
    BMDAudioFormat              _audioFormat     = bmdAudioFormatPCM;
    BMDAudioConnection          _audioConnection = bmdAudioConnectionHeadphones;
    uint32_t                    sampleFramesWritten;
<<<<<<< HEAD
    int64_t first_audio_pts = AV_NOPTS_VALUE;
    int64_t first_video_pts = AV_NOPTS_VALUE;
    int64_t first_pts       = AV_NOPTS_VALUE;
    int fill_me;
=======

>>>>>>> a902e335b697d8d13b0d0e230af17602f5e2277c
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
<<<<<<< HEAD
    pthread_mutex_t sleepMutex;
    pthread_cond_t sleepCond;
=======

>>>>>>> a902e335b697d8d13b0d0e230af17602f5e2277c

private slots :
     void VideoFrameArrived(IDeckLinkVideoInputFrame* _inputFrame, bool _hasNoInputSource);
     void AudioPacketStreamArrived(IDeckLinkAudioInputPacket* _audioPacket);

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
    void captureAudioPacketArrived(IDeckLinkAudioInputPacket*audioPacket);
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
