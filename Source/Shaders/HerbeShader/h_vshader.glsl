#version 410


uniform float animation = 1;


uniform mat4 mvp_matrix;
uniform mat4 camera_matrix;
uniform mat4  transform_Matrix;
in vec4 a_position;
in vec2 a_texcoord;
in vec3 a_normal;
out vec2 v_texcoord;
out vec3 v_position;
out vec3 v_normal;
out vec3 FragPos;
uniform sampler2D texture;

//! [0]
void main()
{

    //gl_Position = mvp_matrix *camera_matrix* transform_Matrix * a_position;

    FragPos = vec3(transform_Matrix * vec4(a_position.xyz, 1.0));

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces

    v_texcoord = a_texcoord;
    v_position = vec3(a_position.xyz);
    // v_position = vec3(transform_Matrix * vec4(a_position.xyz, 1.0));
    v_normal = a_normal;// getNormal(a_position.xyz);// normalize(vec3(gl_NormalMatrix * gl_Normal));

}
//! [0]
