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

#include "geometryengine.h"

#include <iostream>

#include <QVector2D>
#include <QVector3D>


int SEED = 0;

int hash[256] ={208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};

int noise2(int x, int y, int seed = SEED)
{
    int yindex = (y + seed) % 256;
    if (yindex < 0) {
        yindex += 256;
    }
    int  xindex = (hash[yindex] + x) % 256;
    if (xindex < 0) {
        xindex += 256;
    }
    return int (hash[xindex]);
}

float Rand(QVector2D co){
    float value = sin(QVector2D::dotProduct(co ,QVector2D(12.9898,78.233))) * 43758.5453;
    return value - floor(value);
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}
float noise2D(float x, float y){
    // float s =Rand(QVector2D(floor(x),floor(y)));
    //    float t =Rand(QVector2D(floor(x)+1,floor(y)));
    //    float u =Rand(QVector2D(floor(x),floor(y)+1));
    //   float v =Rand(QVector2D(floor(x)+1,floor(y)+1));

    float s =noise2(int(floor(x)),int(floor(y)));
    float t =noise2(int(floor(x)+1),int(floor(y)));
    float u =noise2(int(floor(x)),int(floor(y)+1));
    float v =noise2(int(floor(x)+1),int(floor(y)+1));

    float low = smooth_inter(s, t, x-floor(x));
    float high = smooth_inter(u, v, x-floor(x));
    return smooth_inter(low, high, y-floor(y));
}

float perlin2d(float x, float y , int depth)
{
    float xa = x*0.3;
    float ya = y*0.3;
    float amp = 1;
    float fin = 0;
    float div = 0.0;
    //div += 256;
    int i;
    for(i=0; i<depth; i++)
    {
        //div += 256*(amp);
        div+=255*amp;
        fin += noise2D(xa, ya) * amp;
        amp /= 10;//2/pow(2,depth+1);
        xa *= 20;
        ya *= 20;
    }

    return fin/div;
}


//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    //   initCubeGeometry();

    //    initPlanegeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]



std::vector<QVector3D> GeometryEngine::getVertex(){
    return vertex;
}


//recallage lors collision
QVector3D GeometryEngine::recallageCollision(GeometryEngine *geoB){
    QVector3D milieuA = BBMin + (BBMax - BBMin)/2;
    QVector3D milieuB = geoB->BBMin +(geoB->BBMax - geoB->BBMin)/2;

    QVector3D vecAB = milieuB -milieuA;
    return getNormal()*1.5;
}




QVector3D GeometryEngine::getNormal(){
    QVector3D val;
    if(heightMap){
        QVector3D pt1 = QVector3D(BBMin[0],BBMin[1],0);
        QVector3D pt2 = QVector3D(BBMin[0],BBMax[1],0);
        QVector3D pt3= QVector3D(BBMax[0],BBMax[1],0);
        val= QVector3D::normal(pt2-pt1, pt3-pt1);
    }

    else{
        QVector3D pt = QVector3D(BBMax[0],BBMin[1],BBMin[2]);
        val= QVector3D::normal(pt-BBMin, BBMax-BBMin);
    }
    return val;

}

QVector3D GeometryEngine::getNormal(QVector3D pt){
    QVector3D A = QVector3D(pt.x(),pt.y(),perlin2d(pt.x(),pt.y()  , 2)-.3)*2;
    QVector3D B = QVector3D(pt.x()+0.1,pt.y(),perlin2d(pt.x()+0.1,pt.y()  , 2)-.3)*2;
    QVector3D C = QVector3D(pt.x(),pt.y()+0.1,perlin2d(pt.x(),pt.y()+0.1  , 2)-.3)*2;
    return QVector3D::normal(A,B,C);
}

//geo en déplacement
QVector3D GeometryEngine::gestionCollision(GeometryEngine *geoB, QVector3D vec, QVector3D mesh){
    // qDebug("  %f,   %f    %f   \n ", mesh.x(), mesh.y(),(mesh.z()));
    if(mesh == QVector3D(0,0,0)){
        QVector3D milieuA = BBMin + (BBMax - BBMin)/2;
        QVector3D milieuB = geoB->BBMin +(geoB->BBMax - geoB->BBMin)/2;
        // qDebug("\n\nAAAAAAAAAAAAAAAAAAAAA\n\n");
        QVector3D vecAB = milieuB -milieuA;

        //V = V - 2(V.N)*N

        //  return vec - 2* QVector3D::dotProduct(vec, vecAB) * vecAB;
        return vec - 2* QVector3D::dotProduct(vec, getNormal()) * getNormal();
    }
    else{
        return vec - 2* QVector3D::dotProduct(vec, getNormal(mesh)) * getNormal(mesh);
    }

}

