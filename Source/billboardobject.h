#ifndef BILLBOARDOBJECT_H
#define BILLBOARDOBJECT_H
#include <QVector4D>
#include "object.h"
class billboardObject: public Object
{
public:
    billboardObject():Object(){}
    billboardObject(Transform tt,Transform anim):Object(tt,anim){}
    void updateScene(double deltaTime, QMatrix4x4 m);

    bool UpdatebarreDeVie(double deltaTime);

    float vie = 100;


};

#endif // BILLBOARDOBJECT_H
