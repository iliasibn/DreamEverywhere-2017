#include "mltcontroller.h"
#include "visu.h"
#include "mltudpcontroller.h"
#include "mainwindow.h"
#include <QWidget>
#include <QPalette>
#include <iostream>

MltController::MltController(QObject *parent)
    : QObject (parent)
    , m_profile (0)
    , m_producer (0)
    , m_consumer (0)
{
    //On consrtuit la fenetre servant a l'affichage de la source
    widget = new visu();
    widget1 = new visu();



}

MltController::~MltController ()
{
    delete widget;
    close();
    Mlt::Factory::close();
}

void MltController::init ()
{
    Mlt::Factory::init();
}

int MltController::open (const char* url, const char* profile)
{
    int error = 0;

    close ();
    m_profile = new Mlt::Profile (profile);
    m_producer = new Mlt::Producer (*m_profile, url);
    if (!m_producer->is_valid ()) {
        // Cleanup on error
        error = 1;
        delete m_producer;
        m_producer = 0;
        delete m_profile;
        m_profile = 0;
    }
    else {

        // utilisation du consumer sdl
       // m_consumer = new Mlt::Consumer (*m_profile, "sdl");

        //utilisation du consumer xgl pour OpenGL et de sdl_audio pour le son
       m_consumer = new Mlt::Consumer (*m_profile, "sdl_audio");
       m_consumer = new Mlt::Consumer (*m_profile, "sdl");




        if (m_consumer->is_valid ())
        {
            // On connecte la souce à notre fenêtre
            m_consumer->set ("window_id", (int) widget->winId());
            // connection du producer au consumer
             m_consumer->connect (*m_producer);
            // Make an event handler for when a frame's image should be displayed
             m_consumer->listen ("consumer-frame-show", this, (mlt_listener) on_frame_show);
             m_consumer-> start();
        }
        else {
            // on réinitialise tout en cas d'erreur
            error = 2;
            delete m_consumer;
            m_consumer = 0;
            delete m_producer;
            m_producer = 0;
            delete m_profile;
            m_profile = 0;
        }
    }
    return error;
}

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

void MltController::play ()
{
    if (m_producer)
        m_producer->set_speed (1);
    // Si on est en pause, on doit réactiver la lecture du consumer
    if (m_consumer)
        m_consumer->set ("refresh", 1);
}

void MltController::pause ()
{
    if (m_producer)
        m_producer->pause ();

}



QImage MltController::getImage (void* frame_ptr)
{
    Mlt::Frame* frame = static_cast<Mlt::Frame*> (frame_ptr);
    int width = 0;
    int height = 0;
    /*int *width = mlt_properties_get_int( frame_ptr, "width");
    int *height = mlt_properties_get_int( frame_ptr, "height");*/
    mlt_image_format format = mlt_image_glsl_texture;
    const uint8_t* image = frame->get_image (format, width, height);


    //-------------Ajout 2016---------------------------

    /* On veut sélectionner la frame en prendre la partie image puis l'afficher dans un QImage
       Fonction mlt_frame_get_image qui retourne un entier 1 si erreur,
       prends en paramètres une frame, un buffer uint8, un format d'image, longueur, largeur,
       possibilité d'écriture sur l'image*/

    //const uint8_t** image;
    //mlt_frame_get_image(frame_ptr, image, mlt_image_rgb24a, *width, *height)
    delete frame;
    QImage qimage(width, height, QImage::Format_ARGB32);
    memcpy (qimage.scanLine(0), image, width * height * 4);
    //qimage->loadFromData(image);
    return qimage;
}

// Creation d'un gestionnaire et d'un envoie des frames recues et traités dans le consumer
void MltController::on_frame_show (mlt_consumer, void* self, mlt_frame frame_ptr)
{
    MltController* controller = static_cast<MltController*> (self);
    Mlt::Frame* frame = new Mlt::Frame (frame_ptr);
    emit controller->frameReceived (frame, (unsigned) mlt_frame_get_position (frame_ptr));
    uint8_t** buffer;
    mlt_image_format fmt = mlt_image_rgb24a;
    int w = 400;
    int h= 400;
    mlt_frame_get_image(frame_ptr, buffer, &fmt, &w, &h,1);
    //std::cout << buffer << std::endl;
    //convert uint8 -> Byte Array
    //A FAIRE SA MAIRE
    //emit MainWindow::pixmap->loadFromData(*buffer);
}