bool GeometryEngine::ifNoeudVide(){
    return Min == QVector3D(0,0,0) && Max == QVector3D(0,0,0);
}
void GeometryEngine::resetBB(){
    BBMin = QVector3D(0,0,0);
    BBMax = QVector3D(0,0,0);
}

bool GeometryEngine::internintersect(GeometryEngine *geo){
    return (geo->BBMin.x() <= internBBMax.x() && geo->BBMax.x() >= internBBMin.x()) &&
            (geo->BBMin.y() <= internBBMax.y() && geo->BBMax.y() >= internBBMin.y()) &&
            (geo->BBMin.z() <= internBBMax.z() && geo->BBMax.z() >= internBBMin.z());
}
bool GeometryEngine::intersect(GeometryEngine *geo){
    bool result;
    //  if (heightMap == false){
    result = (geo->BBMin.x() <= BBMax.x() && geo->BBMax.x() >= BBMin.x()) &&
            (geo->BBMin.y() <= BBMax.y() && geo->BBMax.y() >= BBMin.y()) &&
            (geo->BBMin.z() <= BBMax.z() && geo->BBMax.z() >= BBMin.z());
    // }
    //  else{
    //      result = (geo->BBMin.x() <= BBMax.x() && geo->BBMax.x() >= BBMin.x()) &&
    //           (geo->BBMin.y() <= BBMax.y() && geo->BBMax.y() >= BBMin.y()); }



    return result;
}



//matrice avec coefficiant négatif -> inverse le min et le max !
void GeometryEngine::updateBB(QMatrix4x4 m){
    // if (noCollision) return;
    QVector3D tempMin = calcBBMin( m*Min,m*Max);
    QVector3D tempMax = calcBBMax( m*Min,m*Max);

    BBMin = tempMin;
    BBMax = tempMax;
    internBBMin = tempMin;
    internBBMax = tempMax;
}


void GeometryEngine::ajustBB(QVector3D min, QVector3D max){
    if(BBMin ==BBMax){
        BBMin = min;
        BBMax = max;
    }
    else{
        BBMin = calcBBMin(BBMin, min);
        BBMax = calcBBMax(BBMax, max);
    }
}
QVector3D GeometryEngine::calcBBMin(QVector3D const & last, QVector3D const & min){
    QVector3D result = last;
    if(min[0]< last[0])
        result[0]= min[0];
    if(min[1]< last[1])
        result[1]= min[1];
    if(min[2]< last[2])
        result[2]= min[2];
    return result;
}
QVector3D GeometryEngine::calcBBMax(QVector3D const & last, QVector3D const & max){
    QVector3D result = last;
    if(max[0]> last[0])
        result[0]= max[0];
    if(max[1]> last[1])
        result[1]= max[1];
    if(max[2]> last[2])
        result[2]= max[2];
    return result;
}

void GeometryEngine::ajustBB(GeometryEngine *geo){
    ajustBB(geo->BBMin,geo->BBMax);
}

void GeometryEngine::setBBMin(QVector3D v){
    BBMin = v;
}
void GeometryEngine::setBBMax(QVector3D v){
    BBMax = v;
}
void GeometryEngine::remplaceBB(GeometryEngine* geo){
    BBMin = geo->BBMin;
    BBMax = geo->BBMax;
}
void GeometryEngine::remplaceBB(QVector3D m,QVector3D M){
    BBMin = m;
    BBMax = M;
}

void GeometryEngine::initBB(VertexData vertices[],int max){

    Min= vertices[0].position;
    Max= vertices[0].position;

    for(int i=0;i<max; i++){
        if(vertices[i].position[0]< Min[0])
            Min[0]= vertices[i].position[0];
        if(vertices[i].position[1]< Min[1])
            Min[1]= vertices[i].position[1];
        if(vertices[i].position[2]< Min[2])
            Min[2]= vertices[i].position[2];

        if(vertices[i].position[0]> Max[0])
            Max[0]= vertices[i].position[0];
        if(vertices[i].position[1]> Max[1])
            Max[1]= vertices[i].position[1];
        if(vertices[i].position[2]> Max[2])
            Max[2]= vertices[i].position[2];
    }
    BBMin = Min;
    BBMax = Max;
}


