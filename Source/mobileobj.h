#ifndef MOBILEOBJ_H
#define MOBILEOBJ_H

#include <QVector3D>
#include "transform.h"
#include "geometryengine.h"
#include "object.h"

/**
 * @file
 * @brief le fichier contient la classe MobileObject contient les objets subissant la gravité, on peut y trouver le joueur, la boite.
*/

/**
 * @brief la classe MobileObject contient les objets subissant la gravité, on peut y trouver le joueur, la boite.
*/

class MobileObj  : public Object
{
Q_OBJECT

public:

    /**
     * @brief  Constructeur
     */
    MobileObj():Object(){}


       /**
     * @brief constructeur avec parametre
     * @param tt matrice de transformation
     * @param anim matrice d'animation
     */
    MobileObj(Transform tt,Transform anim):Object(tt,anim){}


    float facteurGravite =300;
    float facteurCynetique = 50;


    /**
     * @brief calcul la distance entre deux points
     * @param pt1 point1
     * @param pt2 point2
     * @return retourne la distance entre pt1 et pt2
     */
    float dist2Points(QVector3D pt1, QVector3D pt2){
        return
                pt1.distanceToPoint(pt2);
    };

    /**
     * @brief ajoute la gravité et la perte cinetique en fonction du deltaTemps
     * @param deltaTime intervalle de temps depuis le dernier appel
     */
    void addGravite(double deltaTime){


        float dist = dist2Points(geo->coordLastCollision, Transform::extracteTranslate(t.doTransformation()));
        if(dist >1.1){


        //l'objet subit la gravité
        Transform G = Transform();
        //QVector3D(0,0,-(pow(1.1,(deltaTime/facteurGravite)))/10);
        G.setTranslate(0,0,-(pow(1.1,(deltaTime/facteurGravite)))/10);
        animation = animation.combine_with(G, deltaTime);

        }
        //l'objet est freiner

        animation.setTranslate(pow(0.9,deltaTime/facteurCynetique));
        //animation.setRotation(0.75);
        animation.setTranslate(Transform::convergeZero(animation.getTranslate()));

    }

    /**
     * @brief appel FindCollision afin de rechercher si une collision a lieu
     * @param m matrice dans le repère monde
     */
    void testCollision(QMatrix4x4 m = QMatrix4x4()){
        QMatrix4x4 anim = animation.doTransformation();
        Monde->findCollision(this,anim,m);
    }

    /**
     * @brief updateScene boucle de rendu, appel recursif,
     * appel à addGravite() et testCollision()
     * @param deltaTime intervalle de temps depuis le dernier appel
     */
    void  updateScene( double deltaTime){
        if(animate){
            addGravite( deltaTime);
            testCollision();
        }
        QMatrix4x4 m= chargeMatriceForShader(deltaTime);

        Object::updateScene(deltaTime, m);

    }
    /**
     * @brief updateScene boucle de rendu, appel recursif,
     * appel à addGravite() et testCollision()
     * @param deltaTime intervalle de temps depuis le dernier appel
     * @param lastM matrice de transformation du parent

     */
    void  updateScene(double deltaTime,QMatrix4x4 lastM){
        if(animate){
            addGravite( deltaTime);
            testCollision(lastM);
        }

        Object::updateScene(deltaTime, lastM);

    }
};



#endif // MOBILEOBJ_H
