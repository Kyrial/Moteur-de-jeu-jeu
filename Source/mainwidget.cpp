/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>
#include <iostream>
#include <math.h>
#include <QElapsedTimer>


bool Tourne = false;

MainWidget::MainWidget(){
    FPS = 40;
}

MainWidget::MainWidget(int fps){
    FPS = fps;
}
void MainWidget::modifFPS(int x){
    FPS = x;
}

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0),
    gameObj(0)
{

}

void MainWidget::initMonde(){
    //Transform tt = Transform();
    gameObj = new GameObject();// tt, geo);
}

Object* MainWidget::addGameObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh=new GeometryEngine(), Transform *anim = new Transform(),QOpenGLTexture *texture=NULL){
    //setTexture(QOpenGLTexture *txtr)
    Object *gameObj2 = new GameObject(*t, *anim);
    gameObj2->updateMesh(mesh);
    gameObj2->setTexture(texture);
    parent->addChild(gameObj2);
    gameObj2->Monde = gameObj;
    gameObj2->setShader(shad);
    return gameObj2;
}
Object* MainWidget::addMobileObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh=new GeometryEngine(), Transform *anim = new Transform(),QOpenGLTexture *texture=NULL ){
    //setTexture(QOpenGLTexture *txtr)
    //MobileObj *Obj2
    Object *mobileobj= new MobileObj(*t, *anim);
    mobileobj->updateMesh(mesh);
    mobileobj->setTexture(texture);
    parent->addChild(mobileobj);
    mobileobj->Monde = gameObj;
    mobileobj->setShader(shad);
    return mobileobj;
}


