#include "controler.h"

Controler::Controler()
{
    setFocusPolicy( Qt::StrongFocus );
}



void Controler::keyPressEvent(QKeyEvent *event)
{

    qDebug("[Controler] touche appuyé ");
    switch (event->key()) {
    case Qt::Key_O:  // move Forward
    case Qt::Key_L:  //  move Backward
    case Qt::Key_K: //move Right
    case Qt::Key_M: //move Left
    case Qt::Key_I: //jump
        emit moveObject(event);
        break;

    default:
        emit viewChanged(event);
    }
}