void GeometryEngine::initBB(std::vector<QVector3D> vertex){

    Min= this->vertex[0];
    Max= this->vertex[0];

    foreach(QVector3D val , vertex){
        if(val[0]< Min[0])
            Min[0]= val[0];
        if(val[1]< Min[1])
            Min[1]= val[1];
        if(val[2]< Min[2])
            Min[2]= val[2];

        if(val[0]> Max[0])
            Max[0]= val[0];
        if(val[1]> Max[1])
            Max[1]= val[1];
        if(val[2]> Max[2])
            Max[2]= val[2];
    }
    BBMin = Min;
    BBMax = Max;

}

float GeometryEngine::getHauteur(QVector2D coordText){


    int x = (coordText[0])*img.width();
    int y = (coordText[1])*img.height();

    // QImage im2g = QImage(QString(":/heightmap.png"));
    QRgb rgb = img.pixel(x,y);
    //    float q = (qRed(img.pixel(y,x))/ 125.0-1.0)*0.7;
    return (qRed(rgb)/ 255.0);
}

QVector3D GeometryEngine::findCoordmesh(GeometryEngine *geo, QMatrix4x4 objM,  QMatrix4x4 ourM, bool &collision, QVector3D &normal){
    QMatrix4x4 invObjM = Transform::inverse(objM);
    QMatrix4x4 invOurM = Transform::inverse(ourM);

    QVector3D inv_BBMin = invObjM*geo->BBMin;
    QVector3D inv_BBMax = invObjM*geo->BBMax;

    QVector3D a = (inv_BBMin + QVector3D(inv_BBMax.x(),inv_BBMax.y(), inv_BBMin.z()))/2; // minimum BB
    //   QVector3D b = invObjM*geo->BBMax;
    //  QVector3D c = invOurM*BBMin;
    //   QVector3D d = invOurM*BBMax;

    // vertices[i*y+j]= {QVector3D(Xmin+intervalX*i, Ymin+intervalY*j,0.0f ), QVector2D((intervalX_Texture*i)/2, (intervalY_Texture*j)/2)};
    float interval=(Max[0]-Min[0])/(float)(precisionX-1);
    //(val+min)/ interval = case
    int caseX = (a.x()- Min[0])/interval;
    int caseY = (a.y()- Min[1])/interval;
    //float interval_Texture=2/(float)(precisionX-1);
    // QVector3D k
    normal= vertex[caseX*precisionX+caseY];
    /*VertexData vertices[precisionX*precisionY];

   for(int i=0; i<precisionX; i++){
        for(int j=0;j<precisionY; j++){
            float hauteurMesh = (perlin2d( float(Min[0]+interval*i),  float(Min[1]+interval*j) , 1)-0.3)*2;
            vertices[i*precisionY+j]= {QVector3D(Min[0]+interval*i, Min[1]+interval*j,hauteurMesh ), QVector2D((interval_Texture*i)/2, (interval_Texture*j)/2)};
}}
   vertices[caseX*precisionX+caseY].position.setZ(1);

   arrayBuf.bind();
   arrayBuf.allocate(vertices, precisionX*precisionY * sizeof(VertexData));



*/
    //QVector2D coordText = QVector2D((interval_Texture*caseX)/2, (interval_Texture*caseY)/2);
    QVector3D newCoord = inv_BBMin;
    // float colorx = getHauteur( coordText);
    //float hauteurMesh = colorx*0.7 +k[2];
    float hauteurMesh =(perlin2d( normal.x(), normal.y() , 6)-0.3)*2; // (perlin2d( k.x(), k.y() , 8)-0.3)*2;
    //float hauteurTexture = std::max(-0.5, std::min((float)1.25,colorx*2)-0.25);
    if(hauteurMesh<-0.2){
        hauteurMesh = -0.2;//+cos((animation+(a_position.y)*300)/100)/150;
        normal= QVector3D(0,0,0);
    }
    QVector3D vecTranslate;
    if(hauteurMesh < a[2])
        collision  = false;
    else
        geo->coordLastCollision = objM*QVector3D(normal.x(), normal.y(),hauteurMesh);
    newCoord[2]= hauteurMesh;
    newCoord  = objM*newCoord;
    vecTranslate = newCoord - geo->BBMin;
    //normal = k;
    return vecTranslate;
}



















