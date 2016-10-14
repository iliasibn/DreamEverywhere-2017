#include "gui_ingevision.h"
#include "colorwheel.h"
#include <QGridLayout>
#include <iostream>

using namespace std;

Vision::Vision()
{
     //   this->setFixedSize(1400, 1400);
        wheel.resize(3);
        mSlider.resize(3);
        mIDsource = 0;

    //QFrame *frame0 = new QFrame(this);
    QGridLayout *grid = new QGridLayout(this);

    // EXPOSITIONS

    QFrame *frame1a = new QFrame();
     mSlider.insert(0, new QSlider(Qt::Horizontal, this));
     mSlider.at(0)->setRange(0,100);
     mSlider.at(0)->setValue(50);
    QLabel* mGammaLabel = new QLabel("Gamma", this);
    mGammaLabel->setAlignment(Qt::AlignCenter);
    QBoxLayout *layout1a = new QBoxLayout(QBoxLayout::TopToBottom, frame1a);
    layout1a->addWidget(mGammaLabel);
    layout1a->addWidget(mSlider.at(0));

    QFrame *frame1b = new QFrame();
    mSlider.insert(1, new QSlider(Qt::Horizontal, this));
    mSlider.at(1)->setRange(0,100);
    mSlider.at(1)->setValue(50);
    QLabel* mBlackLabel = new QLabel("Black Level", this);
    mBlackLabel->setAlignment(Qt::AlignCenter);
    QBoxLayout *layout1b = new QBoxLayout(QBoxLayout::TopToBottom, frame1b);
    layout1b->addWidget(mBlackLabel);
    layout1b->addWidget(mSlider.at(1));

    QFrame *frame1c = new QFrame();
    mSlider.insert(2, new QSlider(Qt::Horizontal, this));
    mSlider.at(2)->setRange(0,100);
    mSlider.at(2)->setValue(50);
    QLabel* mWhiteLabel = new QLabel("White level", this);
    mWhiteLabel->setAlignment(Qt::AlignCenter);
    QBoxLayout *layout1c = new QBoxLayout(QBoxLayout::TopToBottom, frame1c);
    layout1c->addWidget(mWhiteLabel);
    layout1c->addWidget(mSlider.at(2));

    grid->addWidget(frame1a, 0,0,1,1);
    grid->addWidget(frame1b, 1,0,1,1);
    grid->addWidget(frame1c, 2,0,1,1);

    for(int i = 0; i<3; i++)
    QObject::connect(mSlider.at(i), SIGNAL(valueChanged(int)), this, SLOT(save_levels(int)));

// COMPRESSIONmSourceCombo->addItem("IN 3");

    QFrame *frame2a = new QFrame();

    QLabel* mWhiteCompLabel = new QLabel("White Compression", this);
    QBoxLayout *layout2a = new QBoxLayout(QBoxLayout::TopToBottom, frame2a);
    layout1c->addSpacing(100);
    layout1c->addWidget(mWhiteCompLabel);

    QFrame *frame2b = new QFrame();
    QLabel* mKneeLabel = new QLabel("Knee", this);
    mKneeLabel->setAlignment(Qt::AlignCenter);
    mSlider.insert(3, new QSlider(Qt::Horizontal, this));
    mSlider.at(3)->setRange(0,100);
    mSlider.at(3)->setValue(100);
    mSlider.at(3)->setDisabled(true);
    QBoxLayout *layout2b = new QBoxLayout(QBoxLayout::TopToBottom, frame2b);
    layout2b->addWidget(mKneeLabel);
    layout2b->addWidget(mSlider.at(3));

    QFrame *frame2c = new QFrame();
    QLabel* mRatioLabel = new QLabel("Ratio", this);
    mRatioLabel->setAlignment(Qt::AlignCenter);

    mSlider.insert(4, new QSlider(Qt::Horizontal, this));
    mSlider.at(4)->setRange(0,100);
    mSlider.at(4)->setValue(100);
    mSlider.at(4)->setDisabled(true);
    QBoxLayout *layout2c = new QBoxLayout(QBoxLayout::TopToBottom, frame2c);
    layout2b->addWidget(mRatioLabel);
    layout2b->addWidget(mSlider.at(4));

    grid->addWidget(frame2a, 3,0,1,1);
    grid->addWidget(frame2b, 4,0,1,1);
    grid->addWidget(frame2c, 5,0,1,1);

    // Combos

    QFrame *frame3 = new QFrame();
    QLabel* mSourceLabel = new QLabel("Source", this);
    mSourceCombo = new QComboBox(this);
    mSourceCombo->addItem("IN 1");
    mSourceCombo->addItem("IN 2");
    mSourceCombo->addItem("IN 3");
    mSourceCombo->addItem("IN 4");
    QBoxLayout *layout3 = new QBoxLayout(QBoxLayout::TopToBottom, frame3);
    layout3->addWidget(mSourceLabel);
    layout3->addWidget(mSourceCombo);
    layout3->setAlignment(Qt::AlignRight);
    grid->addWidget(frame3, 0,1,1,1);

    QObject::connect(mSourceCombo, SIGNAL(activated(int)), this, SLOT(slotSourceChanged(int)));

    // Wheels

    QFrame *frame4a = new QFrame();
    QLabel* mShadowLabel = new QLabel("SHADOWS", frame4a);
    mShadowLabel->setAlignment(Qt::AlignCenter);

    wheel.insert(0, new ColorWheel(frame4a));
    wheel.at(0)->show();
    QBoxLayout *layout4a = new QBoxLayout(QBoxLayout::TopToBottom, frame4a);
    layout4a->addWidget(mShadowLabel);
    layout4a->addWidget(wheel.at(0));

    QFrame *frame4b = new QFrame();
    QLabel* mMediumLabel = new QLabel("MEDIUM", frame4b);
    mMediumLabel->setAlignment(Qt::AlignCenter);
    wheel.insert(1, new ColorWheel(frame4b));
    wheel.at(1)->show();
    QBoxLayout *layout4b = new QBoxLayout(QBoxLayout::TopToBottom, frame4b);
    layout4b->addWidget(mMediumLabel);
    layout4b->addWidget(wheel.at(1));

    QFrame *frame4c = new QFrame();
    QLabel* mHighlightsLabel = new QLabel("HIGHLIGHTS", frame4c);
    mHighlightsLabel->setAlignment(Qt::AlignCenter);

    wheel.insert(2, new ColorWheel(frame4c));
    wheel.at(2)->show();
    QBoxLayout *layout4c = new QBoxLayout(QBoxLayout::TopToBottom, frame4c);
    layout4c->addWidget(mHighlightsLabel);
    layout4c->addWidget(wheel.at(2));

    grid->addWidget(frame4a, 6,0,1,1);
    grid->addWidget(frame4b, 6,1,1,1);
    grid->addWidget(frame4c, 6,2,1,1);

    for (int i=0; i<3; i++)
    QObject::connect(wheel.at(i), SIGNAL(colorChanged(QColor)), this, SLOT(save_balances(QColor)));
    for (int i=0; i<5; i++)
    QObject::connect(mSlider.at(i), SIGNAL(valueChanged(int)), this, SLOT(save_levels(int)));
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
    emit save_vision_levels(value, id, mIDsource);

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
emit save_vision_balance(color, id, mIDsource);
}

void Vision::slotSourceChanged(int a)
{

    mIDsource = a;

}
