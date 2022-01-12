#ifndef GEOMETRYMESHENGINE_H
#define GEOMETRYMESHENGINE_H
#include "geometryengine.h"


struct VertexDataWithNormal
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};
/**
* @file
* @brief le fichier contient la classe GeometryMeshEngine qui effectue toute les actions en rapport aux maillage importer
*/

/**
* @brief la classe GeometryMeshEngine effectue toute les actions en rapport aux maillage importer
*/
class GeometryMeshEngine : public GeometryEngine
{
public:
    GeometryMeshEngine();
    /**
     * @brief initMesh charge un fichier .off et appelle bindMesh
     * @param filename[in] nom du fichier
     * @param collisionActivated[in] bouleen determinant si l'objet subit les collisions
     * @param centre boolean permet de modifier la direction de la normal ( pour les spheres)
     * @param inverse si centre a True, determine l'orientation de la normal
     */
    void initMesh(std::string filename, bool collisionActivated= true, bool centre= false, bool inverse = false);
    void initMeshObj(std::string filename, bool collisionActivated= true, bool centre= false, bool inverse = false);
    void bindMesh(std::vector< std::vector<unsigned int> >  faces, bool a = true, bool centre= false, bool inverse = false);


    std::vector<QVector2D>  textures;
    std::vector< std::vector<unsigned int> >  indicesTextures;

//        QOpenGLBuffer normalBuf;

    void drawWithNormal(QOpenGLShaderProgram *program);
    void drawCubeGeometry(QOpenGLShaderProgram *program) override;
    QVector3D setNormalToCentreCircle(QVector3D vec, QVector3D centre, bool inverse) override;

};

#endif // GEOMETRYMESHENGINE_H
