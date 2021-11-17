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

    Object::updateScene(program, deltaTime, m);
}

