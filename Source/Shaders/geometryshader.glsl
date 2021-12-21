#version 410
layout (triangles) in;
layout (triangle_strip, max_vertices = 9) out;

uniform float animation = 1;


uniform mat4 mvp_matrix;
uniform mat4 camera_matrix;
uniform mat4  transform_Matrix;

in vec2 g_texcoord[];
in vec3 g_position[];
in vec3 g_normal[];
in vec3 g_FragPos[];


out vec2 v_texcoord;
out vec3 v_position;
out vec3 v_normal;
out vec3 FragPos;

uniform sampler2D texture;



void initTriangle(){
    for(int index = 0; index<3; index++){
        v_texcoord = g_texcoord[index];
        v_position = g_position[index];
        v_normal = g_normal[index];
        FragPos = g_FragPos[index];
        gl_Position =  gl_in[index].gl_Position;
        EmitVertex();

    }
}

void GenerateLine(int index)
{
    v_texcoord = g_texcoord[index];
    v_position = vec3(g_position[index].xy,1);
    v_normal = g_normal[index];
    FragPos = g_FragPos[index];
    gl_Position =  gl_in[index].gl_Position*2;
    EmitVertex();
}

void generatePoint(vec4 v)
{
    v_texcoord = g_texcoord[0];
    v_position =g_position[0] ;// vec3(g_position[0].xy,1);
    v_normal = g_normal[0];
    FragPos = g_FragPos[0];
    if(g_position[0].z >-0.04 && 0.029- g_position[0].z/10>0 ){
   /*     gl_Position =  mvp_matrix *camera_matrix* transform_Matrix*(vec4( v_position.xyz,1.));
        EmitVertex();
        gl_Position =  mvp_matrix *camera_matrix* transform_Matrix*(vec4( v_position.xyz,1.));
        EmitVertex();*/
        gl_Position =  mvp_matrix *camera_matrix* transform_Matrix*(vec4( v_position.xyz,1.)+vec4(0.,cos((animation+(g_position[0].y)*300)/200)/75,0.035-(g_position[0].z/11),0.));
        EmitVertex();
        gl_Position =  mvp_matrix *camera_matrix* transform_Matrix*(vec4( v_position.xyz,1.)+vec4(0.,cos(0.5+(animation+(g_position[0].y)*300)/200)/60,0.05-(g_position[0].z/11),0.));
        EmitVertex();
     /*   gl_Position =  mvp_matrix *camera_matrix* transform_Matrix*(vec4( v_position.xyz,1.)+vec4(cos(0.5+(animation+(g_position[0].y)*300)/200)/100,0.0,0.04-(g_position[0].z/11),0.));
        EmitVertex();
        gl_Position = gl_in[2].gl_Position;
        EmitVertex();*/
    }
    v_position = vec3(g_position[0].xy,0.01);

}


void main(void){
    /*  v_texcoord = g_texcoord[0];
     v_position = g_position[0];
     v_normal = g_normal[0];
     FragPos = g_FragPos[0];*/

    initTriangle();
    generatePoint(vec4(0.,0.,10000.,0.));
    //GenerateLine(0);
    //GenerateLine(1);


    EndPrimitive();

}
