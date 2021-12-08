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

#include <QOpenGLWidget>
#include <QObject>
#include <QKeyEvent>
class Object: public QObject
{
    Q_OBJECT

    ///ATTRIBUT
public:
    GeometryEngine *geo = new GeometryEngine();
    static bool  animate;
    Object *Monde;
 QVector<QOpenGLShaderProgram*> allShader;
    boolean instanced = false;


protected:
    Transform t = Transform();
    Transform animation = Transform();
    QOpenGLTexture *texture;
    bool ifTexture =false;
    QVector< Object*> enfants= QVector<Object*>();
    Object *parent;
    QMatrix4x4 transf = QMatrix4x4();
    bool canJump = true;
    bool lumiere = false;
    QVector3D dirView = QVector3D(0,1,0);
    QMatrix4x4 projection = QMatrix4x4();
    QSet<int> pressedKeys;
    QOpenGLShaderProgram *shader;
    Transform saveAlltransform = Transform();
    ///Constructeur
public:


    Object();
    Object(Transform tt,Transform anim):t(tt),animation(anim){}


    ///Getter/Setter
    void updateMesh(GeometryEngine *ge){
        geo = ge;
    }
    void setTexture(QOpenGLTexture *txtr){
        if(txtr !=NULL){
            texture = txtr;
            ifTexture =true;
            txtr->setMinificationFilter(QOpenGLTexture::Nearest);
            txtr->setMagnificationFilter(QOpenGLTexture::Linear);
            txtr->setWrapMode(QOpenGLTexture::Repeat);
        }
        else{
            ifTexture =false;
        }}
    void setShader(QOpenGLShaderProgram * shad){
        shader = shad;
    }
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

    void setLumiere(){
        lumiere = true;
    }

    ///Methode
    void calculsInstanced(double deltaTime,QMatrix4x4 m);
protected:
    void chargerTextureForShader(){
        if(ifTexture){
            texture->bind(10);
            shader->setUniformValue("textureScene",10);
        }
        //ifTexture.bind(5);
        shader->setUniformValue("textureSample", ifTexture);

//        glDrawArraysInstanced
    }




    QMatrix4x4 calculMatrice(double deltaTime){
        QMatrix4x4 a;
        if(animate)
            a = t.doAnimation(&animation, deltaTime);
        else
            a = t.doTransformation();
        return a;
    }
    virtual QMatrix4x4 ApplyMatriceForShader( double deltaTime, QMatrix4x4 m){
        QMatrix4x4 anim= calculMatrice( deltaTime);
        shader->setUniformValue("transform_Matrix", m*anim);
        return m*anim;
    }


    virtual QMatrix4x4 chargeMatriceForShader( double deltaTime){

        QMatrix4x4 a =  calculMatrice(deltaTime);

        shader->setUniformValue("transform_Matrix", a);
        return a;
    }

    virtual QMatrix4x4 chargeMatriceForShader( double deltaTime, QMatrix4x4 m){
        QMatrix4x4 anim= calculMatrice(deltaTime);
        shader->setUniformValue("transform_Matrix", m*anim);
        return m*anim;
    }

public:
    virtual void  updateScene( double deltaTime =1, QMatrix4x4 m= QMatrix4x4());
    void findCollision( Object *obj,QMatrix4x4 anim,  QMatrix4x4 t);
    void updateBB();

    Object* getRacine();

    virtual void addShader(QOpenGLShaderProgram * shader);

signals:
   void viewDirChanged(QVector3D vec);
   void emitPosition(QVector3D vec,QMatrix4x4 objM);
   void emitTree(QVector3D);
public slots:
    void controleMouvements(QKeyEvent *event);
    void getDirView(QVector3D dirView);
    void getProjection(QMatrix4x4 proj);
    void controleRotation(QKeyEvent *event);
    void keyPressedChangedMove(QEvent * event);
    void keyPressedChangedRotate(QEvent * event);

    void mapCoordChanged(QVector3D vec,  QMatrix4x4 objM);

    void updateTree(QVector3D vec);

};


#endif // OBJECT_H
