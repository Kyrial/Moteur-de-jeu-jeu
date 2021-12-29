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
    gameObj->setName("racine");
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
Object* MainWidget::addBillboardObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh=new GeometryEngine(), Transform *anim = new Transform(),QOpenGLTexture *texture=NULL ){
    //setTexture(QOpenGLTexture *txtr)
    //MobileObj *Obj2
    Object *billboardobj= new billboardObject(*t, *anim);
    billboardobj->updateMesh(mesh);
    billboardobj->setTexture(texture);
    parent->addChild(billboardobj);
    billboardobj->Monde = gameObj;
    billboardobj->setShader(shad);
    return billboardobj;
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
    noeudTerre->setName("noeudTerre");
    //Fin creation

    //Instance INIT GAME OBJECT //Terre
    GeometryEngine *geo_Terre = new GeometryEngine;
    geo_Terre->setPrecisionTexture(10);
    geo_Terre->initPlanegeometry(-25,-25,25,25);
    // geo_Terre->initMesh(":/Mesh/sphere.off");
    Transform *t_Terre = new Transform;
    //t_Terre->setRotation(-1,0,0,23.44);
    Transform *anim_Terre = new Transform;
    //anim_Terre->setRotation(0,0,1,1);
    Object* Terre = addGameObject(allShaders[0],noeudTerre,t_Terre , geo_Terre,anim_Terre);
    Terre->setName("terre");
    //Fin creation

    // Terre->geo->initPlanegeometry(-1,-1,11,11);






    //Instance INIT GAME OBJECT // NOEUD noeud soleil
    Transform *tSoleil = new Transform;
    tSoleil->setScale(1,1,1);
    tSoleil->setTranslate(0,0,10);
    //anim_NTerre->setRotation(0,0,0.2,1);
    Transform *anim_Soleil = new Transform;
    anim_Soleil->setRotation(0,0,1,2.8);
    Object* noeudSoleil = addGameObject(&program,NoeudUnivers,tSoleil,new GeometryEngine,anim_Soleil);
    //Fin creation



    //Instance INIT GAME OBJECT //arbre
    GeometryEngine *geo_herbe = new GeometryMeshEngine;
    geo_herbe->withNormal = true;
    geo_herbe->setPrecisionTexture(0.20);
    geo_herbe->initMeshObj(":/Mesh/tree.obj");
    geo_herbe->addInstancedGrass();
    Transform *tHerbe = new Transform;
    tHerbe->setScale(0.05,0.05,0.05);
    tHerbe->setRotation(1,0,0,90);
    Object* herbe= addGameObject(allShaders[1],Terre,tHerbe , geo_herbe,new Transform);
    herbe->instanced=true;
    herbe->setName("arbre");

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
    geo_mobile->withNormal = true;
    geo_mobile->setPrecisionTexture(0.5);
    geo_mobile->initMesh(":/Mesh/space_station.off");
    Transform *anim_mobile = new Transform;
    anim_mobile->setTranslate(0,0,0);
    Object* satellite =addGameObject(allShaders[1],NoeudSatellite, new Transform ,   geo_mobile, anim_mobile,
            new QOpenGLTexture(QImage(":/Texture/textureSoleil.png").mirrored()));


    Object *cameraObj= new CameraObject();
    satellite->addChild(cameraObj);
    cameraObj->setShader(&program);
    for(int i =0 ;i < allShaders.size(); i++)
        cameraObj->addShader(allShaders[i]);



    //Instance INIT GAME OBJECT // NOEUD LUNE
    Transform *t_NLune = new Transform;
    //    t_NLune->setScale(0.3,0.3,0.3);
    t_NLune->setScale(15.3,15.3,15.3);
    t_NLune->setTranslate(40,0,35);
    Transform *anim_NLune = new Transform;
    anim_NLune->setRotation(0,0,-2,2);
    //anim_NLune->setRotation(0,1,0,2);
    Object* noeudLune = addGameObject(&program,NoeudSatellite,t_NLune,new GeometryEngine, anim_NLune);
    noeudLune->setName("noeudLune");
    noeudLune->geo->noCollision = true;
    //Fin creation
    //Instance INIT GAME OBJECT //lune
    GeometryEngine *geo_Lune = new GeometryMeshEngine;
    geo_Lune->setPrecisionTexture(0.5);
    //geo_Lune->initCubeGeometry();
    geo_Lune->withNormal = true;
    geo_Lune->initMesh(":/Mesh/sphere.off", false, true, true);
    // geo_Lune->initMesh(":Mesh/space_station.off");
    Transform *t_Lune = new Transform;
    t_Lune->setScale(2,2,2);
    t_Lune->setRotation(1,0,0,6.68);
    Transform *anim_Lune = new Transform;
    anim_Lune->setRotation(0,0,1,0.8);
    Object* Lune = addGameObject(allShaders[1],noeudLune,t_Lune , geo_Lune,anim_Lune,new QOpenGLTexture(QImage(":/Texture/textureSoleil.png").mirrored()));
    Lune->setLumiere();
    Lune->setName("Lune");
    for(int i =0 ;i < allShaders.size(); i++)
        Lune->addShader(allShaders[i]);
    //Fin creation
    ////////////
    // qDebug("test");
    //Instance INIT GAME OBJECT //lune
    GeometryEngine *geo_ciel = new GeometryMeshEngine;
    //geo_Lune->initCubeGeometry();
    geo_ciel->setPrecisionTexture(0.20);
    geo_ciel->withNormal = true;
    geo_ciel->initMesh(":/Mesh/sphere.off", false,true,false);
    //qDebug("test");
    // geo_Lune->initMesh(":Mesh/space_station.off");
    Transform *t_Ciel = new Transform;
    t_Ciel->setScale(2800,2800,2800);
    t_Ciel->setRotation(1,0,0,90);
    Transform *anim_Ciel = new Transform;
    // anim_Ciel->setRotation(0,0,1,0.8);
    Object* Ciel = addGameObject(allShaders[1],NoeudSatellite,t_Ciel , geo_ciel,anim_Ciel,new QOpenGLTexture(QImage(":/Texture/Textureciel1.jpg").mirrored()));
    // Lune->setLumiere();
    Lune->setName("Ciel");
    /* for(int i =0 ;i < allShaders.size(); i++)
        Lune->addShader(allShaders[i]);*/
    //Fin creation
    ////////////
    // qDebug("test");

    //Instance INIT GAME OBJECT // BILLBOARD
    GeometryEngine *geo_bill = new geometryUI;
    // geo_bill->initMesh(":/Mesh/sphere.off", false);
    geo_bill->initLifeBar();
    Transform *tbill = new Transform;
    tbill->setScale(10,10,10);
    tbill->setTranslate(0,0,2);
    Transform *anim_tbill = new Transform;
    Object* noeudBill = addBillboardObject(allShaders[1],satellite,tbill, geo_bill,anim_tbill,new QOpenGLTexture(QImage(":/Texture/lifeBar.png").mirrored()));
    //Fin creation

    //Instance INIT GAME OBJECT //Terre
    GeometryEngine *geo_nuage = new GeometryEngine;


    geo_nuage->initCurvedPlanegeometry(-35,-35,35,35, false);
    // geo_Terre->initMesh(":/Mesh/sphere.off");
    Transform *t_nuage = new Transform;
    t_nuage->setScale(280,280,280);
    t_nuage->setTranslate(0,0,1);
    Transform *anim_nuage = new Transform;
    //anim_Terre->setRotation(0,0,1,1);
    Object* nuage = addGameObject(allShaders[2],NoeudSatellite,t_nuage , geo_nuage,anim_nuage);
    Terre->setName("nuage");
    //Fin creation








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


    QObject::connect(satellite, &Object::emitPosition,
                     Terre, &Object::mapCoordChanged);
    QObject::connect(Terre, &Object::emitTree,
                     herbe, &Object::updateTree);
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
   //  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    // Enable back face culling
    //      glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);
    //! [2]
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);



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
    lastFrame.start();
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
    //compile control shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/Shaders/controlshader.glsl"))
        close();
    //compile control shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/Shaders/tesselationshader.glsl"))
        close();
    //compile geometry shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/Shaders/geometryshader.glsl"))
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
    /*    // Compile fragment shader
    if (!herbeShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/HerbeShader/cloud_fshader.glsl"))
        close();*/

    //compile control shader
    if (!herbeShader->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/Shaders/controlshader.glsl"))
        close();
    //compile control shader
    if (!herbeShader->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/Shaders/HerbeShader/h_tesselationshader.glsl"))
        close();


    // Link shader pipeline
    if (!herbeShader->link())
        close();

    allShaders.push_back(herbeShader);



    // Compile vertex shader QOpenGLShaderProgram
    QOpenGLShaderProgram *cloudShader = new QOpenGLShaderProgram;
    if(!cloudShader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/HerbeShader/h_vshader.glsl"))
        close();

    // Compile fragment shader
    if (!cloudShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/CloudShader/cloud_fshader.glsl"))
     //     if(!cloudShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/HerbeShader/h_fshader.glsl"))
        close();
    //compile control shader
    if (!cloudShader->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/Shaders/controlshader.glsl"))
        close();
    //compile control shader
    if (!cloudShader->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/Shaders/HerbeShader/h_tesselationshader.glsl"))
        close();


    // Link shader pipeline
    if (!cloudShader->link())
        close();

    allShaders.push_back(cloudShader);





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
    const qreal zNear = 0.05, zFar = 150.0, fov = 45.0;

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

    if (polygonMode)
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

        /* QPainter painter(this);
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    painter.setBackground(QBrush(QColor(64, 32, 64)));
    painter.setBrush(QBrush(gradient));
    painter.setPen(QPen(Qt::black));
    painter.setPen(1);
    painter.setPen(QPen(Qt::white));
    painter.setFont(QFont());
    painter.drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("MIAOU"));
    */
    /*
    painter.setPen(Qt::red);
    painter.drawLine(rect().topLeft(), rect().bottomRight());
    painter.beginNativePainting();*/


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
    allShaders[1]->bind();
    allShaders[1]->setUniformValue("textureFeuille", 1); //changer texture
    allShaders[1]->setUniformValue("textureBois", 5);
    allShaders[2]->bind();
    allShaders[2]->setUniformValue("textureFeuille", 1); //changer texture
    allShaders[2]->setUniformValue("textureBois", 5);

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
    QToolTip::showText(QPoint(50,50), "meow",this);

    /*  //Opengl api
    painter.endNativePainting();
    painter.end();*/

    //TODO
    //   mobileobj->updateScene(&program,deltaTime);
    //lastFrame.start();
    //geometries->drawCubeGeometry(&program);
}
void MainWidget::keyPressEvent(QKeyEvent *event)
{emit signalKeyPress(event);
}



bool MainWidget::eventFilter(QObject *object, QEvent *event){
    if(true ||(event->type()==QEvent::KeyPress || event->type()==QEvent::KeyRelease)) {
        //qDebug("filtre ");
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

    case Qt::Key_W: // tourne terrain
    {
    if (polygonMode)
        polygonMode = false;


    else
        polygonMode = true;

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


