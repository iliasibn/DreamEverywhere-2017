#include "gui_panel.h"
#include <QLabel> //The QLabel widget provides a text or image display.
#include <iostream>
#include <stdio.h>
#include <strings.h>
#include <QValidator> // The QValidator class provides validation of input text.
#include <sstream> //Header providing string stream classes
#include <QComboBox> // The QComboBox widget is a combined button and popup list.
#include <QInputDialog> //The QInputDialog class provides a simple convenience dialog to get a single value from the user.
#include <QProgressBar>

using namespace std;

int FPS = 25;
int NOMBRE_BOUTONS = 10;

Panel::Panel(int nb_bmd, QWidget *parent)   //Constructeur
    : QMainWindow(parent)                   //The QMainWindow class provides a main application window.
{
    this->setFixedSize(1330,300);
    this->setWindowTitle("Dream Everywhere - Panel");
    this->move(0,700);
    nb_io = nb_bmd+1;

    init_stringlist();  //On crée la liste de decklink
    init_variables();   //On initialise le keyer

    init_panel_droite();
    fenetre_keyer = new KeyerSettings(nb_bmd);
    fenetre_pip = new Pipsettings();
    QObject::connect(fenetre_keyer, SIGNAL(keyer_changes(int,bool,int,int, QColor)), this, SLOT(slot_save_keyer_settings(int, bool, int, int, QColor)));
    QObject::connect(fenetre_pip, SIGNAL(pip_changes(int,int, int, int)), this, SLOT(slot_save_pip_settings(int,int, int, int)));
    QObject::connect(fenetre_keyer, SIGNAL(keyer_change_source(int)), this, SLOT(slot_keyer_change_source(int)));

}
void Panel::init_variables()        //On initialise le keyer
{
    autotrans_images_restantes = -1;
    QColor *white = new QColor();
    white->setRgb(255,255,255);
    for (int i=0;i<NOMBRE_BOUTONS;i++)
    {
        keyer_mode[i]=0;
        keyer_seuil[i]=0;
        keyer_tolerance[i]=0;
        keyer_color[i] = *white;

    }
}