void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    // Hence 4 vertices per face and 6 faces vertices = 24 vertices
    unsigned int vertexNumber = 24 ;
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };


    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    unsigned int indexCount = 34; //Careful update indicesNumber when creating new geometry
    GLushort indices[] = {
        0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
        8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };


    initBB(vertices, vertexNumber);


    //! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount* sizeof(GLushort));
    std::cout << indexBuf.size() << " index count " << indexCount <<"sizeof" <<  sizeof(GLushort) << std::endl;
    //! [1]
}

QVector3D GeometryEngine::mapCoordChanged(QVector3D coordCharacter, QMatrix4x4 objM, QMatrix4x4 ourM){
    //QMatrix4x4 invObjM = Transform::inverse(objM);
    QMatrix4x4 invOurM = Transform::inverse(ourM);
    //QVector3D coordCharacter1 = invObjM*coordCharacter;
    QVector3D coordCharacter2 = invOurM*coordCharacter;
    float centreX = floor(coordCharacter2[0]);
    float centreY = floor(coordCharacter2[1]);
    if (lastCentre != QVector2D(centreX,centreY)){
        lastCentre = QVector2D(centreX,centreY);
         qDebug("maoww :%f, et coordplan = %f \n ",centreX, centreY );
        //qDebug("maoww :%f, et coordperso = %f \n ",coordCharacter1[0], coordCharacter1[1] );
        //qDebug("maoww :%f, et coordperso = %f \n ",coordCharacter2[0], coordCharacter2[1] );
        updatePlanegeometry((centreX)-25,(centreY)-25,(centreX)+25,(centreY)+25, (centreX), (centreY));
    }
    return coordCharacter2;
    //   addInstancedGrass(300,QVector3D((centreX)-12,(centreY)-12,0),QVector3D((centreX)+12,(centreY)+12,0) );
}
/*
void GeometryEngine::reajustePlan(int x, int y, VertexData vertices[], float Xmin=-1,float Ymin=-1,float Xmax=1,float Ymax=1, float centreX, float centreY)//, std::string  nameWeightMap = "")
{
    vertex.resize(x*y);
    float intervalX_Texture=2/(float)(x-1);
    float intervalY_Texture=2/(float)(y-1);

    float intervalX=(Xmax-Xmin)/(float)(x-1);
    float intervalY=(Ymax-Ymin)/(float)(y-1);
    for(int i=0; i<x; i++){
        for(int j=0;j<y; j++){
            vertices[i*y+j]= {QVector3D(Xmin+intervalX*i, Ymin+intervalY*j,0.0f ), QVector2D((intervalX_Texture*(i))*2+(centreX/(Xmax-Xmin))*4, (intervalY_Texture*(j))*2+(centreY/(Ymax-Ymin))*4)};
            vertex[i*y+j] =QVector3D(Xmin+intervalX*i, Ymin+intervalY*j,0.0f );
        }
    }
}*/
void GeometryEngine::subdivisePlan(int x, int y, VertexData vertices[], float Xmin=-1,float Ymin=-1,float Xmax=1,float Ymax=1, float centreX, float centreY)//, std::string  nameWeightMap = "")
{
    vertex.resize(x*y);
    float intervalX_Texture=2/(float)(x-1);
    float intervalY_Texture=2/(float)(y-1);

    float intervalX=(Xmax-Xmin)/(float)(x-1);
    float intervalY=(Ymax-Ymin)/(float)(y-1);
    for(int i=0; i<x; i++){
        for(int j=0;j<y; j++){
            //   qDebug("%f %f",Xmin+intervalX*i, Ymin+intervalY*j);
            //  vertices[i*y+j]= {QVector3D(Xmin+intervalX*i, Ymin+intervalY*j, static_cast<float> (rand()) / static_cast<float> (RAND_MAX) ), QVector2D((intervalX_Texture*i)/2, (intervalY_Texture*j)/2)};
            //            vertices[i*y+j]= {QVector3D(Xmin+intervalX*i, Ymin+intervalY*j,0.0f ), QVector2D((intervalX_Texture*(i))*2+centreX*((Xmax-Xmin)/(float)(x-1))*2, (intervalY_Texture*(j))*2+centreY*((Ymax-Ymin)/(float)(y-1))*2)};
            vertices[i*y+j]= {QVector3D(Xmin+intervalX*i, Ymin+intervalY*j,0.0f ), QVector2D((intervalX_Texture*(i))*2+(centreX/(Xmax-Xmin))*4, (intervalY_Texture*(j))*2+(centreY/(Ymax-Ymin))*4)};
            vertex[i*y+j] =QVector3D(Xmin+intervalX*i, Ymin+intervalY*j,0.0f );
        }
    }
}

