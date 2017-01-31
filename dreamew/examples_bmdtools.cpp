// BMD Capture

void print_output_modes(IDeckLink *deckLink)
{
    IDeckLinkOutput *deckLinkOutput                   = NULL;
    IDeckLinkDisplayModeIterator *displayModeIterator = NULL;
    IDeckLinkDisplayMode *displayMode                 = NULL;
    HRESULT result;
    int displayModeCount = 0;

    // Query the DeckLink for its configuration interface
    result = deckLink->QueryInterface(IID_IDeckLinkOutput,
                                      (void **)&deckLinkOutput);
    if (result != S_OK) {
        fprintf(
            stderr,
            "Could not obtain the IDeckLinkOutput interface - result = %08x\n",
            result);
        goto bail;
    }

    // Obtain an IDeckLinkDisplayModeIterator to enumerate the display modes supported on output
    result = deckLinkOutput->GetDisplayModeIterator(&displayModeIterator);
    if (result != S_OK) {
        fprintf(
            stderr,
            "Could not obtain the video output display mode iterator - result = %08x\n",
            result);
        goto bail;
    }

    // List all supported output display modes
    printf("Supported video output display modes and pixel formats:\n");
    while (displayModeIterator->Next(&displayMode) == S_OK) {
        char *displayModeString = NULL;

        result = displayMode->GetName((const char **)&displayModeString);
        if (result == S_OK) {
            char modeName[64];
            int modeWidth;
            int modeHeight;
            BMDTimeValue frameRateDuration;
            BMDTimeScale frameRateScale;
            int pixelFormatIndex = 0;                     // index into the gKnownPixelFormats / gKnownFormatNames arrays
            BMDDisplayModeSupport displayModeSupport;
            // Obtain the display mode's properties
            modeWidth  = displayMode->GetWidth();
            modeHeight = displayMode->GetHeight();
            displayMode->GetFrameRate(&frameRateDuration, &frameRateScale);
            printf("        %2d:   %-20s \t %d x %d \t %7g FPS\n",
                   displayModeCount++, displayModeString, modeWidth, modeHeight,
                   (double)frameRateScale / (double)frameRateDuration);

            free(displayModeString);
        }
        // Release the IDeckLinkDisplayMode object to prevent a leak
        displayMode->Release();
    }
//	printf("\n");
bail:
    // Ensure that the interfaces we obtained are released to prevent a memory leak
    if (displayModeIterator != NULL) {
        displayModeIterator->Release();
    }
    if (deckLinkOutput != NULL) {
        deckLinkOutput->Release();
    }
}

int usage(int status)
{
    HRESULT result;
    IDeckLinkIterator *deckLinkIterator;
    IDeckLink *deckLink;
    int numDevices = 0;
//  int                displayModeCount = 0;

    fprintf(stderr,
            "Usage: bmdcapture -m <mode id> [OPTIONS]\n"
            "\n"
            "    -m <mode id>:\n"
            );

    // Create an IDeckLinkIterator object to enumerate all DeckLink cards in the system
    deckLinkIterator = CreateDeckLinkIteratorInstance();
    if (deckLinkIterator == NULL) {
        fprintf(
            stderr,
            "A DeckLink iterator could not be created.  The DeckLink drivers may not be installed.\n");
        return 1;
    }

    // Enumerate all cards in this system
    while (deckLinkIterator->Next(&deckLink) == S_OK) {
        char *deviceNameString = NULL;

        // Increment the total number of DeckLink cards found
        numDevices++;
        if (numDevices > 1) {
            printf("\n\n");
        }

        // *** Print the model name of the DeckLink card
        result = deckLink->GetModelName((const char **)&deviceNameString);
        if (result == S_OK) {
            printf("=============== %s (-C %d )===============\n\n",
                   deviceNameString,
                   numDevices - 1);
            free(deviceNameString);
        }

        print_output_modes(deckLink);
        // Release the IDeckLink instance when we've finished with it to prevent leaks
        deckLink->Release();
    }
    deckLinkIterator->Release();

    // If no DeckLink cards were found in the system, inform the user
    if (numDevices == 0) {
        printf("No Blackmagic Design devices were found.\n");
    }
    printf("\n");

/*
 *  if (displayModeIterator)
 *  {
 *      // we try to print out some useful information about the chosen
 *      // card, but this only works if a card has been selected successfully
 *
 *      while (displayModeIterator->Next(&displayMode) == S_OK)
 *      {
 *          char *          displayModeString = NULL;
 *
 *          result = displayMode->GetName((const char **) &displayModeString);
 *          if (result == S_OK)
 *          {
 *              BMDTimeValue frameRateDuration, frameRateScale;
 *              displayMode->GetFrameRate(&frameRateDuration, &frameRateScale);
 *              fprintf(stderr, "        %2d:  %-20s \t %li x %li \t %g FPS\n",
 *                  displayModeCount, displayModeString, displayMode->GetWidth(), displayMode->GetHeight(), (double)frameRateScale / (double)frameRateDuration);
 *              free(displayModeString);
 *              displayModeCount++;
 *          }
 *
 *          // Release the IDeckLinkDisplayMode object to prevent a leak
 *          displayMode->Release();
 *      }
 *  }
 */
    fprintf(
        stderr,
        "    -v                   Be verbose (report each 25 frames)\n"
        "    -f <filename>        Filename raw video will be written to\n"
        "    -F <format>          Define the file format to be used\n"
        "    -c <channels>        Audio Channels (2, 8 or 16 - default is 2)\n"
        "    -s <depth>           Audio Sample Depth (16 or 32 - default is 16)\n"
        "    -p <pixel>           PixelFormat Depth (8 or 10 - default is 8)\n"
        "    -n <frames>          Number of frames to capture (default is unlimited)\n"
        "    -M <memlimit>        Maximum queue size in GB (default is 1 GB)\n"
        "    -C <num>             number of card to be used\n"
        "    -A <audio-in>        Audio input:\n"
        "                         1: Analog (RCA)\n"
        "                         2: Embedded audio (HDMI/SDI)\n"
        "    -V <video-in>        Video input:\n"
        "                         1: Composite\n"
        "                         2: Component\n"
        "                         3: HDMI\n"
        "                         4: SDI\n"
        "Capture video and audio to a file. Raw video and audio can be sent to a pipe to avconv or vlc e.g.:\n"
        "\n"
        "    bmdcapture -m 2 -A 1 -V 1 -F nut -f pipe:1\n\n\n"
        );

    exit(status);
}
