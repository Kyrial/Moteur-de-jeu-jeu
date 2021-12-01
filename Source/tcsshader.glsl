#version 410
#extension GL_ARB_tessellation_shader : enable

layout(vertice = 3) out;

uniform vec3 gEyeWorldPos;
in vec3 v_position_in[];
in vec2 v_texcoord_in[];

out vec3 v_position_in[];
out vec2 v_texcoord_in[];

float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;

    if (AvgDistance <= 2.0) {
        return 10.0;
    }
    else if (AvgDistance <= 5.0) {
        return 7.0;
    }
    else {
        return 3.0;
    }
}

void main(void)
{
    //gl_InvocationID
    v_positionOut[gl_InvocationID] = v_positionOut[gl_InvocationID];

       // Calculate the tessellation levels
       gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
       gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
       gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
       gl_TessLevelInner[0] = gl_TessLevelOuter[2];
   }

}
