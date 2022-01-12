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
    QVector3D texCoord;
};

/**
 * @brief pour la boite englobante (uniquement utilisé pour les instances)
 */
struct MinMax
{
    QVector3D BBMin =QVector3D(0,0,0);
    QVector3D BBMax = QVector3D(0,0,0);
};

/**
* @file
* @brief le fichier contient la classe GeometryEngine qui effectue toute les actions en rapport aux maillage
*/

/**
* @brief la classe GeometryEngine effectue toute les actions en rapport aux maillage
*/
class GeometryEngine : protected QOpenGLFunctions_4_1_Core
{

public:
    bool withTextureCoord = false;
    QVector<MinMax> internbbInstenced;

    QVector3D coordLastCollision = QVector3D(999,999,999);
    QVector2D lastCentre = QVector2D(0,0);

    /**
     * @brief BBMin: minimum de la AABB du noeud (englobe les AABB des enfants) dans l'espace monde
     */
    QVector3D BBMin = QVector3D(0,0,0);
    /**
     * @brief BBMax: maximum de la AABB du noeud (englobe les AABB des enfants) dans l'espace monde
     */
    QVector3D BBMax = QVector3D(0,0,0);
    /**
     * @brief internBBMin: minimum de la AABB du mesh  dans l'espace monde
     */
    QVector3D internBBMin = QVector3D(0,0,0);
    /**
     * @brief internBBMax: maximum de la AABB du mesh  dans l'espace monde
     */
    QVector3D internBBMax = QVector3D(0,0,0);
    bool withNormal = false;
    bool heightMap = false;
    bool noCollision = false;
    float precisionTexture=1;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    /**
     * @brief modelMatrices contient les matrice de transformation des instance si elles existent
     */
    QVector<QMatrix4x4> modelMatrices;

    int triangle_strip = 0; // 0 = triangle_strip // 1 = triangle // 2 = patch


    GeometryEngine();
    virtual ~GeometryEngine();
    /**
     * @brief dessine le mesh bind
     * @param program le shader
     */
    virtual void drawCubeGeometry(QOpenGLShaderProgram *program);
    /**
     * @brief initMesh methode virtuel, voir GeometryMeshEngine::initMesh()
     * @param filename
     * @param collisionActivated vrai si collision activé
     * @param centre pour changer la direction des normals
     * @param inverse inverse la direction des normals
     */
    virtual void initMesh(std::string filename, bool collisionActivated= true,bool centre= false, bool inverse = false){}
    /**
     * @brief initMeshObj methode virtuel, voir GeometryMeshEngine::initMeshObj()
     * @param filename
     * @param collisionActivated vrai si collision activé
     * @param centre pour changer la direction des normals
     * @param inverse inverse la direction des normals
     */
    virtual void initMeshObj(std::string filename,bool collisionActivated= true,bool centre= false, bool inverse = false){}
    /**
     * @brief bindMesh  methode virtuel, voir GeometryMeshEngine::bindMesh()
     * @param faces tableau des face de l'objet
     * @param centre pour changer la direction des normals
     * @param inverse inverse la direction des normals
     */
    virtual void bindMesh(std::vector< std::vector<unsigned int> >  faces,bool centre= false, bool inverse = false){}
    /**
     * @brief virtual, voir BillboardObject::initLifeBar()
     */
    virtual void initLifeBar(){}
    /**
     * @brief virtual, voir BillboardObject::updateLifeBar()

     */
    virtual bool updateLifeBar(double deltaTime){}
    /**
     * @brief virtual, voir GeometryMeshEngine::setNormalToCentreCircle
     */
    virtual QVector3D setNormalToCentreCircle(QVector3D vec, QVector3D centre, bool inverse){};

    /**
     * @brief créer un cube
     */
    void initCubeGeometry();
    /**
     * @brief initialise la conseption d'un plan, appel à subdivisePlan() et bind les buffers
     * @param Xmin
     * @param Ymin
     * @param Xmax
     * @param Ymax
     * @param centreX centre du terrain axe X
     * @param centreY centre du terrain axe Y
     */
    void initPlanegeometry(float Xmin=-1,float Ymin=-1,float Xmax=1,float Ymax=1,float centreX =0, float centreY=0);
    /**
     * @brief initialise la conseption d'un plan incurvé, appel à subdiviseCurvedPlan() et bind les buffers
     * @param Xmin
     * @param Ymin
     * @param Xmax
     * @param Ymax
     * @param collisionActivated boolean si collision
     */
    void initCurvedPlanegeometry(float Xmin,float Ymin,float Xmax,float Ymax,bool collisionActivated);
    /**
     * @brief change la precision de la texture
     * @param val
     */
    void setPrecisionTexture(float val);

protected:
    /**
     * @brief vertex contient le maillage
     */
    std::vector<QVector3D>  vertex;