void Panel::init_panel_droite()
{


    progtbar = new QProgressBar (this);
    progtbar->setFixedSize(25, 250);
    progtbar->move(838, 20);
    progtbar->setOrientation(Qt::Vertical);
    progtbar->setTextVisible(false);

   /* fondiris = new QLabel(this);
    fondiris->setFixedSize(25,250);
    fondiris->move(1368,20);
    fondiris->setStyleSheet("background : #999999;");

    slider_iris = new QSlider( this);
    slider_iris->setFixedSize(100,250);
    slider_iris->move(1330, 20);
    slider_iris->setRange(0,100);
    slider_iris->setValue(62);
    QObject::connect(slider_iris, SIGNAL(valueChanged(int)), this, SLOT(slot_iris_changed(int)));*/

    slider_tbar = new QSlider( this);
    setStyleSheet("QSlider { width: 40px }"
                  "QSlider::groove:vertical {"
                  "border: 0px solid #999999;"
                  "background: transparent;"
                  "height: 240px;"
                  "margin: 0 0 0 0;}"
                  "QSlider::handle:vertical {"
                  "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                  "border: 1px solid #5c5c5c;"
                  "width: 50px;"
                  "height:10px;"
                  "margin: -5px 0 -5px 0;"
                  "border-radius: 3px;}");

    slider_tbar->setFixedSize(100,250);
    slider_tbar->move(800, 20);
    slider_tbar->setRange(0,100);
    depart_alpha = false; // Par défaut, la t_bar part du bas
    QObject::connect(slider_tbar, SIGNAL(valueChanged(int)), this, SLOT(tbar_changed(int)));

    label_autotrans = new QLabel("FPS Autotrans", this);
    label_autotrans->move(950,20);
    label_autotrans->setFixedWidth(300);

    line_autotrans = new QLineEdit(this);
    line_autotrans->setFixedSize(35,20);
    line_autotrans->move(1060,20);
    QValidator *validator = new QIntValidator(0, 999, this);
    line_autotrans->setValidator(validator);
    line_autotrans->setText("25");

    init_barres_sources();
    bouton_cut = new QPushButton(this);
    bouton_cut->setFixedSize(75,75);
    bouton_cut->setText("CUT");
    bouton_cut->move(930,175);

    bouton_reset = new QPushButton(this);
    bouton_reset->setFixedSize(90,50);
    bouton_reset->setText("RESET IRIS");
    bouton_reset->move(1440,170);
    QObject::connect(bouton_reset, SIGNAL(clicked()), this, SLOT(reset_iris()));

    QObject::connect(bouton_cut, SIGNAL(clicked()), this, SLOT(slot_clic_cut()));

    bouton_mix= new QPushButton(this);
    bouton_mix->setFixedSize(75,75);
    bouton_mix->setText("MIX");
    bouton_mix->move(930,100);
    bouton_mix->setCheckable(1);
    bouton_mix->setChecked(true);
    QObject::connect(bouton_mix, SIGNAL(clicked()), this, SLOT(slot_clic_mix()));

    bouton_autotrans= new QPushButton(this);
    bouton_autotrans->setFixedSize(75,75);
    bouton_autotrans->setText("AUTO\nTRANS");
    bouton_autotrans->move(1005,175);
    QObject::connect(bouton_autotrans, SIGNAL(clicked()), this, SLOT(slot_clic_autotrans()));

    bouton_wipe= new QPushButton(this);
    bouton_wipe->setFixedSize(75,75);
    bouton_wipe->setText("WIPE");
    bouton_wipe->setCheckable(1);
    bouton_wipe->move(1005,100);
    QObject::connect(bouton_wipe, SIGNAL(clicked()), this, SLOT(slot_clic_wipe()));

    bouton_pip= new QPushButton(this);
    bouton_pip->setFixedSize(75,75);
    bouton_pip->setText("PIP");
    bouton_pip->setCheckable(1);
    bouton_pip->move(1130,175);
    QObject::connect(bouton_pip, SIGNAL(clicked()), this, SLOT(slot_clic_pip()));

    bouton_volet_rect_vert = new QPushButton(this);
    bouton_volet_rect_vert->setFixedSize(90,90);
    bouton_volet_rect_vert->move(1100,5);
    bouton_volet_rect_vert->setText("Volet rectvert");
    bouton_volet_rect_vert->setStyleSheet("background:#ffffff;");
    bouton_volet_rect_vert->hide();

    bouton_patch = new QPushButton(this);
    bouton_patch->setFixedSize(90,50);
    bouton_patch->setText("Patch");
    bouton_patch->move(1170,20);

    NOMBRE_WIPE = 2;
    for (int i=0; i<NOMBRE_WIPE; i++)
    {

        boutons_wipe[i] = new QPushButton(this);
        boutons_wipe[i]->setFixedSize(75,75);
        boutons_wipe[i]->setCheckable(true);
        QObject::connect(boutons_wipe[i], SIGNAL(clicked()), this, SLOT(slot_change_current_wipe()));
    }
        boutons_wipe[0]->move(930+4*75,100);
        boutons_wipe[0]->setText("Horizontal");
        boutons_wipe[0]->setChecked(true);

        boutons_wipe[1]->move(930+4*75,175);
        boutons_wipe[1]->setText("Cercle");



}

void Panel::reset_iris ()
{
    slot_iris_changed(62);
    slider_iris->setValue(62);
}

void Panel::slot_iris_changed(int nv_iris)
{
    emit signal_iris_changed(nv_iris);
}

void Panel::init_stringlist()           //On crée une liste qui commence par Black, suivi d'une liste des cartes (du genre 1BMD) et on termine par MIRE
{
    if (strlst_BMD)
        strlst_BMD = NULL;
    strlst_BMD = new QStringList();     //The QStringList class provides a list of strings.
    strlst_BMD->push_back("BLACK");     // la dernière case non attribuée de ton vector vaut maintenant BLACK.

    for (int i=1; i < nb_io ; i++)
    {
        QString *cardname = new QString("IN ");
        std::string s;                  //On construit une classe string
        std::stringstream out;          //On construit une classe stringstream (Pourquoi?)
        out << i;
        s = out.str();
        cardname->push_back(QString::fromStdString(s));
        strlst_BMD->push_back(*cardname);
    }
      strlst_BMD->push_back("MIRE");    // la dernière case non attribuée de ton vector vaut maintenant MIRE.
}

