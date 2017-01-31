//#include <opencv/highgui.h>
#include "carte_bmd.h"
#include <QMessageBox>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <LoopThroughWithOpenGLCompositing.h>

using namespace std;

carte_bmd::carte_bmd(QWidget *_parent, INFO_CARTE * _ext):
  mParent(_parent),
  playerDelegate(),
  mListe(0),
  mLocal(_ext),
  m_IO(0),
  mBMD_PLAYBACK(true),
  mOutFrame(0)
 {
    // On enregistre des types de données dans la base de donnée Qt afin de pouvoir établir des signaux et slots
    qRegisterMetaType<IDeckLinkVideoInputFrame*>("IDeckLinkVideoInputFrame*");
    qRegisterMetaType<IDeckLinkVideoFrame*>("IDeckLinkVideoFrame*");
    qRegisterMetaType<BMDOutputFrameCompletionResult>("BMDOutputFrameCompletionResult");
    audioBuffer = NULL;
 }

carte_bmd::~carte_bmd()
{
    stop_DL();
    for (int i = 0; i<mLocal->mNbr_io; i++)
    {
         if (vec_mDLInput.at(i) != NULL)
            { vec_mDLInput.at(i)->SetCallback(NULL);
             vec_mDLInput.at(i)->Release();
         delete mCaptureDelegate.at(i);
         vec_mDLInput[i] = NULL;
       }
         if (vec_mDLOutput.at(0) != NULL)
         {
         vec_mDLOutput[0] = NULL;
         delete playerDelegate;
         }
    }
    delete mLocal;
}


bool carte_bmd::repatch_DL(INFO_CARTE* _ext, void** a)
{
    mLocal = _ext;
    int _c = 0;
    IDeckLinkIterator*				_DLIterator = NULL;
    IDeckLink*						_DL = NULL;
    _DLIterator = CreateDeckLinkIteratorInstance();

    if (_DLIterator == NULL)
    {
       QMessageBox::information(NULL, "L'application requiert l'installation des drivers Blackmagic", "Veuillez installer les drivers Blackmagic Desktop Video afin de pouvoir profiter des cartes Decklink.");
        return false;
    }

    for (int i = 0; i<mLocal->mNbr_io; i++)
    {
         if (vec_mDLInput.at(i) != NULL)
            { vec_mDLInput.at(i)->SetCallback(NULL);
             vec_mDLInput.at(i)->Release();
         delete mCaptureDelegate.at(i);
         vec_mDLInput[i] = NULL;
       }
         if (vec_mDLOutput.at(0) != NULL)
         {
             vec_mDLOutput.at(0)->SetAudioCallback(NULL);
         vec_mDLOutput[0] = NULL;


         }
    }
    delete playerDelegate;
    if (audioBuffer != NULL)
        free(audioBuffer);
    audioBuffer = NULL;



if(!Init_DL(a))
    return 0;
return true;
}

int carte_bmd::check_DL_IO()
{

    IDeckLinkIterator*				_DLIterator = NULL;
    IDeckLink*						_DL = NULL;
    _DLIterator = CreateDeckLinkIteratorInstance();

    if (_DLIterator == NULL)
    {
       QMessageBox::information(NULL, "L'application requiert l'installation des drivers Blackmagic", "Veuillez installer les drivers Blackmagic Desktop Video afin de pouvoir profiter des cartes Decklink.");
        return 0;
    }

    while (_DLIterator->Next(&_DL) == S_OK)
    {
            mLocal->mNbr_io++;
    }
if (mLocal->mNbr_io == 0)
{
    QMessageBox::information(NULL, "Aucune carte ne peux lire ou capture de flux.", "Référer vous à la documentation Blackmagic afin de résoudre le problème.");
     return 0;
}
        return 1;

}

