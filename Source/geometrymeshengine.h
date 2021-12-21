#ifndef GEOMETRYMESHENGINE_H
#define GEOMETRYMESHENGINE_H
#include "geometryengine.h"


struct VertexDataWithNormal
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

class GeometryMeshEngine : public GeometryEngine
{
public:
    GeometryMeshEngine();

    void initMesh(std::string filenamen, bool collisionActivated= true, bool centre= false, bool inverse = false);
    void initMeshObj(std::string filename, bool collisionActivated= true, bool centre= false, bool inverse = false);
    void bindMesh(std::vector< std::vector<unsigned int> >  faces, bool a = true, bool centre= false, bool inverse = false);

//        QOpenGLBuffer normalBuf;

    void drawWithNormal(QOpenGLShaderProgram *program);
    void drawCubeGeometry(QOpenGLShaderProgram *program) override;
    QVector3D setNormalToCentreCircle(QVector3D vec, QVector3D centre, bool inverse) override;

};

#endif // GEOMETRYMESHENGINE_H
