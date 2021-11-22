#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QOpenGLBuffer>

//a faire:
//inversion
//combinaision


class  Transform
{
private:
//Attribut
    QVector3D s; //uniform scale
   QQuaternion r; // rotation
   QVector3D t; // translation





public:
   //constructeur
    Transform():s(QVector3D(1,1,1)),  r(QQuaternion()), t(QVector3D()){}
    Transform(QVector3D sc, QQuaternion ro, QVector3D tr):s(sc), r(ro), t(tr){}

//methode
    QMatrix4x4 doTransformation(){
         QMatrix4x4 a= QMatrix4x4 ();
         a = doTranslate(doRotate(doScale(a)));
         return a;
    }

    QMatrix4x4 doAnimation(Transform* anim, double deltaTime){
        Transform a =combine_with(*anim, deltaTime);
        this->setScale(a.s);
        this->setRotation(a.r);
        this->setTranslate(a.t);
        QMatrix4x4 res = this->doTransformation();
        return res;

    }


    void setRotation( QVector3D & v, float f){
        r = QQuaternion::fromAxisAndAngle(v,f);
    }
    void setRotation(float x,float y,float z, float f){
        r = QQuaternion::fromAxisAndAngle(QVector3D(x,y,z),f);

    }
    void setRotation(QQuaternion q){
        r = q;
    }

    void setScale( QVector3D v){
        s = v;
    }
    void setScale( float x, float y, float z){
        s = QVector3D(x,y,z);
    }

    void setTranslate( QVector3D v){
        t = v;
    }
    void setTranslate( float x, float y, float z){
        t = QVector3D(x,y,z);
    }

    void setTranslate(float vit){
        t[0] = t[0]*vit;
        t[1] = t[1]*vit;
    }
    void addTranslate(QVector3D val){
        t = t+val;
    }

    //Extract is basically the last column of the matrix
    static QVector3D extracteTranslate(QMatrix4x4 m){
        return m.column(3).toVector3D();
    }
    static QVector3D extracteScale(QMatrix4x4 m){
        return QVector3D(m.column(0).toVector3D().length(),m.column(1).toVector3D().length(),m.column(2).toVector3D().length());
    }

    static QMatrix4x4 extracteRotate(QMatrix4x4 m){
       QVector3D vecScale = extracteScale( m);
    QMatrix4x4 r = QMatrix4x4();

    r.setColumn(0,m.column(0).toVector3D()/vecScale.x());
    r.setColumn(1,m.column(1).toVector3D()/vecScale.x());
    r.setColumn(2,m.column(2).toVector3D()/vecScale.x());
r.setColumn(3,QVector4D(.0,.0,.0,1.0));
    return r;
   }
//fromRotationMatrix



    //QVector4D apply( QVector4D p); //p is in affine coords
  //  QVector3D applyToPoint( QVector3D p);
//    QVector3D applyToVector( QVector3D v);
 //   QVector3D applyToVersor( QVector3D v);

   Transform combine_with( Transform & b,double deltaTime){
       Transform result;
       result.s = this->s *b.s; //(b.s*deltaTime) ;

       QVector3D angle = QVector3D();
       float f = 1;
       b.r.getAxisAndAngle(&angle,&f);
       result.r = this->r * QQuaternion::fromAxisAndAngle(angle,f*(0.03*deltaTime));//(b.r*deltaTime);//QQuaternion::slerp(this->r,b.r,0.5);
       result.t = this->t + b.t *deltaTime*0.03;//(b.t*deltaTime);
       return result;
    }


 //   Transform interpolate_with( Transform &t, QVector3D k);

   //interpolation
    Transform mix_with(Transform & b, float k){
       Transform result;
       result.s = this->s * k + b.s * (1-k);
      // result.r = this->r mix_with(b, k);
       result.r = QQuaternion::slerp(this->r,b.r,k);
       result.t = this->t * k + b.t * (1-k);
       return result;
    }







    void convergeZero(){
        if (abs(t[0]) < 0.001)
            t[0]= 0;
        if (abs(t[1]) < 0.001)
            t[1]= 0;
        if (abs(t[2]) < 0.001)
            t[2]= 0;
    }

    static QVector3D convergeZero(QVector3D vec);


   // QVector4D apply( QVector4D p);

    static QMatrix4x4 inverse(QMatrix4x4 const m);

protected:

    QMatrix4x4 doScale(QMatrix4x4 m){
         m.scale(s);
         return m;
    }
    QMatrix4x4 doRotate(QMatrix4x4 m){
         m.rotate(r);
         return m;
    }
    QMatrix4x4 doTranslate(QMatrix4x4 m){
         m.translate(t);
         return m;
    }


public:

    void forward(){
        t += QVector3D(0.1,0,0);
    }
    void backward(){
        t += QVector3D(-0.1,0,0);
    }
    void left(){
        t += QVector3D(0,0.1,0);
    }
    void right(){
        t += QVector3D(0,-01,0);
    }
    void jump(){
        t += QVector3D(0,0,0.1);
    }





};
#endif // TRANSFORM_H

