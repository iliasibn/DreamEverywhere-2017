#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <QColor>
#include <QInputDialog>
#include <QMainWindow>
#include "gui_keyer.h"
#include "gui_pip.h"
#include "gui_mp.h"
#include <QGridLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <strings.h>
#include <QFrame>

using namespace std;

/////////////////////////////////////////////////////////////
// Classe représentant notre interface de controle
/////////////////////////////////////////////////////////////

class Panel : public QMainWindow
{
    Q_OBJECT

   public:
   Panel(int nb_io, string* mListLabel, QWidget *parent = NULL);
    ~Panel();

   void init_barres_sources();
  void init_stringlist(int, string*);
    void reset_barres_sources();
    QPushButton     *bouton_patch;
    QPushButton     *bouton_colo;
    QPushButton     *bouton_player;
    static void unif_ButtonStyle(QPushButton* _button);
    static void unif_CircleStyle(QPushButton* _button);

private:

    // Pour la structure
    QFrame *frm0;
    QGridLayout *grid;
    QFrame *sub_frm1;
    QFrame *sub_frm2;
    QFrame *sub_frm3;
    QFrame *tr_frm;
    QGridLayout *sub_grd2;
    QVBoxLayout *layout;
    QGridLayout *sub_grd3;
    QGridLayout* sub_grid1;

    QPushButton     *boutons_pvw[10];
    QPushButton     *boutons_wipe[4];
    QPushButton     *boutons_pgm[10];
    QComboBox       *combos_source[10];
    QPushButton     *boutons_chroma[10];
    QPushButton     *boutons_keyer[10];

    QPushButton     *bouton_cut;
    QPushButton     *bouton_reset;
    QPushButton     *bouton_mix;
    QPushButton     *bouton_wipe;
    QPushButton     *bouton_autotrans;
    QPushButton     *bouton_pip;
    QPushButton     *bouton_exit;

    QPushButton     *bouton_volet_rect_vert;
    QSlider         *slider_tbar;
    QSlider         *slider_iris;

    QLabel          *label_autotrans;
    QLineEdit       *line_autotrans;

    KeyerSettings   *fenetre_keyer;
    Pipsettings     *fenetre_pip;

    QLabel          *label_modules;
    QSlider         *m_wipeSlider;
    gui_mp          *fenetre_mp;

    QPushButton     *bouton_gestion_sources;
    int             autotrans_images_restantes;
    int             autotrans_nb_images_total;
    int             tbar_offset;
    bool            depart_alpha;
    int             nb_io;
    int             current_alpha;
    int             NOMBRE_WIPE;

    bool keyer_mode[10];//0 chroma 1 luma
    int keyer_seuil[10];
    int keyer_tolerance[10];
    QColor keyer_color[10];

    QInputDialog *dialog_nouveaunom;
    QLabel *fondtbar;
    QProgressBar *progtbar;
    QLabel *fondiris;
    int id_bouton_nv_nom;

    QStringList *strlst_BMD;


    void init_panel_droite();
    void init_variables();
    void closeEvent(QCloseEvent *event);



public slots:
    void slot_clic_pvw();
    void slot_clic_pgm();
    void slot_clic_wipe();
    void slot_clic_mix();
    void slot_clic_autotrans();
    void slot_clic_cut();
    void slot_clic_pip();
    void slot_lecture();
    void tbar_changed(int nvl_value);
    void slot_config_keyer(QPoint p);
    void slot_config_keyer();
    void slot_save_keyer_settings( int id,bool mode, int seuil, int tolerance, QColor color);
    void slot_save_pip_settings( int taille,int x, int y, int modeencour);
    void slot_keyer_change_source(int id);
    void slot_edit_nom_bouton_pgm(QPoint p);
    void slot_change_nom_bouton();
    void combo_changed(int index);
    void slot_iris_changed(int);
    void slot_change_current_wipe(int);
    void setValueInvert(int);
    void change_pressed_color_pvw();
    void change_pressed_color_pgm();
    void reset_iris();
    void uncheck_all();
    void slot_exit_clicked();




signals:                            //La plupart de ces signaux vont communiquer avec le openGLcomposite
    void pvw_changed(int);
    void pgm_changed(int);
    void wipe_mix_changed(int); // 0 mix 1 wipe
    void signal_maj_pgm(int index);
        void signal_maj_pvw(int index);
    void param_luma(int id,bool mode, int seuil, int tolerance, QColor color);
    void param_pip(int taille, int x, int y, int modeencour);

    void signal_alpha_change(int);
    void signal_depart_change(bool);

    void signal_change_wipe(int);
    void signal_iris_changed(int);
    void closing();

    void signal_exit_clicked();


};



#endif // GUI_PANEL_H
