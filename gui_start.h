#ifndef GUI_START_H
#define GUI_START_H

#include <QObject>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>

using namespace std;

class gui_start : public QDialog
{
    Q_OBJECT

public:
    gui_start(QWidget* parent = NULL);
    ~gui_start();

    bool isBMD();
    bool isMP();
    void getAssets(int, int, int);


private:
    QComboBox *m_comboFmt;
    QSlider *m_sliderBMD;
    QSlider *m_sliderMP;
    QPushButton *m_startButton;

     int    m_frameDuration;
     int    m_width;
     int    m_height;

     void closeEvent(QCloseEvent *event);

private slots:
    void slot_startPressed();
    void slot_comboChanged(int);
};

#endif // GUI_START_H
