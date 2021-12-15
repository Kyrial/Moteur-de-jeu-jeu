#include "geometryui.h"

geometryUI::geometryUI()
{
GeometryMeshEngine();
}


void geometryUI::initLifeBar(){
    VertexData vertices[] = {
        // Vertex data for face 0

        {QVector3D(-1.0f, -0.0f,  0.1f), QVector2D(1.0f, 0.0f)},  // v2
        {QVector3D(-1.0f, -0.0f,  -0.1f), QVector2D(1.0f, 0.0f)},

        {QVector3D(0.0f, -0.0f,  0.1f), QVector2D(0.5f, 0.0f)},  // v2
        {QVector3D(0.0f, -0.0f,  -0.1f), QVector2D(0.5, 0.0f)}, // v3

        {QVector3D(1.0f, -0.0f,  0.1f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(1.0f, -0.0f,  -0.1f), QVector2D(0.0f, 0.0f)} // v1
        }; // v3



        unsigned int indexCount = 7; //Careful update indicesNumber when creating new geometry
        GLushort indices[] = {
            0,  1,  2,  3,  4,  5, 5     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        };

        arrayBuf.bind();
        arrayBuf.allocate(vertices, 6 * sizeof(VertexData));
        arrayBuf.release();
        // Transfer index data to VBO 1
        indexBuf.bind();
        indexBuf.allocate(indices,  ((indexCount)* sizeof(GLushort)));
        //  std::cout << indexBuf.size() << " index count " << indexCount <<"sizeof" <<  sizeof(GLushort) << std::endl;
        indexBuf.release();
    }
bool geometryUI::updateLifeBar(double deltaTime){
    vie = vie -deltaTime/500.0;
    if (vie<0) vie = 0;
    float pourcentage = 1-2*vie/100.0;
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -0.0f,  0.1f), QVector2D(1.0f, 0.0f)},  // v2
        {QVector3D(-1.0f, -0.0f,  -0.1f), QVector2D(1.0f, 0.0f)},

        {QVector3D(pourcentage, -0.0f,  0.1f), QVector2D(0.5f, 0.0f)},  // v2
        {QVector3D(pourcentage, -0.0f,  -0.1f), QVector2D(0.5, 0.0f)}, // v3

        {QVector3D(1.0f, -0.0f,  0.1f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(1.0f, -0.0f,  -0.1f), QVector2D(0.0f, 0.0f)} // v1
        }; // v3



        unsigned int indexCount = 7; //Careful update indicesNumber when creating new geometry
        GLushort indices[] = {
            0,  1,  2,  3,  4,  5, 5     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        };

        arrayBuf.bind();
        arrayBuf.allocate(vertices, 6 * sizeof(VertexData));
        arrayBuf.release();
        // Transfer index data to VBO 1
        indexBuf.bind();
        indexBuf.allocate(indices,  ((indexCount)* sizeof(GLushort)));
        //  std::cout << indexBuf.size() << " index count " << indexCount <<"sizeof" <<  sizeof(GLushort) << std::endl;
        indexBuf.release();

        return true;
    }
