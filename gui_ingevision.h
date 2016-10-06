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

class Vision : public QDialog
{
    Q_OBJECT

public:
    Vision();
    ~Vision();

private:
    QVector<QSlider*> mSlider;
    QSlider* mWhiteCompKnee;
    QSlider* mWhiteCompRatio;


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
    void slotSourceChanged(int);

signals:
    void save_vision_balance(QColor, int, int);
    void save_vision_levels(int, int, int);
};

#endif // VISION_H
