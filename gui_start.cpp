#include "gui_start.h"

gui_start::gui_start(QWidget* parent)
{
resize(500,200);
QGridLayout* main_grid = new QGridLayout(this);

m_comboFmt = new QComboBox(this);
main_grid->addWidget(m_comboFmt,0,0,1,2);

m_sliderBMD = new QSlider(Qt::Horizontal, this);
main_grid->addWidget(m_sliderBMD,1,0,1,1);

m_sliderMP = new QSlider(Qt::Horizontal, this);
main_grid->addWidget(m_sliderMP,2,0,1,1);

m_startButton = new QPushButton("START",this);
main_grid->addWidget(m_startButton,1,1,2,1, Qt::AlignCenter);
}

gui_start::~gui_start(){

}
void gui_start::isBMD(){

}
