#ifndef CAMERAOBJECT_H
#define CAMERAOBJECT_H

#include "object.h"
#include "QVector3D"
class CameraObject : public Object
{
public:
    CameraObject();
    CameraObject(Object par){
        parent = &par;
    }
    CameraObject(Object par,QVector<Object*> enf):Object(par,enf){}


    QVector3D rotation_camera  = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D camera_position = QVector3D(0.0f, 1.2f, 1.0f);
    QVector3D camera_target = QVector3D(0.0f, 0.1f, 1.0f);
    QVector3D camera_up = QVector3D(0.0f, 0.0f, 0.5f);


   void rotationScene(double deltaTime){
    camera_position = QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 2.0f), 0.03*(deltaTime)) * camera_position;
}

   void  updateScene(QOpenGLShaderProgram * program, double deltaTime =1, QMatrix4x4 m= QMatrix4x4());

 };
#endif // CAMERAOBJECT_H
