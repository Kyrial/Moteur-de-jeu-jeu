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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"
#include "geometrymeshengine.h"
#include "geometryui.h"
#include "gameobject.h"
#include "billboardobject.h"

//#include "meshobject.h"
#include "controler.h"
#include "mobileobj.h"
#include "cameraobject.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QElapsedTimer>
#include <QPainter>
#include <QToolTip>
class GeometryEngine;
/**
 * @file
 * @brief la classe MainWidget est la classe principale qui contiens le graphe de scène et initialise la confiture
 */
/**
 * @brief la classe MainWidget est la classe principale qui contiens le graphe de scène et initialise la confiture
 */
class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur
     * @param parent
     */
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    MainWidget();

    MainWidget(int fps);
    /**
     * @brief modifFPS : modifi les FPS
     * @param x : nouvelle valeur des FPS
     */
    void modifFPS(int x);

    int FPS = 20;
    QElapsedTimer lastFrame;
    QElapsedTimer absoluteTime;
    double deltaTime = 1;

protected:
    /**
     * @brief sauvegarde la position du clique de la souris
     * @param e : position
     */
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    /**
     * @brief initialise le shader
     */
    void initShaders();
    /**
     * @brief initialise la texture
     */
    void initTextures();

    //  void keyPressEvent(QKeyEvent *e) override;


    Object* addGameObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh, Transform *anim,QOpenGLTexture *txtr);
    Object* addMobileObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh, Transform *anim,QOpenGLTexture *texture);
    Object* addBillboardObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh, Transform *anim,QOpenGLTexture *txtr);

    /**
     * @brief initialise le monde
     */
    void initMonde();
    /**
     * @brief métode répertorient tout les objets du graphe de scène
     */
    void scene();

private:

    QBasicTimer timer;
    /**
     * @brief donne un attribut à la texture
     * @param texture : la texture
     */
    void addAttributeToTexture(QOpenGLTexture* texture);
    QOpenGLShaderProgram program;
    QVector<QOpenGLShaderProgram*> allShaders;

    GeometryEngine *geometries;
    GameObject *gameObj;
    Controler *control = new Controler();

    //  MobileObj *mobileobj;
    QOpenGLTexture *texture;

    QOpenGLTexture * textureGrass;
    QOpenGLTexture * textureRock;
    QOpenGLTexture * textureSnow;
    QOpenGLTexture * textureEau;
    QOpenGLTexture * textureBois;
    bool polygonMode = false;


    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
    /**
     * @brief trigget sur event des touches claviers
     * @param e
     */
    void keyPressEvent(QKeyEvent *e) override;
    /**
     * @brief gère tout les évenements
     * @param object
     * @param event
     * @return
     */
    bool eventFilter(QObject *object, QEvent *event) override;
signals:
    /**
     * @brief envois un signal lorsqu'une touche est préssée
     * @param e
     */
    void signalKeyPress(QKeyEvent *e);
    /**
     * @brief projectionChanged : c'est un signal qui avertit le slot connécté que la projection a changé
     * @param val
     */
    void projectionChanged(QMatrix4x4 val);
    /**
     * @brief emitFilter : signal qui avertit qu'une touche à été préssé ou relaché
     * @param event
     */
    void emitFilter(QEvent *event);
public slots :
    void cameraControle();
    /**
     * @brief envois le signal emitFilter()
     * @param e
     */
    void keyPress(QKeyEvent *e);

};

#endif // MAINWIDGET_H
