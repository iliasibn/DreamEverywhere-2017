#ifndef GUI_START_H
#define GUI_START_H

#include <QObject>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <QWidget>

using namespace std;

class gui_start : public QDialog
{
    Q_OBJECT

public:
    gui_start(/*QWidget* parent = NULL*/);
    ~gui_start();

    void isBMD();

private:
    QComboBox *m_comboFmt;
    QSlider *m_sliderBMD;
    QSlider *m_sliderMP;
    bool    m_condBMD;
    bool    m_condMP;
    QPushButton *m_startButton;

};

#endif // GUI_START_H