void MainWidget::scene(){
    gameObj->setShader(allShaders[0]);

    //Instance INIT GAME OBJECT //NOEUD SOLEIL
    Object* NoeudUnivers = addGameObject(allShaders[0],gameObj,new Transform);
   // noeudSoleil->Monde = noeudSoleil;
    //noeudSoleil->setMonde();
    //Fin creation



    //Instance INIT GAME OBJECT // NOEUD TERRE
    Transform *t_NTerre = new Transform;
    t_NTerre->setScale(3,3,3);
    Transform *anim_NTerre = new Transform;
    //anim_NTerre->setRotation(0,0,0.2,1);
    Object* noeudTerre = addGameObject(allShaders[0],NoeudUnivers,t_NTerre,new GeometryEngine, anim_NTerre);
    //Fin creation

    //Instance INIT GAME OBJECT //Terre
    GeometryEngine *geo_Terre = new GeometryEngine;
    geo_Terre->initPlanegeometry();
   // geo_Terre->initMesh(":/Mesh/sphere.off");
    Transform *t_Terre = new Transform;
    //t_Terre->setRotation(-1,0,0,23.44);
    Transform *anim_Terre = new Transform;
    //anim_Terre->setRotation(0,0,1,1);
    Object* Terre = addGameObject(allShaders[0],noeudTerre,t_Terre , geo_Terre,anim_Terre);
    //Fin creation

    //Instance INIT GAME OBJECT // NOEUD LUNE
    Transform *t_NLune = new Transform;
    t_NLune->setScale(0.3,0.3,0.3);
    t_NLune->setTranslate(26,0,30);
    Transform *anim_NLune = new Transform;
    anim_NLune->setRotation(0,0,-5,5);
    Object* noeudLune = addGameObject(&program,noeudTerre,t_NLune,new GeometryEngine, anim_NLune);

    //Fin creation

    //Instance INIT GAME OBJECT //lune
    GeometryEngine *geo_Lune = new GeometryMeshEngine;
    //geo_Lune->initCubeGeometry();
    geo_Lune->initMesh(":/Mesh/sphere.off");
    // geo_Lune->initMesh(":Mesh/space_station.off");
    Transform *t_Lune = new Transform;
    t_Lune->setRotation(1,0,0,6.68);
    Transform *anim_Lune = new Transform;
    anim_Lune->setRotation(0,0,1,0.8);
    Object* Lune = addGameObject(&program,noeudLune,t_Lune , geo_Lune,anim_Lune);
    Lune->setLumiere();
    for(int i =0 ;i < allShaders.size(); i++)
        Lune->addShader(allShaders[i]);
    //Fin creation
    ////////////


    //Instance INIT GAME OBJECT // NOEUD noeud soleil
    Transform *tSoleil = new Transform;
    tSoleil->setScale(1,1,1);
    tSoleil->setTranslate(0,0,10);
    //anim_NTerre->setRotation(0,0,0.2,1);
    Transform *anim_Soleil = new Transform;
    anim_Soleil->setRotation(0,0,1,2.8);
    Object* noeudSoleil = addGameObject(&program,NoeudUnivers,tSoleil,new GeometryEngine,anim_Soleil);
    //Fin creation



    //Instance INIT GAME OBJECT //soleil1
    GeometryEngine *geo_Soleil1 = new GeometryMeshEngine;
    geo_Soleil1->initMesh(":/Mesh/house.off");
    Transform *t_Soleil1 = new Transform;
    //t_Soleil1->setRotation(-1,0,0,6.68);
    t_Soleil1->setTranslate(0,2,0);
    Transform *anim_Soleil1 = new Transform;
//anim_Soleil1->setRotation(1,1,0,1.8);
    addGameObject(allShaders[0],noeudSoleil,t_Soleil1 , geo_Soleil1,anim_Soleil1,new QOpenGLTexture(QImage(":/Texture/textureSoleil.png").mirrored()));
    //Fin creation

    //Instance INIT GAME OBJECT //soleil2
    GeometryEngine *geo_herbe = new GeometryMeshEngine;
    geo_herbe->withNormal = true;
    geo_herbe->initMeshObj(":/Mesh/tree.obj");
    geo_herbe->addInstancedGrass(300);
    Transform *tHerbe = new Transform;
    tHerbe->setScale(0.05,0.05,0.05);
    tHerbe->setRotation(1,0,0,90);
    Object* herbe= addGameObject(allShaders[1],Terre,tHerbe , geo_herbe,new Transform);
    herbe->instanced=true;
    herbe->geo->withNormal = true;

    //Fin creation
    ////////////





/*
    //Instance INIT GAME MOBILE //test
    GeometryEngine *geo_mobile = new GeometryEngine;
    //geo_Soleil->initCubeGeometry();
    geo_mobile->initMesh(":/Mesh/space_station.off");
    Transform *t_mobile = new Transform;
    t_mobile->setScale(0.02,0.02,0.02);
    t_mobile->setTranslate(80,0,25);
    Transform *anim_mobile = new Transform;
    anim_mobile->setTranslate(0,0,0);
    Object* satellite =addMobileObject(Terre,t_mobile , geo_mobile, anim_mobile,
                    new QOpenGLTexture(QImage(":/textureSoleil.png").mirrored())
                    );*/

    //Instance INIT GAME MOBILE //test
   // GeometryEngine *geo_mobile2 = new GeometryEngine;
    //geo_mobile2->initMesh(":/Mesh/space_station.off");
    Transform *t_mobile = new Transform;
    t_mobile->setScale(0.015,0.015,0.015);
  //  t_mobile->setTranslate(80,0,25);
    Object* NoeudSatellite =addMobileObject(&program,Terre,t_mobile ,  new GeometryEngine, new Transform);


    //geo_Soleil->initCubeGeometry();
    GeometryEngine *geo_mobile = new GeometryMeshEngine;
    geo_mobile->initMesh(":/Mesh/space_station.off");
    Transform *anim_mobile = new Transform;
    anim_mobile->setTranslate(0,0,0);
    Object* satellite =addGameObject(&program,NoeudSatellite, new Transform ,   geo_mobile, anim_mobile,
                    new QOpenGLTexture(QImage(":/Texture/textureSoleil.png").mirrored())
                    );


    Object *cameraObj= new CameraObject();
    satellite->addChild(cameraObj);
    cameraObj->setShader(&program);
    for(int i =0 ;i < allShaders.size(); i++)
        cameraObj->addShader(allShaders[i]);



  //  QObject::connect(control, &Controler::moveObject,
 //                    NoeudSatellite, &Object::controleMouvements);
    QObject::connect(cameraObj, &Object::viewDirChanged,
                         NoeudSatellite, &Object::getDirView);
  //  QObject::connect(this, &MainWidget::projectionChanged,
  //                       NoeudSatellite, &Object::getProjection);
  //  QObject::connect(control, &Controler::moveObject,
   //                  satellite, &Object::controleRotation);

    QObject::connect(this, &MainWidget::emitFilter,
                         NoeudSatellite, &Object::keyPressedChangedMove);
    QObject::connect(this, &MainWidget::emitFilter,
                         satellite, &Object::keyPressedChangedRotate);
    //emitFilter
//    void keyPressedChangedMove(QEvent * event);
  //  void keyPressedChangedRotate(QEvent * event);
    //Fin creation


    ///



}




MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;

    delete textureGrass;
    delete textureRock;
    delete textureSnow;
    delete gameObj;

    delete geometries;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]



QVector3D rotation_camera  = QVector3D(1.0f, 1.0f, 1.0f);
QVector3D camera_position = QVector3D(0.0f, 1.0f, 1.0f);
QVector3D camera_target = QVector3D(0.0f, -0.1f, -1.0f);
QVector3D camera_up = QVector3D(0.0f, 0.0f, 0.5f);


//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{


    // Decrease angular speed (friction)
    angularSpeed *= 0.90;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        //update();
    }

    if(Tourne){       deltaTime = lastFrame.elapsed();
        camera_position = QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 2.0f), 0.03*(deltaTime)) * camera_position;
        //update();

    }
//    deltaTime = lastFrame.elapsed();
//    qDebug("deltaTime: %f", deltaTime);
    update();

   // lastFrame.start();

}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.1, 0.1, 0.1, 1);

    initShaders();
    initTextures();

    //! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    // Enable back face culling
    //  glEnable(GL_CULL_FACE);
    //! [2]





    std::cout<<"INIT MONDE"<<std::endl;
    initMonde();
    std::cout<<"INIT SCENE"<<std::endl;

    // gameObj->geo->initPlanegeometry();

    scene();
    this->installEventFilter(this);
    QObject::connect(this, &MainWidget::signalKeyPress,
                         control, &Controler::keyPressEvent);

    QObject::connect(control, &Controler::viewChanged,
                         this, &MainWidget::keyPress);



    absoluteTime.start();
    for(int i=0; i < allShaders.size();i++){
        allShaders[i]->bind();
       allShaders[i]->setUniformValue("lumiere", QVector3D(0,0,5));
}
    // Use QBasicTimer because its faster than QTimer
    timer.start(1000./FPS, this);
}


//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

    allShaders.push_back(&program);
    // Compile vertex shader QOpenGLShaderProgram
    QOpenGLShaderProgram *herbeShader = new QOpenGLShaderProgram;
    if(!herbeShader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/HerbeShader/h_vshader.glsl"))
        close();

    // Compile fragment shader
    if (!herbeShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/HerbeShader/h_fshader.glsl"))
        close();

    // Link shader pipeline
    if (!herbeShader->link())
        close();
    allShaders.push_back(herbeShader);





}


//! [3]

//! [4]
void MainWidget::addAttributeToTexture(QOpenGLTexture* texture){
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::initTextures()
{
    // Load cube.png image
    //    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
    //texture = new QOpenGLTexture(QImage(":/grass.png").mirrored());
    texture = new QOpenGLTexture(QImage(":/Texture/heightmap-1024x1024.png").mirrored());
    // texture = new QOpenGLTexture(QImage(":/Heightmap_Mountain.png").mirrored());
    //texture = new QOpenGLTexture(QImage(":/Heightmap_Rocky.png").mirrored());
    textureGrass =new QOpenGLTexture(QImage(":/Texture/grass.png").mirrored());
    textureRock =new QOpenGLTexture(QImage(":/Texture/rock.png").mirrored());
    textureSnow =new QOpenGLTexture(QImage(":/Texture/snowrocks.png").mirrored());
    textureEau =new QOpenGLTexture(QImage(":/Texture/textureEau.png").mirrored());
    textureBois =new QOpenGLTexture(QImage(":/Texture/textureBois.png").mirrored());



    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);

    addAttributeToTexture(textureGrass);
    addAttributeToTexture(textureRock);
    addAttributeToTexture(textureSnow);
    addAttributeToTexture(textureEau);
    addAttributeToTexture(textureBois);

}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.05, zFar = 80.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]




