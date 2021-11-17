#version 140

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
    // Calculate vertex position in screen space
    vec4 color = texture2D(texture, a_texcoord);
    if(a_position.z==0){
        gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy , color.x*0.7+a_position.z,1.);
//        gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy, Mandelbrot( sin(a_position.x/10), sin(a_position.y/10))/50,1.);

    }
    else{
        gl_Position = mvp_matrix *camera_matrix* transform_Matrix * a_position;
}
    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
    v_position = vec3(a_position.xy, color.x*1.2);
}
//! [0]
