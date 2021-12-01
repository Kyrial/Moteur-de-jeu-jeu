#version 410
uniform float animation = 1;
uniform sampler2D texture;
uniform sampler2D textureGrass;
uniform sampler2D textureRock;
uniform sampler2D textureSnow;
uniform sampler2D textureEau;


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

float poid(float a, float b, float intervalle){
    //return max(0.01, 100- distance(a,b)*5);
    return min(1,max(0,1-abs(a-b)/intervalle));
}

vec2 animationEau(){
    return  v_texcoord*cos((animation+(v_position.y)*1000)/10000)/7+(0.5)/7;
}

vec4  calculTexture(float position,vec2 texcoord ){
    float herbe = 0.15;
    float pierre = 0.5;
    float neige = 1.1;
    float eau = -0.5;

    float gapHerbe = 0.25;
    float gapPierre = 0.35;
    float gapNeige = 0.5;
    float gapEau = 0.5;


    float poids = poid(position, herbe,gapHerbe)+ poid(position, pierre,gapPierre)+ poid(position, neige,gapNeige) + poid(position, eau,gapEau);

    if(position >neige+gapNeige)
        return texture2D(textureSnow, texcoord);
    if(position <eau-gapEau)
        return texture2D(textureEau, texcoord);
    return (poid(position, eau,gapEau)/poids)*texture2D(textureEau, animationEau())+
            (poid(position, herbe,gapHerbe)/poids)*texture2D(textureGrass, texcoord)+
            (poid(position, pierre,gapPierre)/poids)*texture2D(textureRock, texcoord)+
            (poid(position, neige,gapNeige)/poids)*texture2D(textureSnow, texcoord);

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
        //  gl_FragColor = min(1,max(v_position.z*9-4.,0))*texture2D(textureSnow, v_texcoord)+
        //       min(1,max(1-v_position.z*2.6,0))*texture2D(textureGrass, v_texcoord)+
        //      min(1,max(1-distance(v_position.z,0.4)*4.5,0))*texture2D(textureRock, v_texcoord);
        gl_FragColor =calculTexture(v_position.z,v_texcoord );
    }
    else{
        gl_FragColor = texture2D(textureScene, v_texcoord);
    }
    /*gl_FragColor =0*texture2D(textureSnow, v_texcoord)+
            0*texture2D(textureGrass, v_texcoord)+
            1*texture2D(textureRock, v_texcoord);*/





}
//! [0]

