#version 410


uniform float animation = 1;


uniform mat4 mvp_matrix;
uniform mat4 camera_matrix;
uniform mat4  transform_Matrix;
in vec4 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;
out vec3 v_position;
out vec3 v_normal;
out vec3 FragPos;

uniform sampler2D texture;






int Mandelbrot(float r, float i){
    float ZnR = -0.59;
    float ZnI = -0.46;
    float temporaire;
    int cmp = 0;
    while (pow(ZnR,2) + pow(ZnI,2) < 4 && cmp < 100){
        temporaire = ZnR;
        ZnR = pow(ZnR, 2) - pow(ZnI, 2) + r;
        ZnI = 2 * temporaire * ZnI + i;
        cmp++;
    }
    if (cmp == 100)
        return -1;
    else
        return cmp;
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
   // float s =Rand(vec2(floor(x),floor(y)));
   //  float t =Rand(vec2(floor(x)+1,floor(y)));
  //   float u =Rand(vec2(floor(x),floor(y)+1));
   // float v =Rand(vec2(floor(x)+1,floor(y)+1));

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


vec3 getNormal(vec3 pt){
   vec3 A = vec3(pt.xy,perlin2d(pt.x,pt.y  , 8)-.3)*2;
   vec3 B = vec3(pt.x+0.1,pt.y,perlin2d(pt.x+0.1,pt.y  , 8)-.3)*2;
   vec3 C = vec3(pt.x,pt.y+0.1,perlin2d(pt.x,pt.y+0.1  , 8)-.3)*2;
   return normalize(cross(B - A, C - A));
}


//! [0]
void main()
{
    float hauteurTexture;
 /*z   vec4 color = texture2D(texture, a_texcoord);

    float hauteurMesh = (perlin2d(a_position.x,a_position.y  , 8)-.3)*2;//+a_position.z;//color.x*0.7+a_position.z;
    float hauteurTexture = hauteurMesh;//max(-0.5, min(1.25,color.x*2)-0.25);

    // Calculate vertex position in screen space
    float hauteurEau =-0.1+cos((animation+(a_position.y)*300)/100)/65;
    if(a_position.z==0){
        if(hauteurMesh<hauteurEau){//if(hauteurTexture<-0.1){
            hauteurMesh = hauteurEau;//+(0.5)/8;
            //v_texcoord = a_texcoord*cos((animation+(a_position.y)*1000)/10000)/7+(0.5)/7;
            v_normal = vec3(0,0,1);
        }
        else
            v_normal = getNormal(a_position.xyz); // normalize(vec3(gl_NormalMatrix * gl_Normal));


        //gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy , hauteurMesh,1.);

        FragPos = vec3(transform_Matrix * vec4(a_position.xy,hauteurMesh, 1.0));
        //        gl_Position = mvp_matrix*camera_matrix* transform_Matrix * vec4(a_position.xy, Mandelbrot( sin(a_position.x/10), sin(a_position.y/10))/50,1.);



    }
    else{*/
        //gl_Position = mvp_matrix *camera_matrix* transform_Matrix * a_position;
        hauteurTexture = a_position.z;
        v_normal = getNormal(a_position.xyz);// normalize(vec3(gl_NormalMatrix * gl_Normal));
        FragPos = vec3(transform_Matrix * vec4(a_position.xyz, 1.0));
    //}
    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces


    v_texcoord = a_texcoord;
    v_position = vec3(a_position.xy, hauteurTexture);
}
//! [0]
