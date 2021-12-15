#include "billboardobject.h"


void billboardObject::updateScene(double deltaTime, QMatrix4x4 m){
    /*CameraRight_worldspace = {ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]}
    CameraUp_worldspace = {ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]}

    vec3 vertexPosition_worldspace =
        particleCenter_wordspace
        + CameraRight_worldspace * squareVertices.x * BillboardSize.x
        + CameraUp_worldspace * squareVertices.y * BillboardSize.y;

    // The VBO containing the 4 vertices of the particles.
     static const GLfloat g_vertex_buffer_data[] = {
     -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
     };*/
   // geo->test();
    UpdatebarreDeVie( deltaTime);
     Object::updateScene(deltaTime, m);
}


bool billboardObject::UpdatebarreDeVie(double deltaTime){
    geo->updateLifeBar(deltaTime);

    return vie >0;
}