string* carte_bmd::list_DL_IO()
{
    IDeckLinkIterator*				_DLIterator = NULL;
    IDeckLink*						_DL = NULL;
    HRESULT _result;
    int _numDevices = 0;
    m_IO = new string [10];

    _DLIterator = CreateDeckLinkIteratorInstance();

    // On énumère toutes les cartes disponibles
    while (_DLIterator->Next(&_DL) == S_OK) {
        char *deviceNameString = NULL;
        // *** On récupère le nom de la carte
        _result = _DL->GetModelName((const char **)&deviceNameString);
        if (_result == S_OK) {
            m_IO[_numDevices] = deviceNameString;
            free(deviceNameString);
        }
        _numDevices++;

    }
    if (_numDevices == 0) {
        printf("Aucune carte n'a été trouvée.\n");
    }

    return m_IO;

}

void carte_bmd::get_patch_DL(int* _a)
{
 mListe = NULL;
 mListe = _a;
}

bool carte_bmd::Init_DL_input()
{
    bool							_bSuccess = false;
    IDeckLinkIterator*				_DLIterator = NULL;
    IDeckLink*						_DL = NULL;
    IDeckLinkDisplayModeIterator*	_DLDisplayModeIterator = NULL;
    IDeckLinkDisplayMode*			_DLDisplayMode = NULL;
    BMDDisplayMode					_displayMode =  bmdModeHD1080p25;   //bmdModePAL; //bmdModeHD1080i50;	bmdModePAL	// mode to use for capture and playout

    int _c = 0;

    vec_mDLInput.resize(10);

    _DLIterator = CreateDeckLinkIteratorInstance();

    for (int i = 0; i <mLocal->mNbr_io; i++)

while (_DLIterator->Next(&_DL) == S_OK)
{

        if (mListe[_c] == 2 && !vec_mDLInput.at(mLocal->mNbr_i))
        {
            if (_DL->QueryInterface(IID_IDeckLinkInput, (void**)&vec_mDLInput.at(mLocal->mNbr_i)) != S_OK)
                goto error;
            mLocal->mNbr_i++;
        }
_c++;
}
    if (mLocal->mNbr_i == 0)
       {
              return true;
       }

    if (!mBMD_PLAYBACK) {
    for (int i = 0; i<mLocal->mNbr_i; i++)
    {

            if (vec_mDLInput.at(i)->GetDisplayModeIterator(&_DLDisplayModeIterator) != S_OK)
            {
                QMessageBox::critical(NULL, "Cannot get Display Mode Iterator.", "DeckLink error.");
                goto error;
            }
 }
        while (_DLDisplayModeIterator->Next(&_DLDisplayMode) == S_OK)
        {
            if (_DLDisplayMode->GetDisplayMode() == _displayMode)
                break;

            _DLDisplayMode->Release();
            _DLDisplayMode = NULL;
        }
        _DLDisplayModeIterator->Release();

        if (_DLDisplayMode == NULL)
        {
            QMessageBox::critical(NULL, "Cannot get specified BMDDisplayMode.", "DeckLink error.");
            goto error;
        }

    mFrameWidth = _DLDisplayMode->GetWidth();
    mFrameHeight = _DLDisplayMode->GetHeight();
    _DLDisplayMode->GetFrameRate(&mFrameDuration, &mFrameTimescale);



}


    for (int i =0; i<mLocal->mNbr_i; i++)
{
        if (vec_mDLInput.at(i)->EnableVideoInput(_displayMode, bmdFormat8BitYUV, bmdVideoInputFlagDefault) != S_OK)
            goto error;

       if (vec_mDLInput.at(i)->EnableAudioInput(_audioSampleRate, _audioSampleType,2) != S_OK)
            goto error;


        mCaptureDelegate.insert(i, new CaptureDelegate());
        if (vec_mDLInput.at(i)->SetCallback(mCaptureDelegate.at(i)) != S_OK)
            goto error;

    }


    // Utiliser les signaux et slots pour s'assurer qu'OpenGL rend dans le principal thread

    for (int i=0; i<mLocal->mNbr_i; i++)
    {
        connect(mCaptureDelegate.at(i), SIGNAL(captureFrameArrived(IDeckLinkVideoInputFrame*, bool)), this, SLOT(VideoFrameArrived(IDeckLinkVideoInputFrame*, bool)), Qt::QueuedConnection);
        connect(mCaptureDelegate.at(i), SIGNAL(captureAudioPacketArrived(IDeckLinkAudioInputPacket*)), this, SLOT(AudioPacketStreamArrived(IDeckLinkAudioInputPacket*)), Qt::QueuedConnection);

    }

    _bSuccess = true;

    error:
    if (!_bSuccess)
    {
        for (int i =0; i<mLocal->mNbr_i; i++)
            if (vec_mDLInput.at(i) != NULL)
            {
                vec_mDLInput.at(i)->Release();
            }}


    if (_DL != NULL)
    {
        _DL->Release();
        _DL = NULL;
    }

    if (_DLIterator != NULL)
    {
        _DLIterator->Release();
        _DLIterator = NULL;
    }


    return _bSuccess;
}

