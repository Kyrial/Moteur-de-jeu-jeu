#include "gameobject.h"
/*
GameObject::GameObject()
{
    //t = Transform();
}
*/
/*
GameObject::~GameObject(){

    geo.delete;

        t.destroy();
    enfants.destroy()
      parent->destroy();
}*/
void  GameObject::updateScene(QOpenGLShaderProgram * program, double deltaTime){
    QMatrix4x4 m= chargeMatriceForShader(program, deltaTime);

     Object::updateScene(program, deltaTime, m);

  //  foreach (Object* go, enfants) {
        //   qDebug("foreach %i \n",enfants.size());
 //       go->updateScene(program,deltaTime, m);
 //   }
}
void  GameObject::updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 lastM){
    QMatrix4x4 m= chargeMatriceForShader(program, deltaTime,lastM);



    Object::updateScene(program, deltaTime, m);
    //     qDebug("boucle ");
 //   foreach (Object* go, enfants) {
        //  qDebug("foreach %i \n",enfants.size());
 //       go->updateScene(program,deltaTime, m);
    }



