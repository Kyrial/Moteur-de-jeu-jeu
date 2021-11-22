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
    Controler(QWidget *parent);

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void pauseChanged();
    void viewChanged(QKeyEvent *event);
};

#endif // CONTROLER_H