bool carte_bmd::Init_DL_output(void** _ref_to_out)
{

    bool							_bSuccess = false;
    IDeckLinkIterator*				_DLIterator = NULL;
    IDeckLink*						_DL = NULL;
    IDeckLinkDisplayModeIterator*	_DLDisplayModeIterator = NULL;
    IDeckLinkDisplayMode*			_DLDisplayMode = NULL;
    BMDDisplayMode					_displayMode =  bmdModeHD1080p25 ;   //	bmdModePAL; //bmdModeHD1080i50;	bmdModePAL	// mode to use for capture and playout

    int64_t first_audio_pts = AV_NOPTS_VALUE;
    int64_t first_pts       = AV_NOPTS_VALUE;
    int fill_me = 1;
    int _c = 0;

    vec_mDLOutput.resize(10);

    _DLIterator = CreateDeckLinkIteratorInstance();

    audioSampleDepth =
           av_get_exact_bits_per_sample(audio_st->codec->codec_id);

       switch (audio_st->codec->channels) {
           case  2:
           case  8:
           case 16:
               break;
           default:
               fprintf(stderr,
                       "%d channels not supported, please use 2, 8 or 16\n",
                       audio_st->codec->channels);

       }

       switch (audioSampleDepth) {
           case 16:
           case 32:
               break;
           default:
               fprintf(stderr, "%lubit audio not supported use 16bit or 32bit\n",
                       audioSampleDepth);
   }

    for (int i = 0; i <mLocal->mNbr_io; i++)
while (_DLIterator->Next(&_DL) == S_OK)
{
        if (mListe[_c] == 0 && !vec_mDLOutput.at(0))
        {
            if (_DL->QueryInterface(IID_IDeckLinkOutput, (void**)&vec_mDLOutput.at(0)) != S_OK)
                return 0;
            mLocal->mNbr_o++;
        }
_c++;
}
    // Create a delegate class to allow the DeckLink API to call into our code
    playerDelegate =  new PlaybackDelegate(this,vec_mDLOutput.at(0));
    if (playerDelegate == NULL)
        goto error;
    // Provide the delegate to the audio and video output interfaces
   vec_mDLOutput.at(0)->SetAudioCallback(playerDelegate);



    if(mLocal->mNbr_o == 0)
        mBMD_PLAYBACK = false;
    else
        mBMD_PLAYBACK = true;

 if (mBMD_PLAYBACK)
    {
     if (mLocal->mNbr_o == 0)
        {
               return true;
        }

    for (int i = 0; i<mLocal->mNbr_o; i++)
    {
        if (vec_mDLOutput.at(i)->GetDisplayModeIterator(&_DLDisplayModeIterator) != S_OK)
        {
            QMessageBox::critical(NULL, "Cannot get Display Mode Iterator.", "DeckLink error.");
            return 0;
        }
}
        while (_DLDisplayModeIterator->Next(&_DLDisplayMode) == S_OK)
        {
            if (_DLDisplayMode->GetDisplayMode() == _displayMode)
                break;

            _DLDisplayMode->Release();
            _DLDisplayMode = NULL;
        }
        _DLDisplayModeIterator->Release();

        if (_DLDisplayMode == NULL)
        {
            QMessageBox::critical(NULL, "Cannot get specified BMDDisplayMode.", "DeckLink error.");
            goto error;
        }

        mFrameWidth = _DLDisplayMode->GetWidth();
        mFrameHeight = _DLDisplayMode->GetHeight();
        _DLDisplayMode->GetFrameRate(&mFrameDuration, &mFrameTimescale);
        framesPerSecond = (mFrameTimescale + (mFrameDuration-1))  /  mFrameDuration;




        for (int i = 0; i <mLocal->mNbr_o; i++)
        {
            if (vec_mDLOutput.at(0)->EnableVideoOutput(_displayMode, bmdVideoOutputFlagDefault) != S_OK)
                goto error;
            if (vec_mDLOutput.at(0)->EnableAudioOutput(_audioSampleRate, _audioSampleType, 2, bmdAudioOutputStreamTimestamped) != S_OK)
                goto error;

            if (vec_mDLOutput.at(0)->CreateVideoFrame(mFrameWidth, mFrameHeight, mFrameWidth*4, bmdFormat8BitBGRA, bmdFrameFlagFlipVertical, &mOutFrame) != S_OK)
                goto error;

            mOutFrame->GetBytes(_ref_to_out);
        }

             IDeckLinkConfiguration*         deckLinkConfiguration;
                     if( vec_mDLOutput.at(0)->QueryInterface( IID_IDeckLinkConfiguration, (void**)&deckLinkConfiguration) != S_OK )
                                             {
                                                    cout << "la cest la m**de"<<endl;
                                             }

              if (deckLinkConfiguration->SetInt(bmdDeckLinkConfigVideoOutputConversionMode ,  bmdVideoOutputHardwareLetterboxDownconversion	) != S_OK )
                     {

              //cout << "la config marche pas ARG"<<endl;

              }
              if(deckLinkConfiguration->SetInt(BMDDeckLinkAudioOutputConnections, bmdAudioConnectionHeadphones) != S_OK)
              {
                  fprintf(stderr, "Pas de changement de connection audio en Headphones\n");
              }

/*

              audioSampleRate = _audioSampleRate;
              audioSamplesPerFrame = ((audioSampleRate * mFrameDuration) / mFrameTimescale);
              audioBufferSampleLength = (framesPerSecond * audioSampleRate * mFrameDuration) / mFrameTimescale;
              audioSampleDepth = _audioSampleType;
              audioChannelCount = 2;
              audioBuffer = malloc(audioBufferSampleLength * audioChannelCount * (audioSampleDepth / 8));
*/
              //memset(audioBuffer, 0x0, (audioBufferSampleLength * audioChannelCount * audioSampleDepth/8));



            //  if (audioBuffer == NULL)
            //      goto error;


         // FillSine(audioBuffer, audioBufferSampleLength, audioChannelCount, audioSampleDepth);

              packet_queue_init(&audioqueue);
              packet_queue_init(&dataqueue);
              pthread_t th;
              pthread_create(&th, NULL,fill_queues, NULL);

              // Begin audio preroll.  This will begin calling our audio callback, which will start the DeckLink output stream.
              totalAudioSecondsScheduled = 0;
             if (vec_mDLOutput.at(0)->BeginAudioPreroll() != S_OK)
                  goto error;

             pthread_mutex_lock(&sleepMutex);
                 pthread_cond_wait(&sleepCond, &sleepMutex);
                 pthread_mutex_unlock(&sleepMutex);
                 fill_me = 0;
                 fprintf(stderr, "Exiting, cleaning up\n");
             packet_queue_end(&audioqueue);
 }

        _bSuccess = true;

    error:
    if (!_bSuccess)
    {
        for (int i =0; i<mLocal->mNbr_o; i++)
        if (vec_mDLOutput.at(i) != NULL)
        {
            vec_mDLOutput.at(i)->Release();
        }}

    if (_DL != NULL)
    {
        _DL->Release();
        _DL = NULL;
    }
    if (_DLIterator != NULL)
    {
        _DLIterator->Release();
        _DLIterator = NULL;
    }
    return _bSuccess;

}

