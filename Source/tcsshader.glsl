#version 150
#extension GL_ARB_tessellation_shader : enable

layout(vertice = 3) out;


in vec3 v_position[];

in vec3 v_positionOut[];

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
    v_positionOut[gl_InvocationID] = v_positionOut[0];
}
