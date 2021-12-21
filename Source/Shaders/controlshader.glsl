#version 410
//#extension GL_ARB_tessellation_shader : enable
// define the number of CPs in the output patch
layout(vertices = 3) out;

uniform vec3 viewPosition;

in vec3 v_position[];
in vec2 v_texcoord[];
in vec3 v_normal[];
in vec3 FragPos[];
out vec3 v_position_ES_in[];
out vec2 v_texcoord_ES_in[];
out vec3 v_normal_ES_in[];
out vec3 FragPos_ES_in[];

float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;
/*
    if (AvgDistance <= 3) {
        return 32.0;
    }
    else if (AvgDistance <= 6) {
        return 16;
    }
    else  if (AvgDistance <= 9) {
        return 8;
    }
    else {
        return 1.0;
    }
*/
    //return min(32,(max(1, 16- pow(log(AvgDistance),2)-AvgDistance/3)));
    return min(32,(max(1, 16- sqrt(AvgDistance*7))));

}

void main(void)
{
    //gl_InvocationID
    v_position_ES_in[gl_InvocationID] = v_position[gl_InvocationID];
    v_texcoord_ES_in[gl_InvocationID] = v_texcoord[gl_InvocationID];
    v_normal_ES_in[gl_InvocationID] = v_normal[gl_InvocationID];
    FragPos_ES_in[gl_InvocationID] = FragPos[gl_InvocationID];

    // Calculate the distance from the camera to the three control points
    float EyeToVertexDistance0 = distance(viewPosition, FragPos[0]);
    float EyeToVertexDistance1 = distance(viewPosition, FragPos[1]);
    float EyeToVertexDistance2 = distance(viewPosition, FragPos[2]);
    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
    gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);


    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}