bool carte_bmd::Init_DL(void** _ref_to_out)
{
    if(!Init_DL_input() || !Init_DL_output(_ref_to_out))
    return false;
    else
    {
    return true;
    }
}

bool carte_bmd::writetoDLcard()
 {
     {  // C'est ici que l'on envoie sur la carte de sortie l'image rendue
        if(vec_mDLOutput.at(0)->DisplayVideoFrameSync(mOutFrame) != S_OK)
            return false;
        else
            return true;
     }
}


void carte_bmd::VideoFrameArrived(IDeckLinkVideoInputFrame* _inputFrame, bool _hasNoInputSource)
{
    CaptureDelegate *delegsender = qobject_cast <CaptureDelegate*> (sender());
    int _identifiant_sender;
    for (int i=0; i<mCaptureDelegate.size();i++)
    {

        if (delegsender == mCaptureDelegate.at(i))
        {
            _identifiant_sender=i;

        }
    }
   void* pFrame;
   _inputFrame->GetBytes(&pFrame);
   emit emitVideoFrame(&pFrame, _identifiant_sender);
   _inputFrame->Release();




}

void carte_bmd::AudioPacketStreamArrived(IDeckLinkAudioInputPacket* _audioPacket)
{
    void* audioBytes;
    _audioPacket->GetBytes(&audioBytes);
    SampleFrameCount = _audioPacket->GetSampleFrameCount();
    long sampleLength = SampleFrameCount* 2 * 2;



}
bool carte_bmd::start_DL()
{

    for (int i=0; i<mLocal->mNbr_i;i++)
    {
        vec_mDLInput.at(i)->StartStreams();
    }

    vec_mDLOutput.at(0)->StartScheduledPlayback(0, 100, 0.1);

    return true;
}


