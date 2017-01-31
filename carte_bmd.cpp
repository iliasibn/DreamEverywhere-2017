//#include <opencv/highgui.h>
#include "carte_bmd.h"
#include <QMessageBox>
#include <iostream>
#include <stdio.h>
#include <string>
#include <LoopThroughWithOpenGLCompositing.h>

using namespace std;

carte_bmd::carte_bmd(QWidget *_parent, INFO_CARTE * _ext):
  mParent(_parent),
  mPlayoutDelegate(NULL),
  mListe(0),
  mLocal(_ext),
  m_IO(0),
  mBMD_PLAYBACK(true),
  mOutFrame(0)
 {
    // On enregistre des types de données dans la base de donnée Qt afin de pouvoir établir des signaux et slots
    qRegisterMetaType<IDeckLinkVideoInputFrame*>("IDeckLinkVideoInputFrame*");
    qRegisterMetaType<IDeckLinkAudioInputPacket*>("IDeckLinkAudioInputPacket*");
    qRegisterMetaType<IDeckLinkVideoFrame*>("IDeckLinkVideoFrame*");
    qRegisterMetaType<BMDOutputFrameCompletionResult>("BMDOutputFrameCompletionResult");

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
         delete mPlayoutDelegate;
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
         vec_mDLOutput[0] = NULL;
         delete mPlayoutDelegate;
         }
    }

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

        if (vec_mDLInput.at(i)->EnableAudioInput(bmdAudioSampleRate48kHz, 16, 2)!= S_OK)
            goto error;

        mCaptureDelegate.insert(i, new CaptureDelegate());

        if (vec_mDLInput.at(i)->SetCallback(mCaptureDelegate.at(i)) != S_OK)
            goto error;

    }


    // Utiliser les signaux et slots pour s'assurer qu'OpenGL rend dans le principal thread

    for (int i=0; i<mLocal->mNbr_i; i++)
    {
        connect(mCaptureDelegate.at(i), SIGNAL(captureFrameArrived(IDeckLinkVideoInputFrame*, bool)), this, SLOT(VideoFrameArrived(IDeckLinkVideoInputFrame*, bool)), Qt::QueuedConnection);

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

        for (int i = 0; i <mLocal->mNbr_o; i++)
        {
        if (vec_mDLOutput.at(0)->EnableVideoOutput(_displayMode, bmdVideoOutputFlagDefault) != S_OK)
            goto error;

        if (vec_mDLOutput.at(0)->EnableAudioOutput(bmdAudioSampleRate48kHz, 16, 2, bmdAudioOutputStreamTimestamped)!= S_OK)
            goto error;

        if (vec_mDLOutput.at(0)->CreateVideoFrame(mFrameWidth, mFrameHeight, mFrameWidth*4, bmdFormat8BitBGRA, bmdFrameFlagFlipVertical, &mOutFrame) != S_OK)
            goto error;
        if (vec_mDLOutput.at(0)->BeginAudioPreroll()!= S_OK)
            goto error;


     mOutFrame->GetBytes(_ref_to_out);

     connect(mPlayoutDelegate, SIGNAL(writenextaudiosamplesemit(bool)), this, SLOT(WriteNextAudioSamples(bool)), Qt::QueuedConnection);

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


bool carte_bmd::start_DL()
{
    // Generate one second of audio tone
    audioSamplesPerFrame = ((audioSampleRate * frameDuration) / frameTimescale);
    audioBufferSampleLength = (framesPerSecond * audioSampleRate * frameDuration) / frameTimescale;
    audioBuffer = malloc(audioBufferSampleLength * audioChannelCount * (audioSampleDepth / 8));

    if (audioBuffer == NULL)
        goto bail;
    FillSine(audioBuffer, audioBufferSampleLength, audioChannelCount, audioSampleDepth);

    for (int i=0; i<mLocal->mNbr_i;i++)
    {
        vec_mDLInput.at(i)->StartStreams();
    }
    if (vec_mDLOutput.at(i)->BeginAudioPreroll() != S_OK)
        goto bail;
    return true;

}


bool carte_bmd::stop_DL()
{
    for (int i = 0; i < 10; i++)
    {
        if (vec_mDLInput.at(i))
        {
    vec_mDLInput.at(i)->StopStreams();
    vec_mDLInput.at(i)->DisableVideoInput();
        }
    }
    if (mBMD_PLAYBACK)
    {
        vec_mDLOutput.at(0)->DisableVideoOutput();
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

void carte_bmd::WriteNextAudioSamples(bool preroll)
{

    unsigned int bufferedSamples;

    vec_mDLOutput.at(0)->GetBufferedAudioSampleFrameCount(&bufferedSamples);

    vec_mDLOutput.at(0)->ScheduleAudioSamples(audioBuffer, audioSamplesPerFrame, (totalAudioSecondsScheduled * audioBufferSampleLength), audioSampleRate, NULL);


    totalAudioSecondsScheduled += 1;

    if (preroll)
    {
        // Start audio and video output
        vec_mDLOutput.at(0)->StartScheduledPlayback(0, 100, 1.0);
    }

}



////////////////////////////////////////////
// DeckLink Capture Delegate Class
////////////////////////////////////////////
HRESULT	CaptureDelegate::VideoInputFrameArrived(IDeckLinkVideoInputFrame* inputFrame, IDeckLinkAudioInputPacket* audioPacket)
{
  /*  void* frameBytes;
    void* audioFrameBytes;
    int audioOutputFile = -1;
    static int g_audioChannels = 2;
    static int g_audioSampleDepth = 16;
    const char * g_audioOutputFile = NULL;
    Sound *audioengine;*/
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
                if (audioPacket)
                {
/*
                        if (audioOutputFile != -1)
                        {
                                audioPacket->GetBytes(&audioFrameBytes);
<<<<<<< HEAD
                               // vec_mDLOutput.at(0)->WriteAudioSamplesSync(audioFrameBytes,audioPacket->GetSampleFrameCount(), (uint32_t*)(audioPacket->GetSampleFrameCount() * g_audioChannels * (g_audioSampleDepth / 8)));
                        }
=======

                                audioengine = new Sound();
                                audioengine->searchforinput();
                                audioengine->startaudiostream(audioFrameBytes,audioPacket->GetSampleFrameCount());

                               write(g_audioOutputFile, audioFrameBytes, audioPacket->GetSampleFrameCount() * g_audioChannels * (g_audioSampleDepth / 8));


                        }*/
>>>>>>> a902e335b697d8d13b0d0e230af17602f5e2277c
                }

    return S_OK;
}

HRESULT	CaptureDelegate::VideoInputFormatChanged(BMDVideoInputFormatChangedEvents /*notificationEvents*/, IDeckLinkDisplayMode* /*newDisplayMode*/, BMDDetectedVideoInputFormatFlags /*detectedSignalFlags*/)
{
    fprintf(stderr, "VideoInputFormatChanged()\n");
    return S_OK;
}

HRESULT PlayoutDelegate::RenderAudioSamples(bool preroll)
{
    // Provide further audio samples to the DeckLink API until our preferred buffer waterlevel is reached
    emit writenextaudiosamplesemit(preroll);

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
