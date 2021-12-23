#include "object.h"


bool Object::animate = false;


Object::Object():t(Transform())
{

}

void Object::addShader(QOpenGLShaderProgram * shad){
    allShader.push_back(shad);
}


/**
 * @brief  Met à jour la scene
 * @details Parcours le graphe de scene, met a jour les bounding box, envoie au shader matrice de transformation, mesh, texture
 * @param deltaTime[in] Intervalle de temps entre la dernière mise a jour de la scene
 * @param lastM[in] matrice de transformation du parent
 */
void  Object::updateScene(double deltaTime, QMatrix4x4 lastM){
    shader->bind();

    QMatrix4x4 m= chargeMatriceForShader(deltaTime,lastM);
    saveAlltransform.setTransform(m);
    emit emitPosition(Transform::extracteTranslate(lastM), m);

    //setTransf(m);
    if(lumiere){
        //QVector3D a = t.extracteTranslate(m);
        for(int i = 0; i< allShader.size(); i++){
            allShader[i]->bind();
            allShader[i]->setUniformValue("lumiere", t.extracteTranslate(m));
        }
    }
    shader->bind();
    chargerTextureForShader();

    if(instanced)
        calculsInstanced(deltaTime, lastM);
    else
        geo->drawCubeGeometry(shader);
    QVector3D newBBMin =QVector3D();
    QVector3D newBBMax =QVector3D();
    bool firstPassage = true;
    int enfant_without_collision = 0;
    foreach (Object* go, enfants) {

        //  qDebug("foreach %i \n",enfants.size());
        go->updateScene(deltaTime, m);

        if(!go->geo->noCollision){
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
        else
            enfant_without_collision++;
    }



    if(enfants.size()<=0+ enfant_without_collision)
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


/**
 * @brief verifie si l'element a subit une collision
 * @param obj[in,out] object recherchant une collision avec un autre objet
 * @param anim
 * @param t
 */
void Object::findCollision( Object* obj, QMatrix4x4 anim, QMatrix4x4 t){

    // QMatrix4x4 m= chargeMatriceForShader(program, deltaTime,lastM);
    if (this/*->parent*/ == obj){
        return;
    }
    foreach (Object* go, enfants){
        if(go->geo->intersect(obj->geo)){
            go->findCollision(obj, anim, t);
        }
    }



    if(!geo->ifNoeudVide() && this != obj &&this->geo->internintersect(obj->geo)){

        if(geo->heightMap){
            bool collision = true;
            QVector3D mesh = QVector3D();
            QVector3D hauteur = geo->findCoordmesh( obj->geo,  t, this->getTransf(),collision, mesh);
            hauteur.setZ(hauteur.z()+hauteur.z()/20);
            if(collision){
                obj->canJump=true;
               // qDebug("COOOOOOOOOLLLLLLLLLLLIIIIIIIIIIIIISSSSSSSIIIIIIIIIIIOOOOOOOOONNNNNNNNNN");
                obj->t.addTranslate(hauteur);
                QVector3D direction =Transform::extracteTranslate(anim);
                //  qDebug("  %f,   %f    %f   \n ", mesh.x(), mesh.y(),(mesh.z()));

                qDebug("Direction Collision %f, %f, %f",direction.x(), direction.y(), direction.z() );

                direction = (this->geo->gestionCollision(obj->geo, direction, mesh))*0.7;

                qDebug("Direction Collision %f, %f, %f \n",direction.x(), direction.y(), direction.z() );
                direction = Transform::convergeZero(direction);
                obj->animation.setTranslate(direction);
                //obj->animation.setTranslate(QVector3D(0,0,0));

            }
        }
        else{
            qDebug("COOOOOOOOOLLLLLLLLLLLIIIIIIIIIIIIISSSSSSSIIIIIIIIIIIOOOOOOOOONNNNNNNNNN");
            QVector3D direction =Transform::extracteTranslate(anim);
            direction = this->geo->gestionCollision(obj->geo, direction);
            obj->animation.setTranslate(direction*0.7);
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
        //animation.forward();
        animation.forward(dirView);
        break;
    }
    case Qt::Key_L: { //  move Backward
        animation.backward(dirView);
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
void Object::controleRotation(QKeyEvent *event){
    qDebug("[Controler] rotation mobile objet ");
    switch (event->key()) {
    case Qt::Key_K: {//move Right
        t.right2();
        break;
    }
    case Qt::Key_M: {//move Left
        t.left2();
        break;
    }
    }
}

void Object::keyPressedChangedMove(QEvent * event){
    if(event->type()==QEvent::KeyPress) {
        pressedKeys += ((QKeyEvent*)event)->key();
    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }

    if( pressedKeys.contains(Qt::Key_O))
        animation.forward(dirView);
    if( pressedKeys.contains(Qt::Key_L))
        animation.backward(dirView);
    if( pressedKeys.contains(Qt::Key_I))
        if (canJump){
            animation.jump();
            canJump=false;
        }


}
void Object::keyPressedChangedRotate(QEvent * event){
    if(event->type()==QEvent::KeyPress) {
        pressedKeys += ((QKeyEvent*)event)->key();
    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }
    if( pressedKeys.contains(Qt::Key_K))
        t.right2();
    if( pressedKeys.contains(Qt::Key_M))
        t.left2();

}

void Object::getDirView(QVector3D newDirView)
{
    dirView =newDirView;
};
void Object::getProjection(QMatrix4x4 proj){
    projection =proj;
}


void Object::calculsInstanced(double deltaTime,QMatrix4x4 m){

    //   QOpenGLBuffer arrayBuf;
    // QVector<QMatrix4x4> modelMatrices;// = QMatrix4x4();
    //bind buffer
    //  arrayBuf.bind();
    //  arrayBuf.allocate(&modelMatrices, instanced * sizeof(QMatrix4x4));
    //  arrayBuf.release();
    QMatrix4x4 courant= calculMatrice(deltaTime);
    //shader->setUniformValue("transform_Matrix", m*anim);

    for(int i=0; i< geo->modelMatrices.size(); i++){
        shader->setUniformValue("transform_Matrix", m*geo->modelMatrices[i]*courant);
        // geo->drawCubeGeometry(shader);
        geo->drawCubeGeometry(shader);
    }
}
void Object::mapCoordChanged(QVector3D coordCharacter, QMatrix4x4 objM){
    emit emitTree(geo->mapCoordChanged(coordCharacter,  objM, saveAlltransform.doTransformation()));
}

void Object::updateTree(QVector3D coordCharacter2){
    float centreX = floor(coordCharacter2[0]);
    float centreY = floor(coordCharacter2[1]);
    if (geo->lastCentre != QVector2D(centreX,centreY)){
        geo->lastCentre = QVector2D(centreX,centreY);
        geo->addInstancedGrass(0.42,QVector3D((centreX)-12,(centreY)-12,0),QVector3D((centreX)+12,(centreY)+12,0) );
    }
}






