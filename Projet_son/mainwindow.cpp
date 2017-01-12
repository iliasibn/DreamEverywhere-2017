#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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

        searchforinput();
        startaudiostream(1);

}
void MainWindow::startaudiostream(int signal)
{
    output.deviceId = 2;
    output.nChannels = 2;
    output.firstChannel = 0;

    input.deviceId = audio->getDefaultInputDevice();
    input.nChannels = 2;
    input.firstChannel = 0;

    RtAudio::StreamOptions options;

    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 512;

    unsigned int bufferBytes = bufferFrames * input.nChannels * sizeof( MY_TYPE );
/*
    for (int i =0; i<mLocal->mNbr_i; i++)
    {
        if (vec_mDLInput.at(i)->EnableAudioInput(sampleRate, FORMAT, output.nChannels))
            goto error;

    }
*/

    try {
        if(signal == 0)
        {
        audio->openStream(&output,&input, FORMAT, sampleRate,
                          &bufferFrames, &duplex, (void *)&bufferBytes,
                          &options);
        }
        else if (signal == 1)
        {
           audio->openStream(&output,NULL, FORMAT, sampleRate,
                              &bufferFrames, &saw,static_cast<void*>(&num),
                              &options,&ErrorCallback);
        }
        audio->startStream();
    }
    catch (RtAudioError& e) {
        e.printMessage();
        exit(0);
    }

}
int MainWindow::saw(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *data)
{
    unsigned int i, j;
    unsigned int channels = 2;
    MY_TYPE *buffer = (MY_TYPE *) outputBuffer;
    double *lastValues = (double *) data;

    if ( status )
      std::cout << "Stream underflow detected!" << std::endl;

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

int MainWindow::duplex( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                           double streamTime, RtAudioStreamStatus status, void *data )
                {
                  // Since the number of input and output channels is equal, we can do
                  // a simple buffer copy operation here.
                  if ( status ) std::cout << "Stream over/underflow detected." << std::endl;

                  unsigned int *bytes = (unsigned int *) data;
                  memcpy( outputBuffer, inputBuffer, *bytes );
                  return 0;
                }

void MainWindow::ErrorCallback( RtAudioError::Type type, const std::string &errorText )
{
  // This example error handling function does exactly the same thing
  // as the embedded RtAudio::error() function.
  std::cout << "in errorCallback" << std::endl;
  if ( type == RtAudioError::WARNING )
    std::cerr << '\n' << errorText << "\n\n";
  else if ( type != RtAudioError::WARNING )
    throw( RtAudioError( errorText, type ) );
}

int MainWindow::searchforinput()
{
    RtAudio::DeviceInfo info;
unsigned int devices = audio->getDeviceCount();
  std::cout << "\nFound " << devices << " device(s) ...\n";

  for (unsigned int i=0; i<devices; i++) {
    info = audio->getDeviceInfo(i);

    std::cout << "\nDevice Name = " << info.name << '\n';
    if ( info.probed == false )
      std::cout << "Probe Status = UNsuccessful\n";
    else {
      std::cout << "Probe Status = Successful\n";
      std::cout << "Output Channels = " << info.outputChannels << '\n';
      std::cout << "Input Channels = " << info.inputChannels << '\n';
      std::cout << "Duplex Channels = " << info.duplexChannels << '\n';
      if ( info.isDefaultOutput ) std::cout << "This is the default output device.\n";
      else std::cout << "This is NOT the default output device.\n";
      if ( info.isDefaultInput ) std::cout << "This is the default input device.\n";
      else std::cout << "This is NOT the default input device.\n";
      if ( info.nativeFormats == 0 )
        std::cout << "No natively supported data formats(?)!";
      else {
        std::cout << "Natively supported data formats:\n";
        if ( info.nativeFormats & RTAUDIO_SINT8 )
          std::cout << "  8-bit int\n";
        if ( info.nativeFormats & RTAUDIO_SINT16 )
          std::cout << "  16-bit int\n";
        if ( info.nativeFormats & RTAUDIO_SINT24 )
          std::cout << "  24-bit int\n";
        if ( info.nativeFormats & RTAUDIO_SINT32 )
          std::cout << "  32-bit int\n";
        if ( info.nativeFormats & RTAUDIO_FLOAT32 )
          std::cout << "  32-bit float\n";
        if ( info.nativeFormats & RTAUDIO_FLOAT64 )
          std::cout << "  64-bit float\n";
      }
      if ( info.sampleRates.size() < 1 )
        std::cout << "No supported sample rates found!";
      else {
        std::cout << "Supported sample rates = ";
        for (unsigned int j=0; j<info.sampleRates.size(); j++)
          std::cout << info.sampleRates[j] << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
  return 0;


}
MainWindow::~MainWindow()
{
    if ( audio->isStreamOpen() ) audio->closeStream();
    // Clean up
     delete audio;
}



