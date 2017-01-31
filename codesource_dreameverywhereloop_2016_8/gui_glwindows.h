#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include "GL/glu.h"
#include <QtOpenGL/QGLWidget>

class GLWidget : public QGLWidget {

    Q_OBJECT
public:
    GLWidget(QWidget *parent = NULL);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif  /* _GLWIDGET_H */
