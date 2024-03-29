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

/**
 * @file
 * @brief le fichier contient la classe Transform effectue les calculs géométrique afin de générer une matrice de tranformation à partir de scale, translate, rotation
*/
/**
 * @brief la classe Transform Transform effectue les calculs géométrique afin de générer une matrice de tranformation à partir de scale, translate, rotation
*/
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
    /**
     * @brief calcul la transformation a partir de scale, translate, rotate
     * @return
     */
    QMatrix4x4 doTransformation(){
         QMatrix4x4 a= QMatrix4x4 ();
         a = doTranslate(doRotate(doScale(a)));
         return a;
    }

    /**
     * @brief appel combine_with(*anim, deltaTime) et doTransformation() afin de mettre a jour la matrice de transformation en fonction de la matrice d'animation
     * @param anim matrice d'animation
     * @param deltaTime intervalle de temps depuis le dernier appel
     * @return matrice résultante de la combinaison entre this et anim
     */
    QMatrix4x4 doAnimation(Transform* anim, double deltaTime){
        Transform a =combine_with(*anim, deltaTime);
        this->setScale(a.s);
        this->setRotation(a.r);
        this->setTranslate(a.t);
        QMatrix4x4 res = this->doTransformation();
        return res;

    }


    void setTransform(QMatrix4x4 m){
       s = extracteScale(m);
       QGenericMatrix<3, 3, float> q =Transform::extracteRotate(m).toGenericMatrix<3,3>();
       r =  QQuaternion::fromRotationMatrix(q);

       t = extracteTranslate(m);
    }


    void setRotation( QVector3D & v, float f){
        r = QQuaternion::fromAxisAndAngle(v,f);
    }
    void setRotation(float x,float y,float z, float f){
        r = QQuaternion::fromAxisAndAngle(QVector3D(x,y,z),f);

    }
    void setRotation(float facteur){
        borneRotation();
        QVector3D vec = QVector3D();
        float angle = 1;
        r.getAxisAndAngle(&vec,&angle);
        r = QQuaternion::fromAxisAndAngle(vec,angle*facteur);

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
        if (t[2]>0)
            t[2] = t[2]*vit;
    }
    void addTranslate(QVector3D val){
        t = t+val;
    }

    /**
     * @brief extrait la composante translate d'une QMatrix4x4
     * @param m la fameuse matrice QMatrix4x4
     * @return retourne la translation
     */
    static QVector3D extracteTranslate(QMatrix4x4 m){
        return m.column(3).toVector3D();
    }
    /**
     * @brief extrait la composante scale d'une QMatrix4x4
     * @param m la fameuse matrice QMatrix4x4
     * @return retourne la mise à l'echelle
     */
    static QVector3D extracteScale(QMatrix4x4 m){
        return QVector3D(m.column(0).toVector3D().length(),m.column(1).toVector3D().length(),m.column(2).toVector3D().length());
    }

    /**
     * @brief extrait la composante rotate d'une QMatrix4x4
     * @param m la fameuse matrice QMatrix4x4
     * @return retourne la rotation
     */
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

    /**
    * @brief combine deux transformations
    * @param b l'autre transformation
    * @param deltaTime intervalle de temps
    * @return le resultat de la combinaison
    */
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


   //interpolation
   /**
     * @brief interpole deux transformations
     * @param b transformation
     * @param k le poid entre les deux transformations
     * @return le resutltat de l'interpolation
     */
    Transform mix_with(Transform & b, float k){
       Transform result;
       result.s = this->s * k + b.s * (1-k);
      // result.r = this->r mix_with(b, k);
       result.r = QQuaternion::slerp(this->r,b.r,k);
       result.t = this->t * k + b.t * (1-k);
       return result;
    }


    QVector3D getTranslate(){
        return t;
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
    /**
     * @brief fait avencer le joueur
     */
    void forward(){
        t += QVector3D(0.8,0,0);
    }
    /**
     * @brief fait avencer le joueur dans la direction dirView
     * @param dirView direction
     */
    void forward(QVector3D dirView){
        if( (QVector3D(dirView.x(),dirView.y(),0).normalized()).length()<9)
        t += QVector3D(dirView.x(),dirView.y(),0).normalized();
    }

    void backward(){
        t += QVector3D(-0.8,0,0);
    }
    /**
     * @brief fait reculer le joueur dans la direction dirView
     * @param dirView direction
     */
    void backward(QVector3D dirView){
        if( (QVector3D(-dirView.x(),-dirView.y(),0).normalized()).length()<9)
        t += QVector3D(-dirView.x(),-dirView.y(),0).normalized();
    }

    void left(){
        t += QVector3D(0,0.8,0);
    }
    /**
     * @brief fait tourner a gauche le joueur
     */
    void left2(){
       // borneRotation();
         r =  this->r *QQuaternion::fromAxisAndAngle(QVector3D(0,0,1),1);
    }
    void right(){
        t += QVector3D(0,-0.6,0);
    }
    /**
     * @brief fait tourner a droite le joueur
     */
    void right2(){
         //borneRotation();

         r =  this->r *QQuaternion::fromAxisAndAngle(QVector3D(0,0,-1),1);
    }
    /**
     * @brief jump, tout est dit
     */
    void jump(){
        t += QVector3D(0,0,2);
    }

    /**
     * @brief obsolete
     */
    void borneRotation(){
        QVector3D vec = QVector3D();
        float angle = 1;
        r.getAxisAndAngle(&vec,&angle);
        if (angle < 0.01)
            angle = 0.0;
        if (angle > 5)
            angle = 5;

        vec[0] = abs(vec.x())<0.01? 0 : abs(vec.x()) > 100 ? 100 : vec.x();
        vec[1] = abs(vec.y())<0.01? 0 : abs(vec.y()) > 100 ? 100 : vec.y();
        vec[2] = abs(vec.z())<0.01? 0 : abs(vec.z()) > 100 ? 100 : vec.z();
        r = QQuaternion::fromAxisAndAngle(vec,angle);
    }



};
#endif // TRANSFORM_H

