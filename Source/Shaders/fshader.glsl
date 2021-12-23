#version 410
uniform float animation = 1;
uniform sampler2D texture;
uniform sampler2D textureGrass;
uniform sampler2D textureRock;
uniform sampler2D textureSnow;
uniform sampler2D textureEau;

uniform vec3 lumiere;
uniform vec3 viewPosition;
uniform sampler2D textureScene;
uniform bool textureSample = false;
uniform mat4 mvp_matrix;

in vec2 v_texcoord;
in vec3 v_position;
in vec3 v_normal;
in vec3 FragPos;

out vec4 FragColor;

//! [0]

float max(float a, float b){
    return a>b?a:b;
}
float min(float a, float b){
    return a<b?a:b;
}
/*
float distance(float a, float b){
    if(a<b)
        return b-a;
    else
        return a-b;
}*/

float poid(float a, float b, float intervalle){
    //return max(0.01, 100- distance(a,b)*5);
    return min(1,max(0,1-abs(a-b)/intervalle));
}

vec2 animationEau(int zoom = 4){
    vec2 eaux = vec2(0.,0.);
    eaux.y=  (v_texcoord.y+(animation/8000))/zoom;//+cos((animation/10000+(v_position.y)*100)/40000)/7+(0.5)/7;
    eaux.x = (v_texcoord.x +cos((animation/500))/10)/zoom;
    return eaux;
}

vec4 getLumiere(vec3 fragPosition, float specularStrength=1.,float minDiffusion=0.16){
    vec3 lightDir = normalize(lumiere - fragPosition);
    float diff = max(dot(v_normal, lightDir), minDiffusion);
    vec3 diffuse = diff * vec3(1,1,1);
    vec3 viewDir = normalize(vec4(mvp_matrix * vec4(viewPosition.xyz,1)).xyz - fragPosition);


    vec3 halfwayDir = normalize(lightDir + viewDir);



    vec3 reflectDir = reflect(-lightDir, v_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    //   float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 256);
    vec3 specular = specularStrength * spec * vec3(1,1,1);

    return vec4(diffuse.xyz + specular.xyz,1);
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
    return (poid(position, eau,gapEau)/poids)*texture2D(textureEau, (animationEau(8)+animationEau(4))/2)*getLumiere( FragPos.xyz,5.)+
            (poid(position, herbe,gapHerbe)/poids)*texture2D(textureGrass, texcoord)*getLumiere( FragPos.xyz,0.5)+
            (poid(position, pierre,gapPierre)/poids)*texture2D(textureRock, texcoord)*getLumiere( FragPos.xyz,2.)+
            (poid(position, neige,gapNeige)/poids)*texture2D(textureSnow, texcoord)*getLumiere( FragPos.xyz,5.);

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
        //gl_FragColor =calculTexture(v_position.z,v_texcoord);
        //gl_FragColor =getLumiere( FragPos.xyz)*calculTexture(v_position.z,v_texcoord);
        FragColor =calculTexture(v_position.z,v_texcoord);
    }
    else{

        //gl_FragColor = texture2D(textureScene, v_texcoord);

        FragColor = getLumiere( FragPos.xyz)*texture2D(textureScene, v_texcoord) ;

    }
    //FragColor.xyz = FragColor.xyz - max(distance(viewPosition.xyz,FragPos.xyz)/20,0);




}
//! [0]