    /**
     * @brief Min min de l'AABB du mesh
     */
    QVector3D Min = QVector3D(0,0,0);

    /**
     * @brief Max max de l'AABB du mesh
     */
    QVector3D Max = QVector3D(0,0,0);

    /**
     * @brief Subdivise le plan de precision x et y,
     * @param x precision
     * @param y precision
     * @param vertices
     * @param Xmin intervalle
     * @param Ymin intervalle
     * @param Xmax intervalle
     * @param Ymax intervalle
     * @param centreX centre du terrain axe X
     * @param centreY centre du terrain axe Y
     */
    void subdivisePlan(int x, int y,  VertexData vertices[],float Xmin,float Ymin,float Xmax,float Ymax,float centreX =0, float centreY=0);//,std::string nameWeightMap );
    /**
     * @brief Subdivise le plan incurvé de precision x et y,
     * @param x precision
     * @param y precision
     * @param vertices
     * @param Xmin intervalle
     * @param Ymin intervalle
     * @param Xmax intervalle
     * @param Ymax intervalle
     */
    void subdiviseCurvedPlan(int x, int y, VertexData vertices[], float Xmin=-1,float Ymin=-1,float Xmax=1,float Ymax=1);
    /**
     * @brief TriangleStripForPlan ordonne les indices en triangleStrip
     * @param x
     * @param y
     * @param indices
     */
    void TriangleStripForPlan(int x, int y,GLushort indices[]);
    /**
     * @brief updatePlanegeometry met a jour le plan du terrain
     * @param Xmin intervalle
     * @param Ymin intervalle
     * @param Xmax intervalle
     * @param Ymax intervalle
     * @param centreX centre du terrain axe X
     * @param centreY centre du terrain axe Y
     */
    void updatePlanegeometry(float Xmin,float Ymin,float Xmax,float Ymax, float centreX =0, float centreY=0);
    /**
     * @brief convertStripToTriangle
     * @param indicesIn
     * @param indicesOut
     * @param size
     * @return
     */
    unsigned int convertStripToTriangle(GLushort indicesIn[], GLushort indicesOut[], int size);

    std::vector<QVector3D> getVertex();

    /**
     * @brief precisionX presision du maillage
     */
    int precisionX = 101; // attention! une valeur trop haute provoque
    /**
     * @brief precisionY presision du maillage
     */
    int precisionY= 101;  // un dépassement de capacité (size > sizemax of array)


    /**
     * @brief initBB initialise Min et Max en fonction de vertex
     * @param vertex
     */
    void initBB(std::vector<QVector3D> vertex);
    /**
     * @brief initBB initialise Min et Max en fonction de vertices
     * @param vertex
     */
    void initBB(VertexData vertices[], int i);

    void setBBMin(QVector3D v);
    void setBBMax(QVector3D v);

  //  float getHauteur(QVector2D coordText);
public:

