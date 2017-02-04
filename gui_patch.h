#ifndef GUI_PATCH_H
#define GUI_PATCH_H

#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QInputDialog>
#include <QMainWindow>
#include <QWidget>
#include <string>
#include <iostream>
#include "info_carte.h"

using namespace std;

/////////////////////////////////////////////////////////////
// Classe représentant notre fenêtre de patch Blackmagic
/////////////////////////////////////////////////////////////

class Patch : public QDialog
{
        Q_OBJECT
public:
    Patch(int, string* , QWidget* parent = NULL);
    ~Patch();

    QLabel *mLabel;
    QLabel *mLabel_in;
    QLabel *mLabel_out;
    QSlider *mSwitcher[10];
    QPushButton *mBouton_conf;

    //  Accesseurs
    int* access_patch_information(bool);

private:
    int nb_io;
    int* mPatch_info;
    //int* a;

private slots:
       void patch_done();


};

#endif // GUI_PATCH_H
