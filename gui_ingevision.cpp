#include "gui_ingevision.h"
#include "colorwheel.h"
#include <QGridLayout>
#include <iostream>

using namespace std;



Vision::Vision(int id)
{
     //   this->setFixedSize(1400, 1400);
        wheel.resize(3);
        mSlider.resize(3);
        mIDsource = id;

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

    // RESET
    QFrame *frame3_bis = new QFrame();
    QPushButton *QPB_reset = new QPushButton(this);
    QPB_reset->setFixedSize(75,75);
    QPB_reset->setText("RESET");
    QBoxLayout *layout3_bis = new QBoxLayout(QBoxLayout::TopToBottom, frame3_bis);
    layout3_bis->addWidget(QPB_reset);

    grid->addWidget(frame3_bis, 0,2,4,4);

    QObject::connect(QPB_reset, SIGNAL(clicked()), this, SLOT(reset()));


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
    for (int i=0; i<3; i++)
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

void Vision::reset()
{
  for(int i; i<3; i++)
  {
  emit save_vision_balance(QColor(255,255,255), i, mIDsource);
  emit save_vision_levels(50, i, mIDsource);
  wheel.at(i)->changeColor(QColor(255,255,255));
  mSlider.at(i)->setValue(50);
  this->update();
}
}

gui_Vision::gui_Vision()
{
QBoxLayout *layout0 = new QBoxLayout(QBoxLayout::TopToBottom, this);

QTabWidget *Tabs = new QTabWidget();

v_1 = new Vision(0);
v_2 = new Vision(1);
v_3 = new Vision(2);
v_4 = new Vision(3);
Tabs->addTab(v_1, "  CAM 1  ");
Tabs->addTab(v_2, "  CAM 2  ");
Tabs->addTab(v_3, "  CAM 3  ");
Tabs->addTab(v_4, "  CAM 4  ");
layout0->addWidget(Tabs);

}


gui_Vision::~gui_Vision()
{

}

