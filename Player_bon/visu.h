#ifndef VISU_H
#define VISU_H
#include "QObject"
#include "QWidget"

class visu : public QWidget
{

    Q_OBJECT

public:
   visu(QWidget *parent = 0);
     ~visu();
};

#endif // VISU_H