bool carte_bmd::stop_DL()
{
    if (audioBuffer != NULL)
        free(audioBuffer);
    audioBuffer = NULL;
    for (int i = 0; i < 10; i++)
    {
        if (vec_mDLInput.at(i))
        {
    vec_mDLInput.at(i)->StopStreams();
    vec_mDLInput.at(i)->DisableVideoInput();
    vec_mDLInput.at(i)->DisableAudioInput();
        }
    }
    if (mBMD_PLAYBACK)
    {
        vec_mDLOutput.at(0)->DisableVideoOutput();
        vec_mDLOutput.at(0)->DisableAudioOutput();
    }
    return true;
}

int  carte_bmd::access_height()
{
    return (int)mFrameHeight;
}

int carte_bmd::access_width()
{
    return (int)mFrameWidth;
}

int carte_bmd::access_duration()
{
    return (int)(1000/(mFrameTimescale/mFrameDuration));
}

int carte_bmd::access_nbinput()
{
    return mLocal->mNbr_i;
}

void carte_bmd::writeNextAudioSamples()
{

        uint32_t samplesWritten = 0;
        AVPacket pkt            = { 0 };
        unsigned int bufferedSamples;
        int got_frame = 0;
        int i;
        int bytes_per_sample =
            av_get_bytes_per_sample(audio_st->codec->sample_fmt) *
            audio_st->codec->channels;
        int samples, off = 0;

        vec_mDLOutput.at(0)->GetBufferedAudioSampleFrameCount(&bufferedSamples);

        if (bufferedSamples > kAudioWaterlevel)
            return;

        if (!packet_queue_get(&audioqueue, &pkt, 0) < 0)
            return;

        samples = pkt.size / bytes_per_sample;

        do {
            if (vec_mDLOutput.at(0)->ScheduleAudioSamples(pkt.data +
                                                       off * bytes_per_sample,
                                                       samples,
                                                       pkt.pts + off,
                                                       audio_st->time_base.den / audio_st->time_base.num,
                                                       &samplesWritten) != S_OK)
                fprintf(stderr, "error writing audio sample\n");
            samples -= samplesWritten;
            off     += samplesWritten;
        } while (samples > 0);

    av_packet_unref(&pkt);

}
int carte_bmd::packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
    AVPacketList *pkt1;
    int ret;

    pthread_mutex_lock(&q->mutex);

       for (;; ) {
           pkt1 = q->first_pkt;
           if (pkt1) {
               q->first_pkt = pkt1->next;
               if (!q->first_pkt)
                   q->last_pkt = NULL;
               q->nb_packets--;
               if (q->nb_packets > 5000)
                   fprintf(stderr, "pulling %"PRId64" from %p %s\n",
                           q->nb_packets,
                           q,
                           q == &videoqueue ? "videoqueue" : "audioqueue");
               q->size -= pkt1->pkt.size + sizeof(*pkt1);
               *pkt     = pkt1->pkt;
               av_free(pkt1);
               ret = 1;
               break;
           } else if (!block) {
               ret = 0;
               break;
           } else {
               if (q->abort_request) {
                   ret = -1;
                   break;
               }
               pthread_cond_wait(&q->cond, &q->mutex);
           }
       }
       pthread_mutex_unlock(&q->mutex);
   return ret;
}

