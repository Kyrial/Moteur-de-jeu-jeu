#ifndef MOBILEOBJ_H
#define MOBILEOBJ_H

#include <QVector3D>
#include "transform.h"
#include "geometryengine.h"
#include "object.h"

class MobileObj  : public Object
{
Q_OBJECT

public:

    MobileObj():Object(){}


   // MobileObj(Transform tt):Object(tt){}
    MobileObj(Transform tt,Transform anim):Object(tt,anim){}


    float facteurGravite =300;
    float facteurCynetique = 25;





    void addGravite(double deltaTime){
        Transform G = Transform();


        //l'objet subit la gravité
        G.setTranslate(0,0,-(pow(1.1,(deltaTime/facteurGravite)))/10);
        animation = animation.combine_with(G, deltaTime);
        animation.convergeZero();
        //l'objet est freiner

        animation.setTranslate(pow(0.9,deltaTime/facteurCynetique));

    }

    void testCollision(QMatrix4x4 m = QMatrix4x4()){
        QMatrix4x4 anim = animation.doTransformation();
        Monde->findCollision(this,anim,m);
    }


    void  updateScene( double deltaTime){
        if(animate){
            addGravite( deltaTime);
            testCollision();
        }
        QMatrix4x4 m= chargeMatriceForShader(deltaTime);

        Object::updateScene(deltaTime, m);

    }
    void  updateScene(double deltaTime,QMatrix4x4 lastM){
        if(animate){
            addGravite( deltaTime);
            testCollision(lastM);
        }
        QMatrix4x4 m= chargeMatriceForShader(deltaTime,lastM);

        Object::updateScene(deltaTime, m);

    }



};

#endif // MOBILEOBJ_H
