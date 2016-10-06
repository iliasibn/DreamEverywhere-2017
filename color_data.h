#ifndef COLOR_DATA_H
#define COLOR_DATA_H
#include <QColor>

/////////////////////////////////////////////////////////////////////////////
// Structure représentant les valeurs utiles à la correction colorimétrique//
/////////////////////////////////////////////////////////////////////////////

typedef struct {
QColor lift = QColor(255,255,255,255), gamma = QColor(255,255,255,255), gain = QColor(255,255,255,255);
int l_gamma = 50, bl = 50, wl = 50;
int wc_r = 100, wc_k = 100;
bool hdr = false;
} COLOR_DATA;

#endif // COLOR_DATA_H
