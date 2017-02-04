#ifndef GUI_PIP_H
#define GUI_PIP_H

#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QInputDialog>
#include <QMainWindow>
#include <QWidget>

//////////////////////////////////////////////////////////////////
// Classe représentant notre fenêtres et nos paramètres de PIP
//////////////////////////////////////////////////////////////////

class Pipsettings : public QDialog
{
    Q_OBJECT
public:
    Pipsettings(QWidget* parent = NULL);
    ~Pipsettings();
    bool modeencour;
    QLabel *label_taille;
    QLabel *label_x;
    QLabel *label_y;
    QSlider *slider_taille;
    QSlider *slider_x;
    QSlider *slider_y;
    QPushButton *bouton_switch;

private:
    void unif_slider(QSlider*);
    void closeEvent(QCloseEvent* event);

public slots:
    void save_settings_pip(int a);
    void invert_pip();

signals:
    void pip_changes(int, int, int, int);
    void dialogClosed();



};

#endif // GUI_PIP_H