void Panel::init_stringlist(int num)
{
    nb_io = num+1;
    if (strlst_BMD)
        strlst_BMD = NULL;
    strlst_BMD = new QStringList();     //The QStringList class provides a list of strings.
    strlst_BMD->push_back("BLACK");     // la dernière case non attribuée de ton vector vaut maintenant BLACK.

    for (int i=1; i < nb_io ; i++)
    {
        QString *cardname = new QString("IN ");
        std::string s;                  //On construit une classe string
        std::stringstream out;          //On construit une classe stringstream
        out << i;
        s = out.str();
        cardname->push_back(QString::fromStdString(s));
        strlst_BMD->push_back(*cardname);
    }
      strlst_BMD->push_back("MIRE");    // la dernière case non attribuée de ton vector vaut maintenant MIRE.
}

void Panel::slot_change_current_wipe()  //Permet aussi d'activer un ou l'autre bouton wipe, en cliquant dessus
{

    int identifiant;
    QPushButton *bt = qobject_cast <QPushButton*> (sender()); //Bt semble etre l'objet qui a envoyé le signal
    for (int i=0;i<NOMBRE_WIPE;i++)//NOMBRE_WIPE
    {
        if (bt == boutons_wipe[i])
        {
            identifiant = i;
            boutons_wipe[i]->setChecked(true);
            emit signal_change_wipe(identifiant);
        }
        else
            boutons_wipe[i]->setChecked(false);
    }



}

void Panel::combo_changed(int index)
{
    int identifiant;
    QComboBox *combo = qobject_cast <QComboBox*> (sender());
    for (int i=0;i<NOMBRE_BOUTONS;i++)
    {
        if (combo == combos_source[i])
            identifiant = i;

    }

    if (boutons_pgm[identifiant]->isChecked())
    {
        if (index == 0)
            emit signal_maj_pgm(99);
        else if (index == nb_io)
             emit signal_maj_pgm(98);
        else
            emit signal_maj_pgm(index-1);
    }

    if (boutons_pvw[identifiant]->isChecked())
    {
        if (index == 0)
            emit signal_maj_pvw(99);
        else if (index == nb_io)
             emit signal_maj_pvw(98);
        else
            emit signal_maj_pvw(index-1);
    }




}

void Panel::init_barres_sources()
{
    for (int i=0;i<NOMBRE_BOUTONS;i++)
    {

        combos_source[i] = new QComboBox(this);
        combos_source[i]->addItems(*strlst_BMD);
        if (i< nb_io)
            combos_source[i]->setCurrentIndex(i);
        else
            combos_source[i]->setCurrentIndex(0); // 0 = BLACK

        combos_source[i]->setMaximumWidth(75);
        combos_source[i]->setMaximumHeight(20);
        combos_source[i]->move(i*75+25,25);
        QObject::connect(combos_source[i], SIGNAL(currentIndexChanged(int)), this, SLOT(combo_changed(int)) );
        QObject::connect(combos_source[i], SIGNAL(currentIndexChanged(int)), this, SLOT(combo_changed(int)) );

        if (i==0) //Création d'un unique keyer pour le moment
        {
            boutons_keyer[i] = new QPushButton(this);
            //boutons_keyer[i]->setFixedSize(60,20);
            //boutons_keyer[i]->move(i*75+32,50);
            boutons_keyer[i]->setFixedSize(75,75);
            boutons_keyer[i]->move(980+75+75,100);
            boutons_keyer[i]->setText("keyer");
            boutons_keyer[i]->setCheckable(true);
            boutons_keyer[i]->setContextMenuPolicy(Qt::CustomContextMenu);
            QObject::connect(boutons_keyer[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_config_keyer(QPoint))); // Pourquoi ?
            QObject::connect(boutons_keyer[i], SIGNAL(clicked()), this, SLOT(slot_config_keyer()));
        }
        boutons_pgm[i] = new QPushButton(this);
        boutons_pgm[i]->setFixedSize(75,75);
        boutons_pgm[i]->move(i*75+25,100);
        boutons_pgm[i]->setCheckable(true);
        boutons_pgm[i]->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(boutons_pgm[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_edit_nom_bouton_pgm(QPoint))); // Pourquoi ?


        boutons_pvw[i] = new QPushButton(this);
        boutons_pvw[i]->setFixedSize(75,75);
        boutons_pvw[i]->move(i*75+25,175);
        boutons_pvw[i]->setCheckable(true);
        boutons_pvw[i]->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(boutons_pvw[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_edit_nom_bouton_pgm(QPoint))); // Pourquoi ?


        std::stringstream out;
        out << i;
        string nbsource = out.str();
        boutons_pvw[i]->setText( QString(nbsource.c_str()));
        boutons_pgm[i]->setText( QString(nbsource.c_str()));
        connect(boutons_pvw[i], SIGNAL(clicked()), this, SLOT(slot_clic_pvw()));
        connect(boutons_pgm[i], SIGNAL(clicked()), this, SLOT(slot_clic_pgm()));
        connect(boutons_pvw[i], SIGNAL(pressed()), this, SLOT(change_pressed_color_pvw()));
        connect(boutons_pgm[i], SIGNAL(pressed()), this, SLOT(change_pressed_color_pgm()));

    }

boutons_pgm[0]->setChecked(true);
boutons_pvw[0]->setChecked(true);

}

