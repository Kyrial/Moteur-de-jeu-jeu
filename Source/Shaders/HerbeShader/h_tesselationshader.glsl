#version 410 core



layout(triangles, equal_spacing, ccw) in;


uniform mat4 mvp_matrix;
uniform mat4 camera_matrix;
uniform mat4  transform_Matrix;


//uniform sampler2D gDisplacementMap;
//uniform float gDispFactor;

in vec3 v_position_ES_in[];
in vec2 v_texcoord_ES_in[];
in vec3 v_normal_ES_in[];
in vec3 FragPos_ES_in[];

out vec2 v_texcoord;
out vec3 v_position;
out vec3 v_normal;
out vec3 FragPos;
vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main(void)
{

    // Interpolate the attributes of the output vertex using the barycentric coordinates
    v_texcoord = interpolate2D(v_texcoord_ES_in[0], v_texcoord_ES_in[1], v_texcoord_ES_in[2]);
    v_normal = interpolate3D(v_normal_ES_in[0], v_normal_ES_in[1], v_normal_ES_in[2]);
    v_normal = normalize(v_normal);
    FragPos = interpolate3D(FragPos_ES_in[0], FragPos_ES_in[1], FragPos_ES_in[2]);
    //FragPos = interpolate3D(FragPos_ES_in[0]+v_normal_ES_in[0], FragPos_ES_in[1]+v_normal_ES_in[1], FragPos_ES_in[2]+v_normal_ES_in[2]);
    v_position = interpolate3D(v_position_ES_in[0], v_position_ES_in[1], v_position_ES_in[2]);

    // Displace the vertex along the normal
    //float Displacement = texture(gDisplacementMap, v_texcoord.xy).x;
    //v_position += v_normal * Displacement * gDispFactor;
    //FragPos += v_normal*0.1 ;
    gl_Position = mvp_matrix *camera_matrix  * vec4(FragPos, 1.0);
    //FragPos = v_position.xyz;
}
