#include "object.h"


bool Object::animate = false;


Object::Object():t(Transform())
{

}




void  Object::updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
    setTransf(m);
    if(lumiere){
        QVector3D a = t.extracteTranslate(m);
        program->setUniformValue("lumiere", t.extracteTranslate(m));
    }

    chargerTextureForShader(program);
    geo->drawCubeGeometry(program);
    QVector3D newBBMin =QVector3D();
    QVector3D newBBMax =QVector3D();
    bool firstPassage = true;
    foreach (Object* go, enfants) {
        //  qDebug("foreach %i \n",enfants.size());
        go->updateScene(program,deltaTime, m);


        if( firstPassage){
            newBBMax = go->geo->BBMax;
            newBBMin = go->geo->BBMin;
            //  geo->remplaceBB(go->geo);
            firstPassage = false;
        }

        newBBMin = GeometryEngine::calcBBMin(newBBMin,go->geo->BBMin);
        newBBMax= GeometryEngine::calcBBMax(newBBMax,go->geo->BBMax);
        //geo->ajustBB(go->geo);

    }
    if(enfants.size()==0)
        geo->updateBB(m);
    else{
        if(geo->ifNoeudVide())
            geo->remplaceBB(newBBMin,newBBMax);
        else
        {
            geo->resetBB();
            geo->updateBB(m);
            geo->ajustBB(newBBMin,newBBMax);

        }

    }

}

Object* Object::getRacine(){
    if(parent !=nullptr)
        return parent->getRacine();
    else
        return this;
}



void Object::findCollision( Object* obj, QMatrix4x4 anim, QMatrix4x4 t){
    // QMatrix4x4 m= chargeMatriceForShader(program, deltaTime,lastM);

    foreach (Object* go, enfants){
        if(go->geo->intersect(obj->geo)){
            go->findCollision(obj, anim, t);
        }
    }
    if(!geo->ifNoeudVide() && this != obj &&this->geo->internintersect(obj->geo)){

        if(geo->heightMap){
            bool collision = true;
            QVector3D hauteur = geo->findCoordmesh( obj->geo,  t, this->getTransf(),collision);
            if(collision){
                obj->canJump=true;
                qDebug("COOOOOOOOOLLLLLLLLLLLIIIIIIIIIIIIISSSSSSSIIIIIIIIIIIOOOOOOOOONNNNNNNNNN");
                obj->t.addTranslate(hauteur);
                QVector3D direction =Transform::extracteTranslate(anim);
                direction = (this->geo->gestionCollision(obj->geo, direction))*0.8;
                //direction = Transform::convergeZero(direction);
                obj->animation.setTranslate(direction);
                //obj->animation.setTranslate(QVector3D(0,0,0));

            }
        }
        else{
            qDebug("COOOOOOOOOLLLLLLLLLLLIIIIIIIIIIIIISSSSSSSIIIIIIIIIIIOOOOOOOOONNNNNNNNNN");
            QVector3D direction =Transform::extracteTranslate(anim);
            direction = this->geo->gestionCollision(obj->geo, direction);
            obj->animation.setTranslate(direction*0.8);
            //obj->animation.setTranslate(QVector3D(0,0,0));
            obj->t.addTranslate(geo->recallageCollision(obj->geo));
        }


    }
}


void Object::updateBB(){
    foreach (Object* go, enfants) {
        //  qDebug("foreach %i \n",enfants.size());
        go->updateBB();
        geo->ajustBB(go->geo);
    }
}


void Object::controleMouvements(QKeyEvent *event){
    qDebug("[Controler] move mobile objet ");
    switch (event->key()) {
    case Qt::Key_O:{  // move Forward
       // animation.forward();
        animation.forward( projection * dirView);
        break;
    }
    case Qt::Key_L: { //  move Backward
        animation.backward();
        break;
    }
    case Qt::Key_K: {//move Right
        animation.right();
        break;
    }
    case Qt::Key_M: {//move Left
        animation.left();
        break;
    }
    case Qt::Key_I: {//jump
        if (canJump){
            animation.jump();
            canJump=false;
        }
    }
    }
}
 void Object::getDirView(QVector3D newDirView)
 {
     dirView =newDirView;
 };
 void Object::getProjection(QMatrix4x4 proj){
     projection =proj;
 }



