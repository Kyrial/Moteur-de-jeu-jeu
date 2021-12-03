#include "cameraobject.h"

CameraObject::CameraObject()
{

}

void  CameraObject::updateScene( double deltaTime, QMatrix4x4 m){
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
    for(int i = 0; i< allShader.size(); i++){
        allShader[i]->setUniformValue("camera_matrix", view);
        allShader[i]->setAttributeValue("viewPosition",m*camera_position);
    }
    emit viewDirChanged(m*QVector3D(0, 0, 0)-(m*camera_position));
    Object::updateScene(deltaTime, m);
}






