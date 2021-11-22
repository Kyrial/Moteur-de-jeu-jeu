#include "controler.h"

Controler::Controler()
{
    setFocusPolicy( Qt::StrongFocus );
}

Controler::Controler(QWidget *parent) : QOpenGLWidget(parent)
{
    setFocusPolicy( Qt::StrongFocus );
}


void Controler::keyPressEvent(QKeyEvent *event)
{

    qDebug("[Controler] touche appuyé ");
    switch (event->key()) {
 /*   case Qt::Key_Z: // haut
        projection.translate(0.0, 0.2, 0.0);
        break;
    case Qt::Key_Q: // gauche
        projection.translate(-0.2, 0.0, 0.0);
        break;
    case Qt::Key_D: //droite
        projection.translate(0.2, 0.0, 0.0);
        break;
    case Qt::Key_S: // bas
        projection.translate(0.0, -0.2, 0.0);
        break;
    case Qt::Key_A: // descendre
        projection.translate(0.0, 0.0, .2);
        break;
    case Qt::Key_E: // monter
        projection.translate(0.0, 0.0, -0.2);
        break;
    case Qt::Key_C: // tourne terrain
    {

        //lastFrame.start();
        Tourne = Tourne == true ? false: true;
        break;
    }
    case Qt::Key_P: //  tourne terrain
    {
        emit pauseChanged();
        //       gameObj->animate = gameObj->animate == true ? false: true;
        break;
    }*/
    }
    viewChanged(event);
}
