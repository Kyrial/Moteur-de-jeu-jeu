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
#include "gameobject.h"
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
class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    MainWidget();

    MainWidget(int fps);

    void modifFPS(int x);

    int FPS = 20;
    QElapsedTimer lastFrame;
    QElapsedTimer absoluteTime;
    double deltaTime = 1;

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

  //  void keyPressEvent(QKeyEvent *e) override;


    Object* addGameObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh, Transform *anim,QOpenGLTexture *txtr);
    Object* addMobileObject(QOpenGLShaderProgram* shad,Object *parent, Transform *t, GeometryEngine *mesh, Transform *anim,QOpenGLTexture *texture);


    void initMonde();
    void scene();

private:
    QBasicTimer timer;

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


    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

    void keyPressEvent(QKeyEvent *e) override;
    bool eventFilter(QObject *object, QEvent *event) override;
signals:
    void signalKeyPress(QKeyEvent *e);
    void projectionChanged(QMatrix4x4 val);
    void emitFilter(QEvent *event);
public slots :
    void cameraControle();
    void keyPress(QKeyEvent *e);
};

#endif // MAINWIDGET_H
