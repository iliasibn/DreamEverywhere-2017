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

    int _c = 0;
    vec_mDLOutput.resize(10);

    _DLIterator = CreateDeckLinkIteratorInstance();



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



              audioSampleRate = _audioSampleRate;
              audioSamplesPerFrame = ((audioSampleRate * mFrameDuration) / mFrameTimescale);
              audioBufferSampleLength = (framesPerSecond * audioSampleRate * mFrameDuration) / mFrameTimescale;
              audioSampleDepth = _audioSampleType;
              audioChannelCount = 2;
              audioBuffer = malloc(audioBufferSampleLength * audioChannelCount * (audioSampleDepth / 8));

              //memset(audioBuffer, 0x0, (audioBufferSampleLength * audioChannelCount * audioSampleDepth/8));



              if (audioBuffer == NULL)
                  goto error;


          FillSine(audioBuffer, audioBufferSampleLength, audioChannelCount, audioSampleDepth);


              // Begin audio preroll.  This will begin calling our audio callback, which will start the DeckLink output stream.
              totalAudioSecondsScheduled = 0;
             if (vec_mDLOutput.at(0)->BeginAudioPreroll() != S_OK)
                  goto error;
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
    //SampleFrameCount = _SampleFrameCount;
    //long sampleLength = SampleFrameCount* 2 * 2;

   //memcpy(audioBuffer,_audioBytes,SampleFrameCount);
    void *audioFrameBytes;
    AVCodecContext *c;
            AVPacket pkt;
            BMDTimeValue audio_pts;
           // av_init_packet(&pkt);

            c = audio_st->codec;
            //hack among hacks
            pkt.size = _audioPacket->GetSampleFrameCount() *
                       audioChannelCount* (audioSampleDepth / 8);
            _audioPacket->GetBytes(&audioFrameBytes);
            _audioPacket->GetPacketTime(&audio_pts, audio_st->time_base.den);
            pkt.pts = audio_pts / audio_st->time_base.num;
 /*  if (initial_audio_pts == AV_NOPTS_VALUE) {
       initial_audio_pts = pkt.pts;
   }

   pkt.pts -= initial_audio_pts;
   pkt.dts = pkt.pts;*/

   //fprintf(stderr,"Audio Frame size %d ts %d\n", pkt.size, pkt.pts);
   pkt.flags       |= AV_PKT_FLAG_KEY;
   pkt.stream_index = audio_st->index;
   pkt.data         = (uint8_t *)audioFrameBytes;
   //pkt.size= avcodec_encode_audio(c, audio_outbuf, audio_outbuf_size, samples);
   c->frame_number++;


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

            sampleFramesWritten = 0;

                BMDTimeValue streamTime = totalAudioSecondsScheduled * audioSampleRate * (mFrameDuration / mFrameTimescale);
                vec_mDLOutput.at(0)->GetBufferedAudioSampleFrameCount( &sampleFramesWritten );


                vec_mDLOutput.at(0)->ScheduleAudioSamples(audioBuffer,audioBufferSampleLength, streamTime, audioSampleRate, &sampleFramesWritten);

              totalAudioSecondsScheduled+=1;



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
