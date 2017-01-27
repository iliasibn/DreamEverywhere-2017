#ifndef VISION_H
#define VISION_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include "colorwheel.h"
#include <QDialog>
#include <QColor>
#include <QPushButton>
#include <sstream> //Header providing string stream classes


class Vision : public QWidget
{
    Q_OBJECT

public:
    Vision(int id);
    ~Vision();

private:
    QVector<QSlider*> mSlider;


    QComboBox* mSourceCombo;
    QComboBox* mMonitorCombo;
    QComboBox* mWaveformCombo;

    QCheckBox* mMonitorCheckBox;
    QCheckBox* mWaveformCheckBox;

    QVector<ColorWheel*> wheel;
    int mIDsource;

    QPushButton *QPB_reset;

public slots:
    void save_balances(QColor);
    void save_levels(int);
    void reset();

signals:
    void save_vision_balance(QColor, int, int);
    void save_vision_levels(int, int, int);
};

class gui_Vision : public QDialog
{
    Q_OBJECT

public:
    gui_Vision();
    ~gui_Vision();

    Vision* m_v[10];
private:
        QTabWidget *Tabs;
};

#endif // VISION_H
