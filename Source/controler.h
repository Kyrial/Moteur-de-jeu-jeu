#ifndef CONTROLER_H
#define CONTROLER_H


#include <QOpenGLWidget>
#include <QObject>
#include <QKeyEvent>

class Controler : public QOpenGLWidget
{
    Q_OBJECT

public:
    Controler();

public slots:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void pauseChanged();
    void viewChanged(QKeyEvent *event);
    void moveObject(QKeyEvent *event);
};

#endif // CONTROLER_H
