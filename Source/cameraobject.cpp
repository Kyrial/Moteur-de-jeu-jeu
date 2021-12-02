#include "cameraobject.h"

CameraObject::CameraObject()
{

}

void  CameraObject::updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
    //QVector3D translate = Transform::extracteTranslate(m);
    QGenericMatrix<3, 3, float> q =Transform::extracteRotate(m).toGenericMatrix<3,3>();
    QQuaternion rotate =  QQuaternion::fromRotationMatrix(q);
   // QVector3D dirCamera = rotate.toVector4D().toVector3D();

    QMatrix4x4 view = QMatrix4x4();
// view.lookAt((translate+camera_position), QVector3D(0, 0, 0), camera_up);
    view.lookAt((m*camera_position),m*QVector3D(0, 0, 0), rotate*camera_up);
//  view.lookAt((translate+camera_position), translate, camera_up);
    //camera_position + camera_target


    // Set modelview-projection matrix
    program->setUniformValue("camera_matrix", view);
    program->setAttributeValue("viewPosition",m*camera_position);

    emit viewDirChanged(m*QVector3D(0, 0, 0)-(m*camera_position));
    Object::updateScene(program, deltaTime, m);
}





void CameraObject::keyPress(QKeyEvent *event)
{
  /*  qDebug("touche appuyé ");
    switch (event->key()) {
    case Qt::Key_Z: // haut
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

        gameObj->animate = gameObj->animate == true ? false: true;
        break;
    }
    }

    //projection.translate(0.0, 0.0, -1.0) ;
    //update();

    // Save mouse press position
    //  mousePressPosition = QVector2D(e->localPos());*/
}
