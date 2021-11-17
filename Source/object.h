#ifndef OBJECT_H
#define OBJECT_H
#include "transform.h"
#include "geometryengine.h"
//#include "meshobject.h"
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QVector>
#include <QOpenGLTexture>

class Object
{
    ///ATTRIBUT
public:
    GeometryEngine *geo = new GeometryEngine();
    static bool  animate;
    Object *Monde;
protected:
    Transform t = Transform();
    Transform animation = Transform();
    QOpenGLTexture *texture;
    bool ifTexture =false;
    QVector< Object*> enfants= QVector<Object*>();
    Object *parent;
    QMatrix4x4 transf = QMatrix4x4();




    ///Constructeur
public:
    Object():t(Transform()),parent(nullptr){}
    Object(Transform tt):t(tt),parent(nullptr){}
    Object(Transform tt,Transform anim):t(tt),animation(anim){}
    Object(Transform tt, Object par):t(tt){
        parent = &par;
    }
    Object(Transform tt, Object par, QVector<Object*> enf)
        :t(tt),enfants(enf){
        parent = &par;
    }
    Object( Object par, QVector<Object*> enf)
        :t(Transform()),enfants(enf){
        parent = &par;
    }

   ///Getter/Setter
    void updateMesh(GeometryEngine *ge){
        geo = ge;
    }
    void setTexture(QOpenGLTexture *txtr){
        if(txtr !=NULL){
            texture = txtr;
            ifTexture =true;
        }
        else{
            ifTexture =false;
        }}
    void addChild(Object * enfant){
        enfants.append(enfant);
        enfant->SetParent(this);
    }

    void SetParent(Object * pa){
        parent = pa;
    }


    void setTransf(QMatrix4x4 m){
        transf= m;
    }
    QMatrix4x4 getTransf(){
       return transf;
    }



 ///Methode
protected:
    void chargerTextureForShader(QOpenGLShaderProgram * program){
        if(ifTexture){
            texture->bind(4);
            program->setUniformValue("textureScene", 4);
        }
        //ifTexture.bind(5);
        program->setUniformValue("textureSample", ifTexture);
    }

    QMatrix4x4 calculMatrice(QOpenGLShaderProgram * program, double deltaTime){
        QMatrix4x4 a;
        if(animate)
             a = t.doAnimation(&animation, deltaTime);
        else
             a = t.doTransformation();
        return a;
}
    virtual QMatrix4x4 ApplyMatriceForShader(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
        QMatrix4x4 anim= calculMatrice(program,  deltaTime);
        program->setUniformValue("transform_Matrix", m*anim);
        return m*anim;
    }


    virtual QMatrix4x4 chargeMatriceForShader(QOpenGLShaderProgram * program, double deltaTime){

        QMatrix4x4 a =  calculMatrice(program,  deltaTime);

        program->setUniformValue("transform_Matrix", a);
        return a;
    }

    virtual QMatrix4x4 chargeMatriceForShader(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
        QMatrix4x4 anim= calculMatrice(program,  deltaTime);
        program->setUniformValue("transform_Matrix", m*anim);
        return m*anim;
    }

public:
    virtual void  updateScene(QOpenGLShaderProgram * program, double deltaTime =1, QMatrix4x4 m= QMatrix4x4());
    void findCollision( Object *obj,QMatrix4x4 anim,  QMatrix4x4 t);
    void updateBB();

    Object* getRacine();
};


#endif // OBJECT_H