void*carte_bmd::fill_queues(void *unused)
{
    AVPacket pkt;
    AVStream *st;
    int once = 0;

            if (pkt.pts != AV_NOPTS_VALUE) {
                if (first_pts == AV_NOPTS_VALUE) {
                    first_pts       = first_audio_pts = pkt.pts;
                }
                pkt.pts -= first_audio_pts;
            }
            packet_queue_put(&audioqueue, &pkt);

    return NULL;
}

int carte_bmd::packet_queue_put(PacketQueue *q, AVPacket *pkt)
{
    AVPacketList *pkt1;

    pkt1 = (AVPacketList *)av_malloc(sizeof(AVPacketList));
    if (!pkt1)
        return -1;
    pkt1->pkt  = *pkt;
    pkt1->next = NULL;

    pthread_mutex_lock(&q->mutex);

    if (!q->last_pkt)

        q->first_pkt = pkt1;
    else
        q->last_pkt->next = pkt1;
    q->last_pkt = pkt1;
    q->nb_packets++;
    if (q->nb_packets > 5000)
        fprintf(stderr,
                "%"PRId64" storing %p, %s - is the input faster than realtime?\n",
                q->nb_packets,
                q,
                q == &videoqueue ? "videoqueue" : "audioqueue");
    q->size += pkt1->pkt.size + sizeof(*pkt1);

    pthread_cond_signal(&q->cond);

    pthread_mutex_unlock(&q->mutex);
    return 0;
}

void carte_bmd::packet_queue_end(PacketQueue *q)
{
    packet_queue_flush(q);
    pthread_mutex_lock(&q->mutex);
    q->abort_request = -1;
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->mutex);
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->cond);
}
void carte_bmd::packet_queue_flush(PacketQueue *q){

    AVPacketList *pkt, *pkt1;

        pthread_mutex_lock(&q->mutex);
        for (pkt = q->first_pkt; pkt != NULL; pkt = pkt1) {
            pkt1 = pkt->next;
            av_packet_unref(&pkt->pkt);
            av_freep(&pkt);
        }
        q->last_pkt   = NULL;
        q->first_pkt  = NULL;
        q->nb_packets = 0;
        q->size       = 0;
    pthread_mutex_unlock(&q->mutex);
}
void carte_bmd::packet_queue_init(PacketQueue *q)
{
    memset(q, 0, sizeof(PacketQueue));
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cond, NULL);
}

