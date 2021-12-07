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

    void initMesh(std::string filename);
    void initMeshObj(std::string filename);
    void bindMesh(std::vector< std::vector<unsigned int> >  faces);

//        QOpenGLBuffer normalBuf;

    void drawWithNormal(QOpenGLShaderProgram *program);
    void drawCubeGeometry(QOpenGLShaderProgram *program) override;
};

#endif // GEOMETRYMESHENGINE_H
