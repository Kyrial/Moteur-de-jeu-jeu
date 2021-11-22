#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "transform.h"
#include "geometryengine.h"
#include "object.h"
//#include "meshobject.h"
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QVector>
#include <QOpenGLTexture>
class GameObject : public Object
{
    Q_OBJECT
    ///ATTRIBUT
private:
   // QVector< GameObject*> enfants= QVector<GameObject*>();
  //  GameObject *parent;


    ///Constructeur
public:
    GameObject():Object(){}
  // GameObject(Transform tt, GameObject par):Object(tt,par){}

   // GameObject(Transform tt):Object(tt){}
    GameObject(Transform tt,Transform anim):Object(tt,anim){}

  /*  GameObject(Transform tt, Object par, QVector<Object*> enf)
        :Object(tt,par,enf){
    }*/




public:
///Getter/Setter
 /*   void addChild(GameObject * enfant){
        enfants.append(enfant);
        enfant->SetParent(this);
    }

    void SetParent(GameObject * pa){
        parent = pa;
    }*/



    ///Methode


    void   updateScene(QOpenGLShaderProgram * program, double deltaTime);
    void  updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 lastM) override;


};


#endif // GAMEOBJECT_H
