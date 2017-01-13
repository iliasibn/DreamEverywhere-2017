#include "Sound.h"

using namespace std;

Sound::Sound()
{
      audio = 0;

      // Default RtAudio constructor
      try {
        audio = new RtAudio();
      }
      catch (RtAudioError &error) {
        // Handle the exception here
        error.printMessage();
      }
    //searchforinput();

}
void Sound::startaudiostream(void *AudioBuffer,unsigned int _sampleRate)
{
    output.deviceId = 2;
    output.nChannels = 2;
    output.firstChannel = 0;

    input.deviceId = 2;
    input.nChannels = 2;
    input.firstChannel = 0;

    RtAudio::StreamOptions options;

    sampleRate = _sampleRate;
    unsigned int bufferFrames = 512;


    try {

           audio->openStream(&output,NULL, FORMAT, sampleRate,
                              &bufferFrames, &duplex,static_cast<void*>(&num),
                              &options,&ErrorCallback);

           audio->startStream();
    }
    catch (RtAudioError& e) {
        e.printMessage();
        exit(0);
    }

}
int Sound::saw(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *data)
{
    unsigned int i, j;
    unsigned int channels = 2;
    MY_TYPE *buffer = (MY_TYPE *) outputBuffer;
    double *lastValues = (double *) data;

    if ( status )
      cout << "Stream underflow detected!" << endl;

    for ( i=0; i<nBufferFrames; i++ ) {
      for ( j=0; j<channels; j++ ) {
        *buffer++ = (MY_TYPE) (lastValues[j] * SCALE * 0.5);
        lastValues[j] += BASE_RATE * (j+1+(j*0.1));
        if ( lastValues[j] >= 1.0 ) lastValues[j] -= 2.0;
      }
    }
    unsigned int frameCounter = 0;
    frameCounter += nBufferFrames;
    bool checkCount = false;
    unsigned int nFrames = 0;
    const unsigned int callbackReturnValue = 1;

    if ( checkCount && ( frameCounter >= nFrames ) ) return callbackReturnValue;
  return 0;
}

int Sound::duplex( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                           double streamTime, RtAudioStreamStatus status, void *data )
                {
                  // Since the number of input and output channels is equal, we can do
                  // a simple buffer copy operation here.
                  if ( status ) cout << "Stream over/underflow detected." << endl;

                  unsigned int *bytes = (unsigned int *) data;
                  memcpy( outputBuffer, inputBuffer, *bytes );
                  return 0;
                }

void Sound::ErrorCallback( RtAudioError::Type type, const string &errorText )
{
  // This example error handling function does exactly the same thing
  // as the embedded RtAudio::error() function.
  cout << "in errorCallback" << endl;
  if ( type == RtAudioError::WARNING )
    cerr << '\n' << errorText << "\n\n";
  else if ( type != RtAudioError::WARNING )
    throw( RtAudioError( errorText, type ) );
}

int Sound::searchforinput()
{
    RtAudio::DeviceInfo info;
    unsigned int devices = audio->getDeviceCount();



   //cout << "\nFound " << devices << " device(s) ...\n";
/*
  for (unsigned int i=0; i<devices; i++) {
    info = audio->getDeviceInfo(i);

    cout << "\nDevice Name = " << info.name << '\n';
    if ( info.probed == false )
      cout << "Probe Status = UNsuccessful\n";
    else {
      cout << "Probe Status = Successful\n";
      cout << "Output Channels = " << info.outputChannels << '\n';
      cout << "Input Channels = " << info.inputChannels << '\n';
      cout << "Duplex Channels = " << info.duplexChannels << '\n';
      if ( info.isDefaultOutput ) cout << "This is the default output device.\n";
      else cout << "This is NOT the default output device.\n";
      if ( info.isDefaultInput ) cout << "This is the default input device.\n";
      else cout << "This is NOT the default input device.\n";
      if ( info.nativeFormats == 0 )
        cout << "No natively supported data formats(?)!";
      else {
        cout << "Natively supported data formats:\n";
        if ( info.nativeFormats & RTAUDIO_SINT8 )
          cout << "  8-bit int\n";
        if ( info.nativeFormats & RTAUDIO_SINT16 )
          cout << "  16-bit int\n";
        if ( info.nativeFormats & RTAUDIO_SINT24 )
          cout << "  24-bit int\n";
        if ( info.nativeFormats & RTAUDIO_SINT32 )
          cout << "  32-bit int\n";
        if ( info.nativeFormats & RTAUDIO_FLOAT32 )
          cout << "  32-bit float\n";
        if ( info.nativeFormats & RTAUDIO_FLOAT64 )
          cout << "  64-bit float\n";
      }
      if ( info.sampleRates.size() < 1 )
        cout << "No supported sample rates found!";
      else {
        cout << "Supported sample rates = ";
        for (unsigned int j=0; j<info.sampleRates.size(); j++)
          cout << info.sampleRates[j] << " ";
      }
      cout << endl;
    }
  }
  cout << endl; */
  return 0;


}
Sound::~Sound()
{
    if ( audio->isStreamOpen() ) audio->closeStream();
    // Clean up
     delete audio;
}



