#include "visu.h"
#include "QObject"
#include "QWidget"

visu::visu(QWidget *parent) : QWidget()
{
    this->setWindowTitle("Player");
    this->setFixedSize(800,500);
    this->show();
}

visu::~visu ()
{

}