void Panel::reset_barres_sources()
{
for (int i=0;i<10;i++)
{
    combos_source[i]->clear();
    combos_source[i]->addItems(*strlst_BMD);

if (i<nb_io)
    combos_source[i]->setCurrentIndex(i);
else
    combos_source[i]->setCurrentIndex(0);
}}

Panel::~Panel()
{
    fenetre_keyer->fermez_les_ecoutilles();
    fenetre_pip->close();
    this->close();
}
void Panel::slot_keyer_change_source(int id)
{
    fenetre_keyer->change_current(id, keyer_mode[id], keyer_seuil[id], keyer_tolerance[id], keyer_color[id]);
}

void Panel::slot_save_keyer_settings(int id, bool mode, int seuil, int tolerance, QColor color) //On modifie le current (appellé par save_settings)
{
    keyer_mode[id] = mode;
    keyer_seuil[id] = seuil;
    keyer_tolerance[id] = tolerance;
    keyer_color[id] = color;
    emit param_luma( id, mode, seuil, tolerance,color);

}


void Panel::slot_save_pip_settings(int taille, int x, int y, int modeencour)
{
    emit param_pip( taille, x, y, modeencour);


}

void Panel::tbar_changed(int new_value)  //Change le sens du tbar et récupère la valeur
{

    if (depart_alpha == false)
    {
        if (new_value >= 100)

        {
            current_alpha = 0;
            depart_alpha = true;
            slot_clic_cut();
            autotrans_images_restantes = 0;
            bouton_autotrans->setDown(false);
        }else
        {

            current_alpha =  new_value;


        }

    }else
    {
        if (new_value <= 0)
        {
            current_alpha = 0;
            depart_alpha = false;
            slot_clic_cut();
            autotrans_images_restantes = 0;
            bouton_autotrans->setDown(false);
        }else
        {

            current_alpha = 100-new_value;


        }

    }

    if (!depart_alpha)
      {QObject::connect(slider_tbar, SIGNAL(valueChanged(int)), progtbar, SLOT(setValue(int)));
          progtbar->setInvertedAppearance(false); }
      else {QObject::connect(slider_tbar, SIGNAL(valueChanged(int)), this, SLOT(setValueInvert(int)));
          progtbar->setInvertedAppearance(true);}
      emit signal_alpha_change(current_alpha);

}

void Panel::slot_config_keyer(QPoint p)
{

    QPushButton *bouton = qobject_cast <QPushButton*> (sender());
    for (int i=0; i<NOMBRE_BOUTONS; i++)
        if (boutons_keyer[i] == bouton)
            fenetre_keyer->change_current(i, keyer_mode[i], keyer_seuil[i], keyer_tolerance[i], keyer_color[i]);
    emit wipe_mix_changed(2);//luma
                 uncheck_all();
    if (fenetre_keyer->isVisible())
    {
        fenetre_keyer->hide();
        emit wipe_mix_changed(8);//luma
        uncheck_all();
    }else{
        fenetre_keyer->show();
        emit wipe_mix_changed(2);//luma
                     uncheck_all();

    }

}
void Panel::slot_config_keyer()
{
    QPushButton *bouton = qobject_cast <QPushButton*> (sender());
    for (int i=0; i<NOMBRE_BOUTONS; i++)
        if (boutons_keyer[i] == bouton)
            fenetre_keyer->change_current(i, keyer_mode[i], keyer_seuil[i], keyer_tolerance[i], keyer_color[i]);
    if (fenetre_keyer->isVisible())
    {
        fenetre_keyer->hide();
        emit wipe_mix_changed(8);//luma
                uncheck_all();
    }else{
        fenetre_keyer->show();
        emit wipe_mix_changed(2);//luma
                     uncheck_all();

    }

}