////////////////////////////////////////////
// DeckLink Capture Delegate Class
////////////////////////////////////////////
HRESULT	CaptureDelegate::VideoInputFrameArrived(IDeckLinkVideoInputFrame* inputFrame, IDeckLinkAudioInputPacket* audioPacket)
{
    if (! inputFrame)
    {
        // It's possible to receive a NULL inputFrame, but a valid audioPacket. Ignore audio-only frame.
        return S_OK;
    }

    bool hasNoInputSource = inputFrame->GetFlags() & bmdFrameHasNoInputSource;

    // emit just adds a message to Qt's event queue since we're in a different thread, so add a reference
    // to the input frame to prevent it getting released before the connected slot can process the frame.
    inputFrame->AddRef();

    emit captureFrameArrived(inputFrame, hasNoInputSource);

    // Handle Audio Frame
                if (!audioPacket)
                {
                                return E_FAIL;
                }

                audioPacket->AddRef();
   emit captureAudioPacketArrived(audioPacket);

                // Handle Audio Frame

    return S_OK;
}

HRESULT	CaptureDelegate::VideoInputFormatChanged(BMDVideoInputFormatChangedEvents /*notificationEvents*/, IDeckLinkDisplayMode* /*newDisplayMode*/, BMDDetectedVideoInputFormatFlags /*detectedSignalFlags*/)
{
    fprintf(stderr, "VideoInputFormatChanged()\n");
    return S_OK;
}


PlaybackDelegate::PlaybackDelegate (carte_bmd* owner, IDeckLinkOutput* deckLinkOutput)
{
    mRefCount = 1;
    mController = owner;
    mDeckLinkOutput = deckLinkOutput;
}

HRESULT		PlaybackDelegate::QueryInterface (REFIID, LPVOID *ppv)
{
    *ppv = NULL;
    return E_NOINTERFACE;
}

ULONG		PlaybackDelegate::AddRef ()
{
    int		oldValue;

    oldValue = mRefCount.fetchAndAddAcquire(1);
    return (ULONG)(oldValue + 1);
}

ULONG		PlaybackDelegate::Release ()
{
    int		oldValue;

    oldValue = mRefCount.fetchAndAddAcquire(-1);
    if (oldValue == 1)
    {
        delete this;
    }

    return (ULONG)(oldValue - 1);
}


HRESULT		PlaybackDelegate::ScheduledPlaybackHasStopped ()
{
    return S_OK;
}

HRESULT		PlaybackDelegate::RenderAudioSamples (bool preroll)
{
    // Provide further audio samples to the DeckLink API until our preferred buffer waterlevel is reached
    mController->writeNextAudioSamples();

    if (preroll)
    {
        // Start audio and video output
        mDeckLinkOutput->StartScheduledPlayback(0, 100, 1.0);
    }

    return S_OK;
}

void	FillSine (void* audioBuffer, uint32_t samplesToWrite, uint32_t channels, uint32_t sampleDepth)
{
    if (sampleDepth == 16)
    {
        int16_t*		nextBuffer;

        nextBuffer = (int16_t*)audioBuffer;
        for (uint32_t i = 0; i < samplesToWrite; i++)
        {
            int16_t		sample;

            sample = (int16_t)(24576.0 * sin((i * 2.0 * M_PI) / 48.0));
            for (uint32_t ch = 0; ch < channels; ch++)
                *(nextBuffer++) = sample;
        }
    }
    else if (sampleDepth == 32)
    {
        int32_t*		nextBuffer;

        nextBuffer = (int32_t*)audioBuffer;
        for (uint32_t i = 0; i < samplesToWrite; i++)
        {
            int32_t		sample;

            sample = (int32_t)(1610612736.0 * sin((i * 2.0 * M_PI) / 48.0));
            for (uint32_t ch = 0; ch < channels; ch++)
                *(nextBuffer++) = sample;
        }
    }
}
