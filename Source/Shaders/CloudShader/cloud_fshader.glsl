#version 410
uniform float animation = 1;
uniform sampler2D texture;
//uniform sampler2D textureFeuille;
//uniform sampler2D textureBois;


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

float distance(float a, float b){
    if(a<b)
        return b-a;
    else
        return a-b;
}

float poid(float a, float b, float intervalle){
    return min(1,max(0,1-abs(a-b)/intervalle));
}





int SEED = 0;

int hash[256] = int[](208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                         185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                         9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                         70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                         203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                         164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                         228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                         232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                         193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                         101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                         135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                         114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219);

int noise2(int x, int y, int seed = SEED)
{
    int yindex = (y + seed) % 256;
    if (yindex < 0) {
        yindex += 256;
    }
    int  xindex = (hash[yindex] + x) % 256;
    if (xindex < 0) {
        xindex += 256;
    }
    return int (hash[xindex]);
}

float Rand(vec2 co){
    //return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
    float value = sin(dot(co ,vec2(12.9898,78.233))) * 43758.5453;
    return value - floor(value);
}


float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}
float noise2D(float x, float y){
    float s =noise2(int(floor(x)),int(floor(y)));
    float t =noise2(int(floor(x)+1),int(floor(y)));
    float u =noise2(int(floor(x)),int(floor(y)+1));
    float v =noise2(int(floor(x)+1),int(floor(y)+1));

    float low = smooth_inter(s, t, x-floor(x));
    float high = smooth_inter(u, v, x-floor(x));
    return smooth_inter(low, high, y-floor(y));
}

float perlin2d(float x, float y , int depth)
{
    float xa = x*0.3;
    float ya = y*0.3;
    float amp = 1;
    float fin = 0;
    float div = 0.0;
    //div += 256;
    int i;
    for(i=0; i<depth; i++)
    {
        //div += 256*(amp);
        div+=255*amp;
        fin += noise2D(xa, ya) * amp;
        amp /= 10;//2/pow(2,depth+1);
        xa *= 20;
        ya *= 20;
    }

    return fin/div;
}

















vec2 animationEau(){
    return  v_texcoord*cos((animation+(v_position.y)*1000)/10000)/7+(0.5)/7;
}

vec4 getLumiere(vec3 fragPosition, float specularStrength=1.,float minDiffusion=0.4){
    vec3 lightDir = normalize(lumiere - fragPosition);
    float diff = max(dot(v_normal, lightDir), minDiffusion);
    vec3 diffuse = diff * vec3(1,1,1);
    vec3 viewDir = normalize(vec4(mvp_matrix * vec4(viewPosition.xyz,1)).xyz - fragPosition);


    vec3 halfwayDir = normalize(lightDir + viewDir);



    vec3 reflectDir = reflect(-lightDir, v_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    //   float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 256);
    vec3 specular =  specularStrength * spec * vec3(1,1,1);

    return vec4(diffuse.xyz + specular.xyz,1);
}



void main()
{

        //vec4 color = getLumiere( FragPos.xyz)*texture2D(textureScene, v_texcoord);

    vec4 color = vec4(0.8,0.8,0.8,1);
    color.a = (perlin2d(FragPos.x/2+animation/1000,FragPos.y/2+animation/1000 , 2)-0.5)+(perlin2d(FragPos.x/4+animation/1000,FragPos.y/4+animation/1000 , 2)-0.4);
        //discard
        FragColor = color ;

    }


//! [0]

