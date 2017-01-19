
#include "LoopThroughWithOpenGLCompositing.h"

#include <QPushButton>
#include <fstream>                  //Permet de travailler avec fichiers
#include "gui_panel.h"
#include <iostream>
#include <QVBoxLayout>              //Permet d'aligner verticalement des fenêtres
#include <carte_bmd.h>
#include "gui_glwindows.h"
#include <QMessageBox>
#include <strings.h>
#include <sstream> //Header providing string stream classes

using namespace std;

////////////////////////////////// Documentation ////////////////////////////////////////
/// Le moteur initialise tout les modules nécessaires au fonctionnement du mélangeur vidéo
///
/// Voici un schéma ASCII du workflow actuel
/// Tout les concepts sont encapsulés dans des objets Qt
/// Les callbacks entre les modules exploitent le principe de slot et signal délivré par Qt
///
/// ////////////////////////////////////////
///
///
///
///                                                     /////////////////////////////
///                                                     /                           /
///                                                     /   Interface utilisateur   /
///                                                     /           (Qt)            /
///                                                     /                           /
///                                                     /////////////////////////////
///                                                                                |
///                                                                                |
///     /////////////////////////////                                              |
///     /       Objet Carte BMD     /                                              |
///     /                           /                                              |
///     /                           /                                             \|/
///     /                           /   Capture
///     /       // Capture //       / -------------->   /////////////////////////////
///     /         (callback)        /                   /                           /
///     /                           /                   /   Calcul d'effet OpenGL   /
///     /                           /                   /        (GLSL)             /
///     /       // Lecture //       / <--------------   /                           /
///     /                           / |            /|\  /////////////////////////////
///     ///////////////////////////// | Timer(40ms) |
///                                   ---------------
///                                     Rendu et lecture
///
////////////////////////////////////////////////////////////////////////////////////////


LoopThroughWithOpenGLCompositing::LoopThroughWithOpenGLCompositing() : QDialog(),
    pOpenGLComposite(NULL),
    pcarte_bmd(NULL),
    m_nb_entrees(0),
    m_nb_sorties(0),
    m_outHeight(1080),
    m_outWidth(1920),
    m_outFrameduration(40),
    mTotalPlayoutFrames(0)
{

    m_listeLabel = new string[10];
for(int i = 0; i<10; i++){
    m_info_carte[i] = new INFO_CARTE();
    m_dl_in[i]= new DL_IN();
}

mainLayout = new QVBoxLayout();
this->setLayout(mainLayout);

// On crée le timer
m_timeLine = new QTimer(this);
m_timeLine->setInterval(m_outFrameduration);

initialize_engine();

this->move(0,0);
this->setMinimumSize((1920*2)/5+20,1080/5);
this->setMaximumSize((1920*2.3)/2.2+20,1080/2.2);
this->setWindowTitle("Dream Everywhere");
}

void LoopThroughWithOpenGLCompositing::initialize_engine()
{

    int nbr_cartes = 0;

     // on initialise le OpenGLComposite

    pOpenGLComposite = new OpenGLComposite(this, m_outHeight, m_outWidth);
    mainLayout->addWidget(pOpenGLComposite);

    //////////////////////////// On crée les objets représentants les différentes cartes. Cela n'implique pas d'intéragir avec les cartes pour l'instant. on peut donc le faire. ////////////////////////////////////////

    pcarte_bmd = new carte_bmd(this, m_info_carte[0]); // On rentre en paramètres les info de la carte, qui sera pointée dans l'objet carte_bmd
            /*
             *  La on crée tout les objets correspondant toutes les cartes possible et inimaginables
             */

    /////////////////////////////////////////////////////// On initialise les cartes, et on les prépare a être utilisées /////////////////////////////////////////////////////////////////////

    if (pcarte_bmd->check_DL_IO() != 0) //
        {
                string s = "BMD ";
                m_info_carte[0]->mNom = s;
                cout << "Cartes d'entrée/sortie Blackmagic DeckLink détectée.\n" << endl;

                pcarte_bmd->get_patch_DL(panel_patch->access_patch_information(true));

                //On initialise la carte
                if (!pcarte_bmd->Init_DL(pOpenGLComposite->link_outFrame())) // On rentre en paramètres les pointeurs vers les E/S OpenGL
                    exit(0);

                // On incrémente les variables gloables de la classe
                m_info_carte[0]->mNbr_i = pcarte_bmd->access_nbinput();

                nbr_cartes++;

                for(int i; i<m_info_carte[0]->mNbr_i; i++)
                {m_dl_in[i]->plug = true;
                    m_dl_in[i]->mNom = s; }

                // On connecte les entrées de la carte d'acquisition Blackmagic à OpenGL
               QObject::connect(pcarte_bmd, SIGNAL(emitVideoFrame(void**, int)), pOpenGLComposite, SLOT(GLC_bindto(void**, int)), Qt::DirectConnection);

        }


    w = new MainWindow(this);
    string s = "MEDIA ";
    m_info_carte[1]->mNom = s;
    m_info_carte[1]->mNbr_i = 1;
    m_info_carte[1]->mNbr_o = 0;
    m_nb_entrees = m_nb_entrees + m_info_carte[1]->mNbr_i;

        if(!m_dl_in[m_nb_entrees-1]->plug)
        {
            m_dl_in[m_nb_entrees-1]->plug = true;
            m_dl_in[m_nb_entrees-1]->mNom = s;
         }

   nbr_cartes++;
   QObject::connect(w, SIGNAL(showImageSignal(QImage, int)),pOpenGLComposite, SLOT(GLC_bindto_test(QImage, int)), Qt::DirectConnection);


    getListFull();
    debug();
    connect(m_timeLine, SIGNAL(timeout()), this, SLOT(rendertoplayback()), Qt::DirectConnection);

    /////////////////////////////////////////// On connecte l'UI /////////////////////////////////////////////////////////////////////////////

    panel_mel = new Panel(m_nb_entrees, m_listeLabel);


            QObject::connect(panel_mel, SIGNAL(pgm_changed(int)), pOpenGLComposite, SLOT(set_pgm_value(int)));
            QObject::connect(panel_mel, SIGNAL(pvw_changed(int)), pOpenGLComposite, SLOT(set_pvw_value(int)));
            QObject::connect(panel_mel, SIGNAL(signal_alpha_change(int)), pOpenGLComposite, SLOT(alphaChanged(int)));
            QObject::connect(panel_mel, SIGNAL(signal_iris_changed(int)), pOpenGLComposite, SLOT(irisChanged(int)));
            QObject::connect(panel_mel, SIGNAL(wipe_mix_changed(int)), pOpenGLComposite, SLOT(modeChanged(int)));
            QObject::connect(this->m_timeLine, SIGNAL(timeout()), panel_mel, SLOT(slot_lecture()));
            QObject::connect(panel_mel, SIGNAL(signal_maj_pgm(int)), pOpenGLComposite, SLOT(set_pgm_value(int)));
            QObject::connect(panel_mel, SIGNAL(signal_maj_pvw(int)), pOpenGLComposite, SLOT(set_pvw_value(int)));
            QObject::connect(panel_mel, SIGNAL(param_luma(int,bool,int,int, QColor)), pOpenGLComposite, SLOT(set_luma_param(int, bool, int, int, QColor)));
            QObject::connect(panel_mel, SIGNAL(param_pip(int,int,int, int)), pOpenGLComposite, SLOT(set_pip_param(int, int, int, int)));
            QObject::connect(panel_mel, SIGNAL(signal_change_wipe(int)), pOpenGLComposite, SLOT(slot_set_wipe(int)));
            QObject::connect(panel_mel, SIGNAL(closing()),this, SLOT(stop_processing()));
            QObject::connect(panel_mel->bouton_patch, SIGNAL(clicked()), this, SLOT(slot_patch_bmd()));
            // PROV


}

