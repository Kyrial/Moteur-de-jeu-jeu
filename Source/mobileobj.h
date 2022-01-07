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
    float facteurCynetique = 50;



//QVector3D coordLastCollision = QVector3D(999,999,999);
    float dist2Points(QVector3D pt1, QVector3D pt2){
        return
                pt1.distanceToPoint(pt2);
    };


    void addGravite(double deltaTime){
        Transform G = Transform();

        float dist = dist2Points(geo->coordLastCollision, Transform::extracteTranslate(t.doTransformation()));
        if(dist >1.1){


        //l'objet subit la gravité
        G.setTranslate(0,0,-(pow(1.1,(deltaTime/facteurGravite)))/10);
        animation = animation.combine_with(G, deltaTime);

        }
        //l'objet est freiner

        animation.setTranslate(pow(0.9,deltaTime/facteurCynetique));
        //animation.setRotation(0.75);
        animation.setTranslate(Transform::convergeZero(animation.getTranslate()));

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

        Object::updateScene(deltaTime, lastM);

    }
};



#endif // MOBILEOBJ_H