void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind(0);
    textureGrass->bind(1);
    textureRock->bind(2);
    textureSnow->bind(3);
    textureEau->bind(4);
    textureBois->bind(5);
    //! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -6);
    matrix.rotate(rotation);

    //QMatrix4x4 view;
    //view.lookAt((camera_position), QVector3D(0, 0, 0), camera_up);

    // Set modelview-projection matrix
    for(int i=0; i < allShaders.size();i++){
         allShaders[i]->bind();
        //program.setUniformValue("mvp_matrix",  projection *  matrix /** view*/);
        allShaders[i]->setUniformValue("mvp_matrix",  projection *  matrix /** view*/);
        allShaders[i]->setUniformValue("texture", 0);
        allShaders[i]->setUniformValue("animation", (float)absoluteTime.elapsed());

    }
    allShaders[1]->setUniformValue("textureFeuille", 1); //changer texture
    allShaders[1]->setUniformValue("textureBois", 5);

    // program.setUniformValue("mvp_matrix",  matrix * view * projection);
    //! [6]
    emit projectionChanged(projection*matrix);
    // Use texture unit 0 which contains cube.png

    allShaders[0]->bind();
    program.setUniformValue("textureGrass", 1);
    program.setUniformValue("textureRock", 2);
    program.setUniformValue("textureSnow", 3);
    program.setUniformValue("textureEau", 4);
    // Draw cube geometry
    // geometries->drawCubeGeometry(&program);

    //##############




//    deltaTime =0.99;// lastFrame.elapsed();
    deltaTime = lastFrame.elapsed();

   //qDebug("deltaTime: %f", deltaTime);
    lastFrame.start();

    gameObj->updateScene(deltaTime);
    //gameObj->updateBB();




    //TODO
 //   mobileobj->updateScene(&program,deltaTime);
    //lastFrame.start();
    //geometries->drawCubeGeometry(&program);
}
void MainWidget::keyPressEvent(QKeyEvent *event)
{emit signalKeyPress(event);
}



bool MainWidget::eventFilter(QObject *object, QEvent *event){
    if(event->type()==QEvent::KeyPress || event->type()==QEvent::KeyRelease) {
        qDebug("filtre ");
        emit emitFilter(event);
    }
    return false;
}

void MainWidget::keyPress(QKeyEvent *event)
{
    qDebug("touche appuyé ");
    switch (event->key()) {
    case Qt::Key_Z: // haut
        projection.translate(0.0, 0.2, 0.0);
        break;
    case Qt::Key_Q: // gauche
        projection.translate(-0.2, 0.0, 0.0);
        break;
    case Qt::Key_D: //droite
        projection.translate(0.2, 0.0, 0.0);
        break;
    case Qt::Key_S: // bas
        projection.translate(0.0, -0.2, 0.0);
        break;
    case Qt::Key_A: // descendre
        projection.translate(0.0, 0.0, .2);
        break;
    case Qt::Key_E: // monter
        projection.translate(0.0, 0.0, -0.2);
        break;
    case Qt::Key_C: // tourne terrain
    {

        //lastFrame.start();
        Tourne = Tourne == true ? false: true;
        break;
    }
    case Qt::Key_P: //  tourne terrain
    {

        gameObj->animate = gameObj->animate == true ? false: true;
        break;
    }
    }
    //emit projectionChanged(projection);

    //projection.translate(0.0, 0.0, -1.0) ;
    //update();

    // Save mouse press position
    //  mousePressPosition = QVector2D(e->localPos());
}



void MainWidget::cameraControle(){
        gameObj->animate = gameObj->animate == true ? false: true;
}


