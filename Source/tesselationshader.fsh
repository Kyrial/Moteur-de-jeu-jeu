#version 410 core



layout(triangles, equal_spacing, ccw) in;

uniform mat4 gVP;
uniform sampler2D gDisplacementMap;
uniform float gDispFactor;

in vec3 v_position_in[];
in vec2 v_texcoord_in[];
//in vec3 Normal_ES_in[];

out vec2 v_texcoord;
out vec3 v_position;
//out vec3 Normal_FS_in;


void main(void)
{
    void main()
    {
        // Interpolate the attributes of the output vertex using the barycentric coordinates
        v_texcoord = interpolate2D(TexCoord_ES_in[0], TexCoord_ES_in[1], TexCoord_ES_in[2]);
        //Normal_FS_in = interpolate3D(Normal_ES_in[0], Normal_ES_in[1], Normal_ES_in[2]);
        //Normal_FS_in = normalize(Normal_FS_in);
        v_position = interpolate3D(WorldPos_ES_in[0], WorldPos_ES_in[1], WorldPos_ES_in[2]);
}