void Panel::slot_lecture()
{
    if (autotrans_images_restantes >= 1)
    {
        autotrans_images_restantes--;
        if (autotrans_images_restantes < 1)
        {

            bouton_autotrans->setDown(false);
            if (depart_alpha)
                slider_tbar->setValue(0);
            else
                slider_tbar->setValue(100);

        }else
        {
            float alpha = ((float)autotrans_images_restantes / autotrans_nb_images_total);
            if (depart_alpha)
            {
                alpha = alpha*100 -tbar_offset;
            }else{
                alpha = (100-(alpha*100))+tbar_offset;
            }
            slider_tbar->setValue(alpha);
        }


    }



}

void Panel::slot_edit_nom_bouton_pgm(QPoint p) // Renommer un bouton pgm
{

    QPushButton *bouton_sender = qobject_cast <QPushButton*> (sender());


    for (int i=0;i<NOMBRE_BOUTONS;i++)
    {
        if (bouton_sender == boutons_pgm[i] || bouton_sender == boutons_pvw[i] )
            id_bouton_nv_nom = i;
    }


    dialog_nouveaunom = new QInputDialog();
    dialog_nouveaunom->setLabelText("Entrez le nouveau nom pour cette source");
    dialog_nouveaunom->setOkButtonText("Valider");
    dialog_nouveaunom->setCancelButtonText("Annuler");
    dialog_nouveaunom->setTextValue(bouton_sender->text());
    dialog_nouveaunom->setWindowTitle("Modification d'un bouton");
    dialog_nouveaunom->setModal(true);
    dialog_nouveaunom->show();

    QObject::connect(dialog_nouveaunom, SIGNAL(accepted()), this, SLOT(slot_change_nom_bouton()));

}

void Panel::slot_change_nom_bouton()
{
    QInputDialog *input = qobject_cast <QInputDialog*> (sender());
    if (id_bouton_nv_nom < 0 || id_bouton_nv_nom > NOMBRE_BOUTONS)
    {
        cout << "erreur etrange"<<endl;
    }
    else
    {
        boutons_pvw[id_bouton_nv_nom]->setText(input->textValue());
        boutons_pgm[id_bouton_nv_nom]->setText(input->textValue());
    }
}

void Panel::slot_clic_pvw()
{
    QPushButton *bouton = qobject_cast <QPushButton*> (sender());
    int identifiant;

    for (int i=0 ; i<10;i++)
    {
        if (bouton == boutons_pvw[i])
            identifiant =i;
    }

    for (int i=9; i>=0;i--)
    {
        boutons_pvw[i]->setChecked(0);

    }

  boutons_pvw[identifiant]->setChecked(1);


    if (combos_source[identifiant]->currentIndex() == 0)
        emit pvw_changed(99);
    else if (combos_source[identifiant]->currentIndex() == nb_io)
         emit pvw_changed(98);
    else
        emit pvw_changed(combos_source[identifiant]->currentIndex()-1);


}


void Panel::slot_clic_pgm()
{
    QPushButton *bouton = qobject_cast <QPushButton*> (sender());
    int identifiant;

    for (int i=0 ; i<10;i++)
    {
        if (bouton == boutons_pgm[i])
            identifiant =i;

    }
    for (int i=9; i>=0;i--)
    {
        boutons_pgm[i]->setChecked(0);
    }

    boutons_pgm[identifiant]->setChecked(1);

    if (combos_source[identifiant]->currentIndex() == 0)
        emit pgm_changed(99);
    else if (combos_source[identifiant]->currentIndex() == nb_io)
    {
         emit pgm_changed(98);
     }
         else
        emit pgm_changed(combos_source[identifiant]->currentIndex()-1);

}

void Panel::slot_clic_mix()
{
    if (bouton_mix->isChecked() == true)
    {
    bouton_mix->setChecked(true);
    bouton_wipe->setChecked(false);
    bouton_pip->setChecked(false);
    fenetre_pip->hide();
    emit wipe_mix_changed(1);
    }
    else
    {
        uncheck_all();
        emit wipe_mix_changed(8);
    }
}