    /**
     * @brief findCoordmesh gère la collision entre objet et terrain.
     * @param geo le geometryEngine de l'objet
     * @param objM matrice de transformation de geometryEngine
     * @param ourM matrice de transformation du terrain
     * @param collision[out] boolean si collision ou non
     * @param mesh[out] coord du mesh ou l'impact a lieu
     * @return retourne le vecteur reflechit
     */
    QVector3D findCoordmesh(GeometryEngine *geo, QMatrix4x4 objM,  QMatrix4x4 ourM,  bool &collision, QVector3D & mesh);
    QVector3D getNormal();
    QVector3D getNormal(QVector3D vertex);
    /**
     * @brief recallageCollision
     * @param geoB
     * @param instance
     * @return
     */
    QVector3D recallageCollision(GeometryEngine *geoB, int instance=-1);
    /**
     * @brief resetBB réinitialise la AABB
     */
    void resetBB();
    bool ifNoeudVide();
    /**
     * @brief remplaceBB remplace la AABB
     * @param geo
     */
    void remplaceBB(GeometryEngine *geo);
    /**
     * @brief remplaceBB remplace la AABB
     * @param m
     * @param M
     */
    void remplaceBB(QVector3D m,QVector3D M);
    /**
     * @brief updateBB
     * @param m
     * @param lastM
     * @param courante
     */
    /**
     * @brief updateBB met a jour la AABB avec la matrice de transformation
     * @param m matrice de base
     * @param lastM matrice utilisé dans le cas d'objet instancié
     * @param courante matrice utilisé dans le cas d'objet instancié
     */
    void updateBB(QMatrix4x4 m, QMatrix4x4 lastM =QMatrix4x4(), QMatrix4x4 courante = QMatrix4x4());
    /**
     * @brief ajustBB combine deux AABB
     * @param geo
     */
    void ajustBB(GeometryEngine *geo);
    /**
     * @brief ajustBB combine deux AABB
     * @param min
     * @param max
     */
    void ajustBB(QVector3D min, QVector3D max);

    /**
     * @brief intersect verifie si une intersection a lieu entre l'objet et la AABB du noeud du gameobject
     * @param geo
     * @return
     */
    bool intersect(GeometryEngine *geo);
    /**
     * @brief internintersect verifie si une intersection a lieu entre l'objet et la AABB du mesh du gameobject
     * @param geo
     * @param numInstence lorsque la collision a lieu avec un objet instencié
     * @param AllTransform
     * @return
     */
    bool internintersect(GeometryEngine *geo ,int &numInstence, QMatrix4x4 AllTransform = QMatrix4x4());
    /**
     * @brief internintersectInstenced verifie si une intersection a lieu entre l'objet et la AABB d'une instance du mesh
     * @param geo
     * @param numInstence numero de l'instance
     * @param AllTransform
     * @return
     */
    bool internintersectInstenced(GeometryEngine *geo ,int &numInstence, QMatrix4x4 AllTransform = QMatrix4x4());
    /**
     * @brief gestionCollision une fois la collision detecter, gère la collision AABB vs AABB avec la reflexion
     * @param geo
     * @param vec
     * @return
     */
    QVector3D gestionCollision(GeometryEngine *geo,QVector3D vec);
    /**
     * @brief gestionCollision une fois la collision detecter, gère la collision AABB vs Terrain avec la reflexion
     * @param geo
     * @param vec
     * @return
     */
    QVector3D gestionCollision(QVector3D vec, QVector3D mesh);
    /**
     * @brief gestionCollision une fois la collision detecter, gère la collision AABB vs AABB instenced avec la reflexion
     * @param geo
     * @param vec
     * @return
     */
    QVector3D gestionCollision(GeometryEngine *geo,QVector3D vec, int numInstenced);

    /**
     * @brief mapCoordChanged gère les changement de coordonnée du joueur afin que la carte reste centrée sur le joueur
     * @param vec
     * @param objM
     * @param ourM
     * @return
     */
    QVector3D mapCoordChanged(QVector3D vec,QMatrix4x4 objM,QMatrix4x4 ourM);
    /**
     * @brief addInstancedGrass ajoute un nombre d'instance d'arbre
     * @param ratioArbre devenu inutile
     * @param min
     * @param max
     */
    void addInstancedGrass(float ratioArbre=0.42, QVector3D min=QVector3D(-13,-13,0), QVector3D max=QVector3D(13,13,0));
    /**
     * @brief coordLastCollisionUpdateForMeshsCollision met à jour les coordonnée du dernier impacte lors d'une collision AABB vs AABB
     * @param geo
     * @param objM
     */
    void coordLastCollisionUpdateForMeshsCollision(GeometryEngine *geo, QMatrix4x4 objM);

    /**
     * @brief calcBBMin renvoie le vecteur avec les coordonnée les plus petite entre last et min
     * @param last
     * @param min
     * @return
     */
    static QVector3D  calcBBMin(QVector3D const & last, QVector3D const & min);
    /**
     * @brief calcBBMin renvoie le vecteur avec les coordonnée les plus grande entre last et max
     * @param last
     * @param min
     * @return
     */
    static QVector3D  calcBBMax(QVector3D const & last, QVector3D const & max);
};

#endif // GEOMETRYENGINE_H
