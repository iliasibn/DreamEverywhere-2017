#include "gui_ingevision.h"
#include "colorwheel.h"


Vision::Vision()
{
    this->setFixedSize(700, 400);
iris = 1;
    wheel.resize(3);
     mSlider.resize(3);

    // Main parameters

     mSlider.insert(0, new QSlider(Qt::Horizontal, this));
     mSlider.at(0)->setFixedSize(250,100);
     mSlider.at(0)->move(20, 70);
     mSlider.at(0)->setRange(0,100);
     mSlider.at(0)->setValue(50);

    QLabel* mExpoLabel = new QLabel("Exposition", this);
    mExpoLabel->move(30,30);
    mExpoLabel->setFixedWidth(100);

    mSlider.insert(1, new QSlider(Qt::Horizontal, this));
    mSlider.at(1)->setFixedSize(250,100);
    mSlider.at(1)->move(20, 10);
    mSlider.at(1)->setRange(0,100);
    mSlider.at(1)->setValue(50);

    QLabel* mBlackLabel = new QLabel("Black Level", this);
    mBlackLabel->move(30,90);
    mBlackLabel->setFixedWidth(100);

    QLabel* mWhiteLabel = new QLabel("White level", this);
    mWhiteLabel->move(30,150);
    mWhiteLabel->setFixedWidth(100);

    mSlider.insert(2, new QSlider(Qt::Horizontal, this));
    mSlider.at(2)->setFixedSize(250,100);
    mSlider.at(2)->move(20, 130);
    mSlider.at(2)->setRange(0,100);
    mSlider.at(2)->setValue(50);

    for(int i = 0; i<3; i++)
    QObject::connect(mSlider.at(i), SIGNAL(valueChanged(int)), this, SLOT(save_levels(int)));


   /* QLabel* mWhiteCompLabel = new QLabel("White Compression", this);
    mWhiteCompLabel->move(30,210);
    mWhiteCompLabel->setFixedWidth(130);

    QLabel* mKneeLabel = new QLabel("Knee", this);
    mKneeLabel->move(50,240);
    mKneeLabel->setFixedWidth(100);

    mWhiteCompKnee = new QSlider(Qt::Horizontal, this);
    mWhiteCompKnee->setFixedSize(250,100);
    mWhiteCompKnee->move(20, 220);
    mWhiteCompKnee->setRange(0,100);
    mWhiteCompKnee->setValue(100);

    QLabel* mRatioLabel = new QLabel("Ratio", this);
    mRatioLabel->move(50,300);
    mRatioLabel->setFixedWidth(100);

    mWhiteCompRatio = new QSlider(Qt::Horizontal, this);
    mWhiteCompRatio->setFixedSize(250,100);
    mWhiteCompRatio->move(20, 280);
    mWhiteCompRatio->setRange(0,100);
    mWhiteCompRatio->setValue(100); */

    // Combos

    QLabel* mSourceLabel = new QLabel("Source", this);
    mSourceLabel->move(380,30);
    mSourceLabel->setFixedWidth(100);

    mSourceCombo = new QComboBox(this);
    mSourceCombo->move(375, 50);
    mSourceCombo->addItem("IN 1");
    mSourceCombo->addItem("IN 2");
    mSourceCombo->addItem("IN 3");

   /* QLabel* mMonitorLabel = new QLabel("Monitoring", this);
    mMonitorLabel->move(380,110);
    mMonitorLabel->setFixedWidth(100);

    mMonitorCombo = new QComboBox(this);
    mMonitorCombo->move(375, 130);
    mMonitorCombo->addItem("OpenGL output");
    mMonitorCombo->addItem("Source output");
    mMonitorCombo->addItem("Both");*/

  /*  QLabel* mWaveformLabel = new QLabel("Waveform", this);
    mWaveformLabel->move(380, 200);
    mWaveformLabel->setFixedWidth(100);

    mWaveformCombo = new QComboBox(this);
    mWaveformCombo->move(375, 220);
    mWaveformCombo->addItem("OpenGL output");
    mWaveformCombo->addItem("Waveform output");
    mWaveformCombo->addItem("Both");*/

    // Wheels

    QLabel* mShadowLabel = new QLabel("SHADOWS", this);
    mShadowLabel->move(100,200);
    mShadowLabel->setFixedWidth(100);


    wheel.insert(0, new ColorWheel(this));
    wheel.at(0)->setFixedSize(160,160);
    wheel.at(0)->move(68,240);
    wheel.at(0)->show();

    QLabel* mMediumLabel = new QLabel("MEDIUM", this);
    mMediumLabel->move(300,200);
    mMediumLabel->setFixedWidth(100);

    wheel.insert(1, new ColorWheel(this));
    wheel.at(1)->setFixedSize(160,160);
    wheel.at(1)->move(265,240);
    wheel.at(1)->show();

    QLabel* mHighlightsLabel = new QLabel("HIGHLIGHTS", this);
    mHighlightsLabel->move(495,200);
    mHighlightsLabel->setFixedWidth(100);

    wheel.insert(2, new ColorWheel(this));
    wheel.at(2)->setFixedSize(160,160);
    wheel.at(2)->move(470,240);
    wheel.at(2)->show();

    for (int i=0; i<3; i++)
    QObject::connect(wheel.at(i), SIGNAL(colorChanged(QColor)), this, SLOT(save_balances(QColor)));
}

Vision::~Vision()
{

}

void Vision::save_levels(int value)
{
    QSlider *delegsender = qobject_cast <QSlider*> (sender());
    int id;
    for (int i=0; i<mSlider.size();i++)
    {

        if (delegsender == mSlider.at(i))
        {
            id=i;

        }
    }
    iris = (value*2)/100;
}

void Vision::save_balances(QColor color)
{
    ColorWheel *delegsender = qobject_cast <ColorWheel*> (sender());
    int id;
    for (int i=0; i<wheel.size();i++)
    {

        if (delegsender == wheel.at(i))
        {
            id=i;

        }
    }
emit save_vision_balance(color.red(), color.green(), color.blue(), id, 1);
}

