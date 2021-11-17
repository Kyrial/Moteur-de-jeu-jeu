#version 140

uniform sampler2D texture;
uniform sampler2D textureGrass;
uniform sampler2D textureRock;
uniform sampler2D textureSnow;


uniform sampler2D textureScene;
uniform bool textureSample = false;

in vec2 v_texcoord;
in vec3 v_position;
//! [0]

float max(float a, float b){
    return a>b?a:b;
}
float min(float a, float b){
    return a<b?a:b;
}

float distance(float a, float b){
    if(a<b)
        return b-a;
    else
        return a-b;
}


void main()
{
    // Set fragment color from texture
    //gl_FragColor = vec4(1., 1.,1.,1.)*texture2D(texture, v_texcoord);
//     gl_FragColor = vec4(v_position.z, 0.,0.,1.);//*texture2D(texture, v_texcoord);

   /* if(v_position.z<0.2)
        gl_FragColor = texture2D(textureGrass, v_texcoord);
    if(v_position.z<0.4)
        gl_FragColor = texture2D(textureRock, v_texcoord);
    else
        gl_FragColor = vec4(1., 1.,1.,1.)*texture2D(textureSnow, v_texcoord);

*/
    if(textureSample==false){
        gl_FragColor = min(1,max(v_position.z*9-4.,0))*texture2D(textureSnow, v_texcoord)+
            min(1,max(1-v_position.z*2.6,0))*texture2D(textureGrass, v_texcoord)+
            min(1,max(1-distance(v_position.z,0.4)*4.5,0))*texture2D(textureRock, v_texcoord);
}
    else{
        gl_FragColor = texture2D(textureScene, v_texcoord);
    }
   /*gl_FragColor =0*texture2D(textureSnow, v_texcoord)+
            0*texture2D(textureGrass, v_texcoord)+
            1*texture2D(textureRock, v_texcoord);*/





}
//! [0]

