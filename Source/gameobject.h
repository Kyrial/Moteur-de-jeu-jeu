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

/**
 * @file
 * @brief le fichier contient la classe GameObject contient les objets qui ne subisse pas la gravité, comme le terrain, le soleil, les arbres etc ...
*/

/**
 * @brief la classe GameObject contient les objets qui ne subisse pas la gravité, comme le terrain, le soleil, les arbres etc ...
*/



class GameObject : public Object
{
    Q_OBJECT
    ///ATTRIBUT
private:
   // QVector< GameObject*> enfants= QVector<GameObject*>();
  //  GameObject *parent;


    ///Constructeur
public:
    /**
     * @brief  Constructeur
     */
    GameObject():Object(){}
    /**
     * @brief constructeur avec parametre
     * @param tt matrice de transformation
     * @param anim matrice d'animation
     */
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

    /**
     * @brief boucle de rendu, appel recursif
     * @param deltaTime intervalle de temps depuis le dernier appel
     */
    void   updateScene( double deltaTime);
    /**
     * @brief boucle de rendu, appel au parents
     * @param deltaTime intervalle de temps depuis le dernier appel
     * @param m matrice de transformation du parent
     */
    void  updateScene( double deltaTime, QMatrix4x4 lastM) override;


};


#endif // GAMEOBJECT_H
