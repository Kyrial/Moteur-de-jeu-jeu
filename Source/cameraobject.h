#ifndef CAMERAOBJECT_H
#define CAMERAOBJECT_H

#include "object.h"
#include "QVector3D"

/**
* @file
* @brief le fichier contient la classe  CameraObject qui gère l'objet Caméra
*/

/**
* @brief la classe CameraObject qui gère l'objet Caméra
*/
class CameraObject : public Object
{
    Q_OBJECT
public:
    /**
     * @brief  Constructeur
     */
    CameraObject();
    /**
     * @brief CameraObject constructeur avec parametre
     * @param par le parent
     */
    CameraObject(Object par){
        parent = &par;
    }
//    CameraObject(Object par,QVector<Object*> enf):Object(par,enf){}


    QVector3D rotation_camera  = QVector3D(1.0f, 1.0f, 3.0f);
    QVector3D camera_position = QVector3D(0.0f, 1.2f, 0.5f);
    QVector3D camera_target = QVector3D(0.0f, 0.1f, 1.0f);
    QVector3D camera_up = QVector3D(0.0f, 0.0f, 0.5f);





    /**
    * @brief updateScene met a jour la caméra
    * @param deltaTime
    * @param m
    */
   void  updateScene( double deltaTime =1, QMatrix4x4 m= QMatrix4x4());

   void keyPress(QKeyEvent *event);



 };
#endif // CAMERAOBJECT_H
