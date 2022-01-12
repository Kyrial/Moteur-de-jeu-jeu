#include "gameobject.h"





/**
 * @brief charge le shader, appelle la methode parent
 * @param deltaTime intervalle de temps
 */
void  GameObject::updateScene( double deltaTime){
    QMatrix4x4 m= chargeMatriceForShader(deltaTime);

    Object::updateScene( deltaTime, m);

    //  foreach (Object* go, enfants) {
    //   qDebug("foreach %i \n",enfants.size());
    //       go->updateScene(program,deltaTime, m);
    //   }
}
void  GameObject::updateScene( double deltaTime, QMatrix4x4 lastM){




    Object::updateScene( deltaTime, lastM);

    //     qDebug("boucle ");
    //   foreach (Object* go, enfants) {
    //  qDebug("foreach %i \n",enfants.size());
    //       go->updateScene(program,deltaTime, m);
}



