#include "gui_ingevision.h"
#include "colorwheel.h"
#include <QGridLayout>

Vision::Vision()
{
        //this->setFixedSize(1400, 1400);
        iris = 1;
        wheel.resize(3);
        mSlider.resize(3);

    QFrame *frame0 = new QFrame();
    QGridLayout *grid = new QGridLayout(frame0);

    // EXPOSITIONS

    QFrame *frame1a = new QFrame();
     mSlider.insert(0, new QSlider(Qt::Horizontal, this));
     //mSlider.at(0)->setFixedSize(250,100);
    // mSlider.at(0)->move(20, 70);
     mSlider.at(0)->setRange(0,100);
     mSlider.at(0)->setValue(50);
    QLabel* mGammaLabel = new QLabel("Gamma", this);
    //mGammaLabel->move(30,30);
    //mGammaLabel->setFixedWidth(100);
    mGammaLabel->setAlignment(Qt::AlignCenter);
    QBoxLayout *layout1a = new QBoxLayout(QBoxLayout::TopToBottom, frame1a);
    layout1a->addWidget(mGammaLabel);
    layout1a->addWidget(mSlider.at(0));

    QFrame *frame1b = new QFrame();
    mSlider.insert(1, new QSlider(Qt::Horizontal, this));
    //mSlider.at(1)->setFixedSize(250,100);
    //mSlider.at(1)->move(20, 10);
    mSlider.at(1)->setRange(0,100);
    mSlider.at(1)->setValue(50);
    QLabel* mBlackLabel = new QLabel("Black Level", this);
    //mBlackLabel->move(30,90);
    //mBlackLabel->setFixedWidth(100);
    mBlackLabel->setAlignment(Qt::AlignCenter);
    QBoxLayout *layout1b = new QBoxLayout(QBoxLayout::TopToBottom, frame1b);
    layout1b->addWidget(mBlackLabel);
    layout1b->addWidget(mSlider.at(1));

    QFrame *frame1c = new QFrame();
    mSlider.insert(2, new QSlider(Qt::Horizontal, this));
    //mSlider.at(2)->setFixedSize(250,100);
    //mSlider.at(2)->move(20, 130);
    mSlider.at(2)->setRange(0,100);
    mSlider.at(2)->setValue(50);
    QLabel* mWhiteLabel = new QLabel("White level", this);
    //mWhiteLabel->move(30,150);
    //mWhiteLabel->setFixedWidth(100);
    mWhiteLabel->setAlignment(Qt::AlignCenter);
    QBoxLayout *layout1c = new QBoxLayout(QBoxLayout::TopToBottom, frame1c);
    layout1c->addWidget(mWhiteLabel);
    layout1c->addWidget(mSlider.at(2));

    grid->addWidget(frame1a, 0,0,1,1);
    grid->addWidget(frame1b, 1,0,1,1);
    grid->addWidget(frame1c, 2,0,1,1);

    for(int i = 0; i<3; i++)
    QObject::connect(mSlider.at(i), SIGNAL(valueChanged(int)), this, SLOT(save_levels(int)));

// COMPRESSION

    QFrame *frame2a = new QFrame();

    QLabel* mWhiteCompLabel = new QLabel("White Compression", this);
    //mWhiteCompLabel->move(30,260);
    //mWhiteCompLabel->setFixedWidth(130);
    QBoxLayout *layout2a = new QBoxLayout(QBoxLayout::TopToBottom, frame2a);
    layout1c->addWidget(mWhiteCompLabel);

    QFrame *frame2b = new QFrame();
    QLabel* mKneeLabel = new QLabel("Knee", this);
    mKneeLabel->setAlignment(Qt::AlignCenter);
    //mKneeLabel->move(50,290);
    //mKneeLabel->setFixedWidth(100);
    mWhiteCompKnee = new QSlider(Qt::Horizontal, this);
    //mWhiteCompKnee->setFixedSize(250,100);
    //mWhiteCompKnee->move(20, 280);
    mWhiteCompKnee->setRange(0,100);
    mWhiteCompKnee->setValue(100);
    QBoxLayout *layout2b = new QBoxLayout(QBoxLayout::TopToBottom, frame2b);
    layout2b->addWidget(mKneeLabel);
    layout2b->addWidget(mWhiteCompKnee);

    QFrame *frame2c = new QFrame();
    QLabel* mRatioLabel = new QLabel("Ratio", this);
    mRatioLabel->setAlignment(Qt::AlignCenter);

    //mRatioLabel->move(50,350);
    //mRatioLabel->setFixedWidth(100);
    mWhiteCompRatio = new QSlider(Qt::Horizontal, this);
    //mWhiteCompRatio->setFixedSize(250,100);
    //mWhiteCompRatio->move(20, 330);
    mWhiteCompRatio->setRange(0,100);
    mWhiteCompRatio->setValue(100);
    QBoxLayout *layout2c = new QBoxLayout(QBoxLayout::TopToBottom, frame2c);
    layout2b->addWidget(mRatioLabel);
    layout2b->addWidget(mWhiteCompRatio);

    grid->addWidget(frame2a, 3,0,1,1);
    grid->addWidget(frame2b, 4,0,1,1);
    grid->addWidget(frame2c, 5,0,1,1);

    // Combos

    QFrame *frame3 = new QFrame();
    QLabel* mSourceLabel = new QLabel("Source", this);
    //mSourceLabel->setAlignment(Qt::AlignRight);
    //mSourceLabel->move(380,30);
    //mSourceLabel->setFixedWidth(100);
    mSourceCombo = new QComboBox(this);
    //mSourceCombo->move(375, 50);
    mSourceCombo->addItem("IN 1");
    mSourceCombo->addItem("IN 2");
    mSourceCombo->addItem("IN 3");
    QBoxLayout *layout3 = new QBoxLayout(QBoxLayout::TopToBottom, frame3);
    layout3->addWidget(mSourceLabel);
    layout3->addWidget(mSourceCombo);

    grid->addWidget(frame3, 0,1,1,1);

    // Wheels

    QFrame *frame4a = new QFrame();
    QLabel* mShadowLabel = new QLabel("SHADOWS", this);
    mShadowLabel->setAlignment(Qt::AlignCenter);

    //mShadowLabel->move(100,500);
    //mShadowLabel->setFixedWidth(100);
    wheel.insert(0, new ColorWheel(this));
    //wheel.at(0)->setFixedSize(160,160);
    //wheel.at(0)->move(68,540);
    wheel.at(0)->show();
    QBoxLayout *layout4a = new QBoxLayout(QBoxLayout::TopToBottom, frame4a);
    layout4a->addWidget(mShadowLabel);
    layout4a->addWidget(wheel.at(0));

    QFrame *frame4b = new QFrame();
    QLabel* mMediumLabel = new QLabel("MEDIUM", this);
    mMediumLabel->setAlignment(Qt::AlignCenter);

    //mMediumLabel->move(300,500);
    //mMediumLabel->setFixedWidth(100);
    wheel.insert(1, new ColorWheel(this));
    //wheel.at(1)->setFixedSize(160,160);
    //wheel.at(1)->move(265,540);
    wheel.at(1)->show();
    QBoxLayout *layout4b = new QBoxLayout(QBoxLayout::TopToBottom, frame4b);
    layout4b->addWidget(mMediumLabel);
    layout4b->addWidget(wheel.at(1));

    QFrame *frame4c = new QFrame();
    QLabel* mHighlightsLabel = new QLabel("HIGHLIGHTS", this);
    mHighlightsLabel->setAlignment(Qt::AlignCenter);

    //mHighlightsLabel->move(495,500);
    //mHighlightsLabel->setFixedWidth(100);
    wheel.insert(2, new ColorWheel(this));
    //wheel.at(2)->setFixedSize(160,160);
    //wheel.at(2)->move(470,540);
    wheel.at(2)->show();
    QBoxLayout *layout4c = new QBoxLayout(QBoxLayout::TopToBottom, frame4c);
    layout4c->addWidget(mHighlightsLabel);
    layout4c->addWidget(wheel.at(2));


    grid->addWidget(frame4a, 6,0,1,1);
    grid->addWidget(frame4b, 6,1,1,1);
    grid->addWidget(frame4c, 6,2,1,1);

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

