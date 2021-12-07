#version 410
uniform float animation = 1;
uniform sampler2D texture;
uniform sampler2D textureFeuille;
uniform sampler2D textureBois;


uniform vec3 lumiere;
uniform vec3 viewPosition;
uniform sampler2D textureScene;
uniform bool textureSample = false;
uniform mat4 mvp_matrix;

in vec2 v_texcoord;
in vec3 v_position;
in vec3 v_normal;
in vec3 FragPos;
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
    return min(1,max(0,1-abs(a-b)/intervalle));
}

vec2 animationEau(){
    return  v_texcoord*cos((animation+(v_position.y)*1000)/10000)/7+(0.5)/7;
}

vec4 getLumiere(vec3 fragPosition){
    vec3 lightDir = normalize(lumiere - fragPosition);
    float diff = max(dot(v_normal, lightDir), 0.35);
    vec3 diffuse = diff * vec3(1,1,1);

    float specularStrength = 0.5;
    vec3 viewDir = normalize(vec4(mvp_matrix * vec4(viewPosition.xyz,1)).xyz - fragPosition);
    vec3 reflectDir = reflect(-lightDir, v_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * vec3(1,1,1);

    return vec4(diffuse.xyz + specular.xyz,1);
}




vec4  calculTexture(float position,vec2 texcoord ){
    float bois = 5.15;
    float feuille = 10.5;

    float gapfeuille = 5.5;
    float gapBois = 5.5;

    float poids = poid(position, bois,gapBois)+ poid(position, feuille,gapfeuille);

    if(position >feuille+gapfeuille)
        return texture2D(textureFeuille, texcoord);
    if(position <bois-gapBois)
        return texture2D(textureBois, texcoord);
    return (poid(position, bois,gapBois)/poids)*texture2D(textureBois, texcoord)+
            (poid(position, feuille,gapfeuille)/poids)*texture2D(textureFeuille, texcoord);

}

void main()
{
    if(textureSample==false){
        gl_FragColor =getLumiere( FragPos.xyz)*calculTexture(v_position.y,v_texcoord);

    }
    else{
        gl_FragColor = getLumiere( FragPos.xyz)*texture2D(textureScene, v_texcoord) ;
    }






}
//! [0]

