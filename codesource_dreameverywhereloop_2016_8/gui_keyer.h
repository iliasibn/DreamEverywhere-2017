#ifndef GUI_KEYER_H
#define GUI_KEYER_H
#include <QDialog>
#include <QSlider>
#include <QComboBox>
#include <QPushButton>
#include <QColorDialog>         //The QColorDialog class provides a dialog widget for specifying colors.
#include <QColor>               //The QColor class provides colors based on RGB, HSV or CMYK values.

/////////////////////////////////////////////////////////////
// Classe représentant la fenêtre et les paramètres de Keying
/////////////////////////////////////////////////////////////

class KeyerSettings: public QDialog
{
    Q_OBJECT
public:
    KeyerSettings(int nb_bmd );
    ~KeyerSettings();
    int current; // La voie que l'on modifie
    void change_current(int, bool, int, int, QColor);
    QComboBox *mCombo_current_source;
    QSlider *mSlider_seuil;
    QSlider *mSlider_tolerance;
    QPushButton *mBouton_mode;
    QComboBox *mCombo_mode;
    QColorDialog *mColor_picker;
    QPushButton *mBouton_color_picking;
    void fermez_les_ecoutilles();


public slots:
    void save_settings(int);        // Emet un signal pour sauvegarder les paramètres de Keying
    void slot_change_mode(int);     // Emet un signal qui indique un changement de mode d'effet de Keying
    void slot_index_changed(int);
    void slot_color_picking();
    void slot_current_color_changed(QColor); // Emet un signal qui envoie la couleur choisie par le picker
signals:
    void keyer_changes(int, bool, int, int, QColor);
    void keyer_change_source(int);
};

#endif // GUI_KEYER_H
