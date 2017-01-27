/*
 * Copyright (c) 2011 Dan Dennedy <dan@dennedy.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "mltcontroller.h"
#include <QWidget>
#include <QPalette>
#include <iostream>


MltController::MltController(QObject *parent)
    : QObject (parent)
    , m_profile (0)
    , m_producer (0)
    , m_consumer (0)

{
image = new u_int8_t[1920*1080*2];
frame = NULL;
}

MltController::~MltController ()
{
    close();
    Mlt::Factory::close();
    delete image;
    delete frame;
}

void MltController::init ()
{
    Mlt::Factory::init();
    //m_list = new Mlt::Playlist();
    //m_list = mlt_playlist_init();
}


int MltController::open (const char* url, const char* profile)
{
    int error = 0;

    close ();



   // m_profile = new Mlt::Profile (mlt_profile_load_file("/usr/share/mlt/profiles/hdv_720_25p"));
    m_profile = new Mlt::Profile(profile);
   // fprintf(stderr, "PROFILE HEIGHT = %d\n",m_profile->height());
//m_profile->set_sample_aspect(16,9);
m_profile->set_width(1920);
m_profile->set_height(1080);

    m_producer = new Mlt::Producer(*m_profile,url);

    //m_list->append(*producer);


    if (!m_producer->is_valid ()) {
        // Cleanup on error
        error = 1;
        delete m_producer;
        m_producer = 0;
        delete m_profile;
        m_profile = 0;
       /* delete m_list;
        m_list = 0;*/
    }
    else {
//        if ( !profile )
//            // Automate profile
//            m_profile->from_producer (*m_producer);
#ifdef Q_WS_MAC
        // use SDL for audio, OpenGL for video
        m_consumer = new Mlt::Consumer (*m_profile, "sdl_audio");
#elif defined(Q_WS_WIN)
        // sdl_preview does not work good on Windows
        m_consumer = new Mlt::Consumer (*m_profile, "sdl");
#else
        m_consumer = new Mlt::Consumer (*m_profile, "sdl_preview");
#endif
        if (m_consumer->is_valid ()) {
            // Embed the SDL window in our GUI.
            QWidget* widget = qobject_cast<QWidget*> (parent());
            m_consumer->set ("window_id", (int) widget->winId());

#ifndef Q_WS_WIN
            // Set the background color
            // XXX: Incorrect color on Windows
            //QPalette pal;
            //m_consumer->set ("window_background", pal.color (QPalette::Window).name().toAscii().constData());
#endif
            // Connect the producer to the consumer - tell it to "run" later
            m_consumer->connect (*m_producer);
            //m_consumer->connect(*m_list);
            // Make an event handler for when a frame's image should be displayed
            m_consumer->listen ("consumer-frame-show", this, (mlt_listener) on_frame_show);
            m_consumer->start ();
            //A FINIR PLUS TARD char* info = m_list->Mlt::Playlist::clip_info(m_list->Mlt::Playlist::current_clip()) ;
            //std::cout << info << std::endl;


        }

        else {
            // Cleanup on error
            error = 2;
            delete m_consumer;
            m_consumer = 0;
            delete m_producer;
            m_producer = 0;
            delete m_profile;
            m_profile = 0;
           /* delete m_list;
            m_list = 0;*/
        }
    }
    return error;
}
/*void MltController::createPlaylist()
{
    m_list = new Mlt::Playlist();

}*/

void MltController::close ()
{
    if (m_consumer)
        m_consumer->stop ();
    delete m_consumer;
    m_consumer = 0;
    delete m_producer;
    m_producer = 0;
    delete m_profile;
    m_profile = 0;
}
/*void MltController::playlistplay()
{
    m_list->clip_start(m_list->current_clip());
}*/

void MltController::play ()
{
    if (m_producer)
        m_producer->set_speed (1);
    // If we are paused, then we need to "unlock" sdl_still.
    if (m_consumer)
        m_consumer->set ("refresh", 1);

  /*   m_list->clip_start(m_list->current_clip());
    if (m_list)
            m_list->set_speed(1);
     //if (m_producer)
       //      m_producer->set_speed (1);

     if (m_consumer)
         m_consumer->set ("refresh", 1);*/

}

void MltController::pause ()
{
   if (m_producer)
        m_producer->pause ();
   // m_list->pause();
}

bool MltController::isPlaying()
{
    bool status = true ;
    double speed = 1;
    //double print = m_producer->get_speed();
    //fprintf(stderr,"%f\n",print);
    if (m_producer->get_speed() == speed)
        status = false;
    return status;

}

void MltController::setVolume (double volume)
{
    if (m_consumer)
        m_consumer->set ("volume", volume);
}

void* MltController::getImage (void* frame_ptr)
{
    frame = static_cast<Mlt::Frame*> (frame_ptr);
    int width = 0;
    int height = 0;
    // TODO: change the format if using a pixel shader
    mlt_image_format format = mlt_image_yuv422;

    image = frame->get_image (format, width, height);
    void* pFrame;
    pFrame = (image+1);
    return pFrame;
}

//REVOIR CETTE PARTIE POUR LA GESTION DE L'AUDIO
/*
void MltController::getAudio(void* frame_ptr)
{
    Mlt::Frame* frame = static_cast<Mlt::Frame*>(frame_ptr);
    short int *audio_data;
    mlt_audio_format audioFormat = mlt_audio_s16;
    int frequency = 0;
    int channels = 0;
    int samples = 0;
    audio_data = (short int*)frame->get_audio(audioFormat, frequency, channels, samples);
    std::cout << audio_data << endl;


}*/

void MltController::onWindowResize ()
{
    if (m_consumer)
        // When paused this tells sdl_still to update.
        m_consumer->set ("refresh", 1);
}

// MLT consumer-frame-show event handler
void MltController::on_frame_show (mlt_consumer, void* self, mlt_frame frame_ptr)
{
    MltController* controller = static_cast<MltController*> (self);
    Mlt::Frame* frame = new Mlt::Frame (frame_ptr);
    emit controller->frameReceived (frame, (unsigned) mlt_frame_get_position (frame_ptr));
}

void MltController::setPosition(const char* time){

   // m_list->seek(time);
    m_producer->seek(time);
}

int MltController::getLength(){
    int time;
    time = m_producer->get_length();
   // time = m_list->get_length();
    return time;
}

/*int MltController::nextclip()
{
    int index = m_list->current_clip();

    return index;
}*/
