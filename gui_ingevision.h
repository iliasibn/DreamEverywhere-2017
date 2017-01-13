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

    Vision* v_1;
    Vision* v_2;
    Vision* v_3;
    Vision* v_4;
};

#endif // VISION_H