void GeometryEngine::TriangleStripForPlan(int x, int y,GLushort indices[])
{    int count =0;
     for(int i=0; i<x-1; i++){
         for(int j=0;j<y; j++){
             //count+=2;
             //      qDebug("indices %i, %i",2*i+i*(y*2)+j*2,2*i+i*(y*2)+j*2+1 );
             //   indices[2*i+i*(y*2)+j*2] = i*y+j;
             //    indices[2*i+i*(y*2)+j*2+1] = (i+1)*y+j;
             indices[count++] = i*y+j;
             indices[count++] = (i+1)*y+j;
         }
         if(i!=x-2){
             //count +=2;
             //   qDebug("indices degenerer %i, %i",2*i+i*(y*2)+y*2,2*i+i*(y*2)+y*2+1 );
             //    indices[2*i+i*(y*2)+y*2]=(i+1)*y+y-1;
             //    indices[2*i+i*(y*2)+y*2+1]=(i+1)*y;
             indices[count++]=(i+1)*y+y-1;
             indices[count++]=(i+1)*y;
         }
     }
      indices[count]=indices[count-1];
}
void GeometryEngine::TriangleListForPlan(int x, int y,GLushort indices[]){
    int count =0;
    for(int i=0; i<x-1; i++){
        for(int j=0;j<y-1; j++){
            indices[count++] = i*y+j;
            indices[count++] = (i+1)*y+j;
            indices[count++] = (i+1)*(y+1)+j;
        }
    }
    for(int i=0; i<x-1; i++){
        for(int j=1;j<y; j++){
            indices[count++] = i*y+j;
            indices[count++] = (i+1)*(y-1)+j;
            indices[count++] = (i+1)*y+j;

        }
    }
}

unsigned int GeometryEngine::convertStripToTriangle(GLushort indicesIn[], GLushort indicesOut[], int size){
    short a, b, c;
     unsigned int count =0;
    for( int i=0; i<size -2; i++ )
    {
        if(indicesIn[i+0] != indicesIn[i+1] && indicesIn[i+0] != indicesIn[i+2] && indicesIn[i+1] != indicesIn[i+2]){
        if( i%2 == 0 )
        {
            a = indicesIn[i+0];
            b = indicesIn[i+1];
            c = indicesIn[i+2];
        }
        else
        {
            a = indicesIn[i+2];
            b = indicesIn[i+1];
            c = indicesIn[i+0];
        }
        indicesOut[count++]=a;
        indicesOut[count++]=b;
        indicesOut[count++]=c;
        }
    }
    return count;
}


void GeometryEngine::updatePlanegeometry(float Xmin,float Ymin,float Xmax,float Ymax, float centreX, float centreY){
    int x=precisionX;
    int y=precisionY;
    unsigned int vertexNumber = x*y ;
    VertexData vertices[x*y];
    subdivisePlan(x,  y,  vertices, Xmin, Ymin, Xmax, Ymax, centreX,  centreY);

    initBB(vertices, vertexNumber);
    if(Min[2]==0 && Max[2]==0){
        Max[2] = 1.5;
        Min[2] = -3.0;
    }
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));
    arrayBuf.release();
}

