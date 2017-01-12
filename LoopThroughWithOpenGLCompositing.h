#ifndef __LOOP_THROUGH_WITH_OPENGL_COMPOSITING_H__
#define __LOOP_THROUGH_WITH_OPENGL_COMPOSITING_H__

#include <QDialog>
#include "OpenGLComposite.h"
#include "gui_panel.h"
#include "carte_bmd.h"
#include "gui_patch.h"
#include "info_carte.h"
#include <QTimer>
#include "colorwheel.h"
#include "gui_ingevision.h"

class OpenGLComposite;

/////////////////////////////////////////////////////////////
// Classe représentant le moteur et l'application mère Qt
/////////////////////////////////////////////////////////////

class LoopThroughWithOpenGLCompositing : public QDialog
{
    Q_OBJECT

public:

	LoopThroughWithOpenGLCompositing();
	~LoopThroughWithOpenGLCompositing();

    /*
     *  Méthode permettant de démarrer les flux
     */
	void start();

    /*
     *  Méthode permettant de vérifier si le nombre d'entrées / sorties est possible
     */
    void debug();

public slots:

    /*
     *  Méthode appelée pour fermer OpenGL lorsque l'on clique sur le bouton "fermer" de la fenêtre du mélangeur
     */
    void stop_processing();

    /*
     *  Méthode qui organise le rendu OpenGL et le rendu sur les cartes
     */
    void rendertoplayback();

    /*
     * Méthode appellée lorsque l'on veut patcher les E/S physiques sur virtuelles (pour l'instant uniquement disponible pour les cartes Blackmagic)
     */
    void slot_patch_bmd();

private:

    /*
     * Initialiser les modules et faire les connexions entre eux
     */
    void initialize_engine();

        OpenGLComposite*							pOpenGLComposite;
        carte_bmd*                                  pcarte_bmd;

        // UI
        Panel *panel_mel;
        Patch *panel_patch;
        Vision *panel_vision;

        // Information sur toutes les cartes utisées
        INFO_CARTE *m_info_carte[10];

        // Nombre total d'entrées et sorties
        int m_nb_entrees;
        int m_nb_sorties;
        QTimer*                                                             m_timeLine;  // utilisé pour le rafraichissement du buffer

        // Parmetres de rendu
        int m_outHeight, m_outWidth, m_outFrameduration, mTotalPlayoutFrames;            // Nombre total de frame lues

        QVBoxLayout *mainLayout;

};

#endif // __LOOP_THROUGH_WITH_OPENGL_COMPOSITING_H__
