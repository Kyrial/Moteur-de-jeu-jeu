#version 140

uniform float animation = 1;

uniform mat4 mvp_matrix;
uniform mat4 camera_matrix;
uniform mat4  transform_Matrix;
in vec4 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;
out vec3 v_position;

uniform sampler2D texture;



int Mandelbrot(float r, float i){
    float ZnR = -0.59;
    float ZnI = -0.46;
    float temporaire;
    int cmp = 0;
    while (pow(ZnR,2) + pow(ZnI,2) < 4 && cmp < 100){
        temporaire = ZnR;

        ZnR = pow(ZnR, 2) - pow(ZnI, 2) + r;
        ZnI = 2 * temporaire * ZnI + i;
        cmp++;
    }
    if (cmp == 100)
        return -1;
    else
        return cmp;
}




//! [0]
void main()
{
    vec4 color = texture2D(texture, a_texcoord);

   float hauteurTexture = max(-0.5, min(1.25,color.x*2)-0.25);
   float hauteurMesh = color.x*0.7+a_position.z;

    // Calculate vertex position in screen space

    if(a_position.z==0){
        if(hauteurTexture<-0.1){
            hauteurMesh = 0.1*cos((animation+(a_position.y)*300)/100)/8+(0.5)/8;
            //v_texcoord = a_texcoord*cos((animation+(a_position.y)*1000)/10000)/7+(0.5)/7;
        }



        gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy , hauteurMesh,1.);
//        gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy, Mandelbrot( sin(a_position.x/10), sin(a_position.y/10))/50,1.);
    ///**cos(animation/200)*/


    }
    else{
        gl_Position = mvp_matrix *camera_matrix* transform_Matrix * a_position;

}
    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces

    v_texcoord = a_texcoord;
    v_position = vec3(a_position.xy, hauteurTexture);
}
//! [0]
