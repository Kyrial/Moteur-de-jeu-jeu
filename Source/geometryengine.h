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

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QtGui/QImage>
#include <QVector2D>
#include <QVector3D>

#include "BasicIO.h"

#include "transform.h"
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};


class GeometryEngine : protected QOpenGLFunctions_4_1_Core
{

public:

    GeometryEngine();
    QVector3D coordLastCollision = QVector3D(999,999,999);
    bool withNormal = false;
    QVector2D lastCentre = QVector2D(0,0);
    virtual ~GeometryEngine();


    virtual void drawCubeGeometry(QOpenGLShaderProgram *program);
    virtual void initMesh(std::string filename, bool a= true){}
    virtual void initMeshObj(std::string filename,bool a= true){}
    virtual void bindMesh(std::vector< std::vector<unsigned int> >  faces){}
    virtual void initLifeBar(){}
    virtual bool updateLifeBar(double deltaTime){}

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;


    QVector<QMatrix4x4> modelMatrices;

    void initCubeGeometry();
    void initPlanegeometry(float Xmin=-1,float Ymin=-1,float Xmax=1,float Ymax=1,float centreX =0, float centreY=0);

    int triangle_strip = 0; // 0 = triangle_strip // 1 = triangle // 2 = patch
    QVector3D BBMin = QVector3D(0,0,0);
    QVector3D BBMax = QVector3D(0,0,0);
    QVector3D internBBMin = QVector3D(0,0,0);
    QVector3D internBBMax = QVector3D(0,0,0);
    bool heightMap = false;
    bool noCollision = false;
protected:
    QImage img;
    std::vector<QVector3D>  vertex;
    //void initPlanegeometry();
    void subdivisePlan(int x, int y,  VertexData vertices[],float Xmin,float Ymin,float Xmax,float Ymax,float centreX =0, float centreY=0);//,std::string nameWeightMap );
    void TriangleStripForPlan(int x, int y,GLushort indices[]);
    void TriangleListForPlan(int x, int y,GLushort indices[]);
    void updatePlanegeometry(float Xmin,float Ymin,float Xmax,float Ymax, float centreX =0, float centreY=0);
    void convertStripToTriangle(GLushort indicesIn[], GLushort indicesOut[], int size);

    std::vector<QVector3D> getVertex();

    int precisionX = 100; // attention! une valeur trop haute provoque
    int precisionY= 100;  // un dépassement de capacité (size > sizemax of array)

    QVector3D Min = QVector3D(0,0,0);
    QVector3D Max = QVector3D(0,0,0);

    void initBB(std::vector<QVector3D> vertex);
    void initBB(VertexData vertices[], int i);
    void setBBMin(QVector3D v);
    void setBBMax(QVector3D v);

    float getHauteur(QVector2D coordText);
public:


    QVector3D findCoordmesh(GeometryEngine *geo, QMatrix4x4 objM,  QMatrix4x4 ourM,  bool &collision, QVector3D & mesh);
    QVector3D getNormal();
    QVector3D getNormal(QVector3D mesh);
    QVector3D recallageCollision(GeometryEngine *geoB);
    void resetBB();
    bool ifNoeudVide();
    void remplaceBB(GeometryEngine *geo);
    void remplaceBB(QVector3D m,QVector3D M);
    void updateBB(QMatrix4x4 m);
    void ajustBB(GeometryEngine *geo);
    void ajustBB(QVector3D min, QVector3D max);
    static QVector3D  calcBBMin(QVector3D const & last, QVector3D const & min);
    static QVector3D  calcBBMax(QVector3D const & last, QVector3D const & max);
    bool intersect(GeometryEngine *geo);
    bool internintersect(GeometryEngine *geo);
    QVector3D gestionCollision(GeometryEngine *geo,QVector3D vec, QVector3D mesh = QVector3D(0,0,0));


    QVector3D mapCoordChanged(QVector3D vec,QMatrix4x4 objM,QMatrix4x4 ourM);

    void addInstancedGrass(int nb, QVector3D min=QVector3D(-13,-13,0), QVector3D max=QVector3D(13,13,0));


    void test(){
         /*  glPushMatrix();
           glRotatef(90, 0, 0, 1);
           QString qStr = QString("Here's a very long string which doesn't mean anything at all but had some rendering problems");
           renderText(0.0, 0.0, 0.0, qStr);
           glPopMatrix();*/
    }

};

#endif // GEOMETRYENGINE_H