void GeometryEngine::initPlanegeometry(float Xmin,float Ymin,float Xmax,float Ymax, float centreX, float centreY)
{
    //img = QImage(":/heightmap-1024x1024.png");
    heightMap = true;
    int x=precisionX;
    int y=precisionY;
    unsigned int vertexNumber = x*y ;
    VertexData vertices[x*y];
    unsigned int indexCount = x*y+y*(x-2)+2*(x-2)+2;
//     unsigned int indexCount = (x*y-1)*3;
    GLushort indicesIn[indexCount];
    subdivisePlan(x,  y,  vertices, Xmin, Ymin, Xmax, Ymax, centreX,  centreY);
    TriangleStripForPlan(x,  y, indicesIn);
  //  TriangleListForPlan(x,  y, indicesIn);
    // qDebug("taille index %i",indexCount);
    //qDebug("taille index tab %i",x*y+y*(x-2)+2*(x-2)+2);
    GLushort indicesOut[indexCount*3];
    indexCount = convertStripToTriangle(indicesIn, indicesOut, indexCount);


    initBB(vertices, vertexNumber);
    if(Min[2]==0 && Max[2]==0){
        Max[2] = 1.5;
        Min[2] = -3.0;
    }
    //! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));
    arrayBuf.release();
    // Transfer index data to VBO 1
    indexBuf.bind();
//    indexBuf.allocate(indicesOut,  ((indexCount*3-1)* sizeof(GLushort)));
    indexBuf.allocate(indicesOut,  ((indexCount)* sizeof(GLushort)));
    //  std::cout << indexBuf.size() << " index count " << indexCount <<"sizeof" <<  sizeof(GLushort) << std::endl;
    indexBuf.release();
    //! [1]
}
double randMToN(double M, double N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
}

void GeometryEngine::addInstancedGrass(int nb, QVector3D min, QVector3D max){

    modelMatrices.clear();
    float nbMaxArbre =0.5;
    float ratioArbre=0.42;
    // float intervalX=( max[0]-min[0])/(float)(nbMaxArbre-1);
    // float intervalY=( max[1]-min[1])/(float)(nbMaxArbre-1);
    for(float i=min[0]+7; i<max[0]-7; i+=nbMaxArbre){
        for(float j=min[1]+7;j<max[1]-7; j+=nbMaxArbre){
            float hauteurMesh =(perlin2d( i, j , 5)-0.3)*2;
            float arbreChance =(perlin2d( i*2, j*2 , 1));
            if(hauteurMesh>0 && ratioArbre> arbreChance){
                Transform t;
                t.setTranslate(i,j,hauteurMesh-0.02);

                Transform t_2;

                float randRotation = perlin2d( i*20, j*20 , 1)*90;
                float randScale = perlin2d( i*15, j*15 , 1)*0.5+0.9;
                t_2.setScale(QVector3D(randScale,randScale,randScale));

                t_2.setRotation(0,0,1,randRotation);
                modelMatrices.push_back(t.doTransformation()*t_2.doTransformation()); //t.doAnimation(&t_2,1));

            }
        }
    }


    /*
    srand(0);
    for(int i =0; i<nb; i++){
        float randX = randMToN( min[0],   max[0]);//randMToN( -12.0,  12.0);
        float randY = randMToN( min[1],   max[1]);//randMToN( -12.0,  12.0);
        float hauteurMesh =(perlin2d( randX, randY , 8)-0.3)*2;
        Transform t;
        if(hauteurMesh>0){
            t.setTranslate(randX,randY,hauteurMesh);

            Transform t_2;
            float randRotation = randMToN( -90.0,  90.0);
            float randScale = randMToN( 0.9,  1.3);
            t_2.setScale(QVector3D(randScale,randScale,randScale));

            t_2.setRotation(0,0,1,randRotation);
            modelMatrices.push_back(t.doTransformation()*t_2.doTransformation()); //t.doAnimation(&t_2,1));
        }
    }*/

}



//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    //   std::cout << indexBuf.size() << " , meow " <<   std::endl;
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    int size = (int)indexBuf.size();
    // std::cout << indexBuf.size() << " , meow " <<  size << std::endl;

    int MaxPatchVertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
    // printf("Max supported patch vertices %d\n", MaxPatchVertices);
    glPatchParameteri(GL_PATCH_VERTICES, 3);


    if(triangle_strip == 0){
        //glDrawElements(GL_TRIANGLE_STRIP, size/2, GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
        glDrawElements(GL_PATCHES, size/2, GL_UNSIGNED_SHORT, 0);
        //glDrawArrays( GL_PATCHES, 0, size/2 );
    }
    if(triangle_strip == 1)
        //        glDrawElements(GL_TRIANGLES, size/2, GL_UNSIGNED_SHORT, 0);
        glDrawElements(GL_PATCHES, size/2, GL_UNSIGNED_SHORT, 0);
    if(triangle_strip == 2)
        glDrawElements(GL_PATCHES, size/2, GL_UNSIGNED_SHORT, 0);


    //glDrawElementsInstanced(GL_TRIANGLES, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
}

//! [2]