void LoopThroughWithOpenGLCompositing::getListFull()
{
   int k=0;
for (k=0; k<10; k++)
{
    if (m_dl_in[k]->plug)
        m_listeLabel[k]=m_dl_in[k]->mNom;
}
}

void LoopThroughWithOpenGLCompositing::rendertoplayback()
{
    pOpenGLComposite->GLC_rendering();
    if (pcarte_bmd->mBMD_PLAYBACK)
    {if(!pcarte_bmd->writetoDLcard())
    {
        printf("Dream Everywhere : Image perdue\n");
        mTotalPlayoutFrames += 2;
    }
    else
        mTotalPlayoutFrames++;}
}

void LoopThroughWithOpenGLCompositing::start()
{
    m_timeLine->start();
       w->initializeMlt ();
    if (!pcarte_bmd->start_DL())
        exit(0);
    panel_mel->show();
    show();
}

void LoopThroughWithOpenGLCompositing::stop_processing()              // Permet de fermer la fenêtre OpenGlComposite en s'assurant que OpenGl a été coupé
{
this->deleteLater();
}

void LoopThroughWithOpenGLCompositing::slot_patch_bmd()
{  
//////////////////////////////// On coupe le processing ///////////////////////////////////
pcarte_bmd->stop_DL();
m_timeLine->stop();
panel_mel->hide();

//////////////////////////////// On réinitialise les variables ////////////////////////////
m_nb_entrees = m_nb_entrees - m_info_carte[0]->mNbr_i;
m_nb_sorties = m_nb_sorties - m_info_carte[0]->mNbr_o;
m_info_carte[0]->mNbr_i = 0;
m_info_carte[0]->mNbr_o = 0;

panel_patch = new Patch(m_info_carte[0]->mNbr_io, pcarte_bmd->list_DL_IO());
panel_patch->exec();
pcarte_bmd->get_patch_DL(panel_patch->access_patch_information(false));

if(!pcarte_bmd->repatch_DL(m_info_carte[0], pOpenGLComposite->link_outFrame()))
    exit(0);

/* IL FAUT CHANGER L'ID ALLOUEE AU MP */

getListFull();
panel_mel->init_stringlist(m_info_carte[0]->mNbr_i, m_listeLabel);
panel_mel->reset_barres_sources();
m_nb_entrees = m_nb_entrees + m_info_carte[0]->mNbr_i;
m_nb_sorties = m_nb_sorties + m_info_carte[0]->mNbr_o;
debug();
m_timeLine->start();
panel_mel->show();
pcarte_bmd->start_DL();
}

void LoopThroughWithOpenGLCompositing::debug()
{
    /////////////////////////// On fait le bilan sur les entrées sorties ////////////////////////////////////////////////

            if (m_nb_entrees == 0)
            {
                QMessageBox::critical(NULL, "Vérifiez votre configuration.", "Aucune carte disponible pour la lecture. Dream Everywhere va quitter.");
                exit(0);
            }
}

LoopThroughWithOpenGLCompositing::~LoopThroughWithOpenGLCompositing()
{
    if (pcarte_bmd)
        {
        pcarte_bmd->stop_DL();
        pcarte_bmd->deleteLater();
        pcarte_bmd = NULL;
    }
    if (pOpenGLComposite)
        {
        delete pOpenGLComposite;
        pOpenGLComposite = NULL;
    }
    delete *m_info_carte;
    delete m_timeLine;
    this->close();
   exit(0);
}
