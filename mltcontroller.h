#ifndef MLTCONTROLLER_H
#define MLTCONTROLLER_H

#include <QObject>
#include <QImage>
#include <Mlt.h>

class MltController : public QObject
{
    Q_OBJECT
public:
    explicit MltController (QObject *parent = 0);
    ~MltController ();

    /** Initialize the controller.
     */
    void init ();

    /** Open a media file, device, or stream.
     * @param[in] url string of file/device/stream
     * @param[in] profile MLT profile
     * @return 0 if no error. Error code if error.
     */
    int open (const char* url, const char* profile = 0);

    /** Close the media.
     */
    void close ();

    /** Start playback.
     */
    void playlistplay();
    void play ();

    bool isPlaying();

    /** Pause playback.
     */
    void pause ();

    /** Set the SDL audio output level.
     * @param volume audio volume in the range [0..1]
     */
    void setVolume (double volume);

    /** Get a QImage for a MLT frame.
     * This is primarily used within a slot connected to the frameReceived signal.
     * @param frame a mlt_frame
     * @return a QImage containing the RGBA image for the frame
     */
   void* getImage (void* frame);
    void getAudio (void* frame);

    Mlt::Profile* profile () const
        { return m_profile; }

    void setPosition(const char* time);

    int getLength();

    int nextclip();
    void createPlaylist();
private:
    Mlt::Frame* frame;
    u_int8_t* image;
signals:
    /** This method will be called each time a new frame is available.
     * @param frame pass this opaque frame pointer to getImage()
     * @param position the frame number of this frame representing time
     */
    void frameReceived (void* frame, unsigned position);


public slots:
    void onWindowResize ();

private:
    Mlt::Profile* m_profile;
    Mlt::Producer* m_producer;
    Mlt::Consumer* m_consumer;
    //Mlt::Playlist* m_list;

    static void on_frame_show (mlt_consumer, void* self, mlt_frame frame);

};

#endif // MLTCONTROLLER_H
