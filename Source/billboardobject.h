#ifndef BILLBOARDOBJECT_H
#define BILLBOARDOBJECT_H
#include <QVector4D>
#include "object.h"

/**
 * @file
 * @brief la classe BillboardObject devait etre a la base capable d'afficher des billboard, mais par manque de temps, elle est capable de contenir uniquement la barre de vie.
 */

/**
 * @brief la classe BillboardObject devait etre a la base capable d'afficher des billboard, mais par manque de temps, elle est capable de contenir uniquement la barre de vie.
**/
class billboardObject: public Object
{
public:
    /**
     * @brief  Constructeur
     */
    billboardObject():Object(){}
    /**
     * @brief constructeur avec parametre
     * @param tt matrice de transformation
     * @param anim matrice d'animation
     */
    billboardObject(Transform tt,Transform anim):Object(tt,anim){}
    /**
     * @brief boucle de rendu, appel au parents
     * @param deltaTime intervalle de temps depuis le dernier appel
     * @param m matrice de transformation du parent
     */
    void updateScene(double deltaTime, QMatrix4x4 m);
    /**
     * @brief met a jour la bare de vie
     * @param deltaTime intervalle de temps depuis le dernier appel
     * @return
     */
    bool UpdatebarreDeVie(double deltaTime);

    /**
     * @brief vie point de vie du joueur, se dégrade au fil du temps
     */
    float vie = 100;


};

#endif // BILLBOARDOBJECT_H
