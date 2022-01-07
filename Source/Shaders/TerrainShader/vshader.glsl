#version 410


uniform float animation = 1;


uniform mat4 mvp_matrix;
uniform mat4 camera_matrix;
uniform mat4  transform_Matrix;
in vec4 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;
out vec3 v_position;
out vec3 v_normal;
out vec3 FragPos;

uniform sampler2D texture;




//! [0]
void main()
{
    float hauteurTexture;
    /*z   vec4 color = texture2D(texture, a_texcoord);

    float hauteurMesh = (perlin2d(a_position.x,a_position.y  , 8)-.3)*2;//+a_position.z;//color.x*0.7+a_position.z;
    float hauteurTexture = hauteurMesh;//max(-0.5, min(1.25,color.x*2)-0.25);

    // Calculate vertex position in screen space
    float hauteurEau =-0.1+cos((animation+(a_position.y)*300)/100)/65;
    if(a_position.z==0){
        if(hauteurMesh<hauteurEau){//if(hauteurTexture<-0.1){
            hauteurMesh = hauteurEau;//+(0.5)/8;
            //v_texcoord = a_texcoord*cos((animation+(a_position.y)*1000)/10000)/7+(0.5)/7;
            v_normal = vec3(0,0,1);
        }
        else
            v_normal = getNormal(a_position.xyz); // normalize(vec3(gl_NormalMatrix * gl_Normal));


        //gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy , hauteurMesh,1.);

        FragPos = vec3(transform_Matrix * vec4(a_position.xy,hauteurMesh, 1.0));
        //        gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy, Mandelbrot( sin(a_position.x/10), sin(a_position.y/10))/50,1.);


    }
    else{*/
    //gl_Position = mvp_matrix *camera_matrix* transform_Matrix * a_position;
    hauteurTexture = a_position.z;
    v_normal = vec3(0,0,0) ;//;getNormal(a_position.xyz);// normalize(vec3(gl_NormalMatrix * gl_Normal));
    FragPos = vec3(transform_Matrix * vec4(a_position.xyz, 1.0));
    //}
    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces


    v_texcoord = a_texcoord;
    v_position = vec3(a_position.xy, hauteurTexture);
}
//! [0]
