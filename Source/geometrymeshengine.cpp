#include "geometrymeshengine.h"

GeometryMeshEngine::GeometryMeshEngine()
{
    GeometryEngine();
}


void GeometryMeshEngine::initMeshObj(std::string filename, bool collisionActivated, bool centre, bool inverse){

    std::vector< std::vector<unsigned int> >  faces;

    OBJIO::open(filename, vertex, faces, true);
    bindMesh(faces,collisionActivated, centre, inverse);
}

void GeometryMeshEngine::initMesh(std::string filename,  bool collisionActivated, bool centre, bool inverse ){

    std::vector< std::vector<unsigned int> >  faces;

    OFFIO::open(filename, vertex, faces, true);
   // qDebug("avant");
    bindMesh(faces,collisionActivated,  centre, inverse);
   // qDebug("après");
}
void GeometryMeshEngine::bindMesh(std::vector< std::vector<unsigned int> >  faces, bool collisionActivated, bool centre, bool inverse){
//qDebug("0.0");
    unsigned int vertexNumber = vertex.size();
    VertexDataWithNormal vertices[vertexNumber];
    VertexData vertices2[vertexNumber];
    unsigned int indexCount = faces.size()*3;
    GLushort indices[indexCount];

    QVector3D normals[vertexNumber];
    //normalBuf
    //int face=0;
    QVector3D normal;
//qDebug("0.5");

    if(centre)
        for(int i=0; i<vertexNumber;i++)
            normals[i]=setNormalToCentreCircle(vertex[i], QVector3D(0,0,0), inverse);
    qDebug("1");
    for(int i=0; i<indexCount;i+=3) {
        indices[i]= faces[i/3][0];
        indices[i+1]= faces[i/3][1];
        indices[i+2]= faces[i/3][2];
        if(!centre){
            normal = QVector3D::normal(vertex[faces[i/3][0]],vertex[faces[i/3][1]],vertex[faces[i/3][2]]);

            for(int k = 0; k<3;k++){

                if(normals[faces[i/3][k]] != QVector3D())
                    normals[faces[i/3][k]]= (normals[faces[i/3][k]]+normal);
                else
                    normals[faces[i/3][k]]= normal;

            }
        }
        //.normalized()
    }
  //  qDebug("2");

    /* for(int i =0; i< indexCount;i++){
        normals[i] = normals[i].normalized();
    }*/

    for(int i=0; i<vertexNumber;i++) {
        vertices[i]= {vertex[i], QVector2D((2+vertex[i][0]+vertex[i][2])*precisionTexture, (2+vertex[i][1]+vertex[i][2])*precisionTexture),normals[i].normalized()};
        vertices2[i]= {vertex[i], QVector2D((vertex[i][0]+vertex[i][1])*precisionTexture, (vertex[i][0]+vertex[i][2])*precisionTexture)};
    }




    qDebug("vertexNumber :%i, et indexCount = %i \n ",vertexNumber, indexCount );
    if(collisionActivated)
        initBB(vertex);
    else{
        Min = QVector3D(0,0,0);
        Max = QVector3D(0,0,0);
        noCollision = true;
    }
   // qDebug("3");

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    if (withNormal)
        arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexDataWithNormal));
    else
        arrayBuf.allocate(vertices2, vertexNumber * sizeof(VertexData));
    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  ((indexCount)* sizeof(GLushort)));

    // normalBuf.bind();
    // normalBuf.allocate(normals, vertexNumber * sizeof(QVector3D));

    triangle_strip = 2;

    //      normalBuf
}

void GeometryMeshEngine::drawCubeGeometry(QOpenGLShaderProgram *program){
    if(withNormal)
        drawWithNormal(program);
    else
        GeometryEngine::drawCubeGeometry(program);
}

void GeometryMeshEngine::drawWithNormal(QOpenGLShaderProgram *program)
{
    //   std::cout << indexBuf.size() << " , meow " <<   std::endl;
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();
    //normalBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexDataWithNormal));//+sizeof(QVector3D));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexDataWithNormal));//+sizeof(QVector3D));


    offset += sizeof(QVector2D);
    // offset = 0;

    int texNormalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(texNormalLocation);
    program->setAttributeBuffer(texNormalLocation, GL_FLOAT, offset, 3,sizeof(VertexDataWithNormal));

    // Draw cube geometry using indices from VBO 1
    int size = (int)indexBuf.size();
    // std::cout << indexBuf.size() << " , meow " <<  size << std::endl;

    int MaxPatchVertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
    // printf("Max supported patch vertices %d\n", MaxPatchVertices);
    glPatchParameteri(GL_PATCH_VERTICES, 3);


    if(triangle_strip==0){
        glDrawElements(GL_TRIANGLE_STRIP, size/2, GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
        //glDrawElements(GL_PATCHES, size/2, GL_UNSIGNED_SHORT, 0);
        //glDrawArrays( GL_PATCHES, 0, size/2 );
    }
    else{  if(triangle_strip == 1)
            glDrawElements(GL_TRIANGLES, size/2, GL_UNSIGNED_SHORT, 0);
        else
            glDrawElements(GL_PATCHES, size/2, GL_UNSIGNED_SHORT, 0);
    }

    //glDrawElementsInstanced(GL_TRIANGLES, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
}
QVector3D GeometryMeshEngine::setNormalToCentreCircle(QVector3D vec, QVector3D centre, bool inverse){
    if(!inverse)
        return   vec - centre;
    else return  centre - vec;
}