void Panel::slot_clic_cut()
{
    int pgm;
    int pvw;
    if (autotrans_images_restantes >0)//Si une autotrans est en cours
    {
        autotrans_images_restantes = 1;
    } // on termine l'autotrans à l'image suivante
    else //autrement on effectue un cut classique
    {
        for (int i=9;i>=0;i--)
        {
            if (boutons_pgm[i]->isChecked() == true)
            {
                pgm = i;

            }

            if (boutons_pvw[i]->isChecked()==true)
            {
                pvw = i;
            }
        }
        boutons_pgm[pgm]->setChecked(false);
        boutons_pvw[pvw]->setChecked(false);

        boutons_pgm[pvw]->setChecked(true);
        boutons_pgm[pvw]->click();
        boutons_pvw[pgm]->setChecked(true);
        boutons_pvw[pgm]->click();


        if (combos_source[pvw]->currentIndex() == 0)
            emit pgm_changed(99);
        else if (combos_source[pvw]->currentIndex() == nb_io)
             emit pgm_changed(98);
        else
            emit pgm_changed(combos_source[pvw]->currentIndex()-1);


        if (combos_source[pgm]->currentIndex() == 0)
            emit pvw_changed(99);
        else if (combos_source[pgm]->currentIndex() == nb_io)
             emit pvw_changed(98);
        else
            emit pvw_changed(combos_source[pgm]->currentIndex()-1);

    }
}


void Panel::slot_clic_wipe()
{
    if (bouton_wipe->isChecked() == true)
    {
    bouton_wipe->setChecked(true);
    bouton_mix->setChecked(false);
    bouton_pip->setChecked(false);
    fenetre_pip->hide();
    emit wipe_mix_changed(4);
    }
    else
    {
        uncheck_all();
        emit wipe_mix_changed(8);
    }
}


void Panel::slot_clic_autotrans()
{
    if (slider_tbar->value() == 0 || slider_tbar->value() == 100)//la transition débute
    {
        autotrans_images_restantes = line_autotrans->text().toInt();
        autotrans_nb_images_total = autotrans_images_restantes;
        tbar_offset = 0;
        bouton_autotrans->setDown(true);
    }
    else// Si une transition était en cours
    {
        bouton_autotrans->setDown(true);//On relance la transition
        if (depart_alpha)
        tbar_offset =100- slider_tbar->value();
        else
            tbar_offset = slider_tbar->value();

        autotrans_images_restantes = line_autotrans->text().toInt();
        autotrans_nb_images_total = autotrans_images_restantes;
    }


}

void Panel::setValueInvert(int a)
{
    progtbar->setValue(100-a);
}

void Panel::change_pressed_color_pvw()
{
    QPushButton *bouton = qobject_cast <QPushButton*> (sender());
     int current;

     for (int i=0 ; i<10;i++)
     {
         if (bouton == boutons_pvw[i])
            current =i;

     }
     for (int i=9; i>=0;i--)
     {

       boutons_pvw[i]->setStyleSheet("color:default;");
     }
     boutons_pvw[current]->setStyleSheet("background-color:#008000;");

}

void Panel::change_pressed_color_pgm()
{
    QPushButton *bouton = qobject_cast <QPushButton*> (sender());
     int current;

     for (int i=0 ; i<10;i++)
     {
         if (bouton == boutons_pgm[i])
             current =i;

     }
     for (int i=9; i>=0;i--)
     {

       boutons_pgm[i]->setStyleSheet("color:default;");
     }
     boutons_pgm[current]->setStyleSheet("background-color:#800000;");

}

void Panel::slot_clic_pip()
{
    if (!fenetre_pip->isVisible())
    {   uncheck_all();
        bouton_pip->setChecked(true);
        emit wipe_mix_changed(9);
        fenetre_pip->show();
    }
    else
    {
      uncheck_all();
      emit wipe_mix_changed(8);
     }
}

void Panel::uncheck_all() // On ferme toutes les fenetres et on actualise le PIP (mode en cour = pvw)
{
    bouton_wipe->setChecked(false);
    bouton_mix->setChecked(false);
    bouton_pip->setChecked(false);
    fenetre_pip->hide();
    fenetre_pip->modeencour = false;
    fenetre_pip->bouton_switch->setChecked(false);
    fenetre_pip->bouton_switch->setStyleSheet("background : #008000;");
    fenetre_pip->save_settings_pip(0);
}

void Panel::closeEvent(QCloseEvent *event) { // Fonction qui permet de gérer la fermeture de la fenêtre OpenGLComposite à la sortie du programme

    emit closing();
}
