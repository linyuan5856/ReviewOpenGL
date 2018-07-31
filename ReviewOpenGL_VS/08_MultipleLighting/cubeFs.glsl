#version 330 core 

struct DirLight{
 vec3 lightDir;
 vec3 lightColor;
};

struct PointLight{
    vec3 lightPos;
    vec3 lightColor;

    float kc;
    float kl;
    float kq;
};

struct SpotLight{
   vec3 lightPos;
   vec3 direction;
   vec3 lightColor;
   float cutoff;

   float kc;
   float kl;
   float kq;
};


out vec4 FragColor;

in vec2  TexCoords;
in vec3  Normal;
in vec3 WorldPos;

uniform sampler2D texture_diffuse1;
uniform vec3 viewPos;


uniform DirLight dirlight;
uniform PointLight pointlight;
uniform SpotLight spotlight;

vec3 CalculateDirLight(vec3 viewDir,vec3 normalDir,vec3 albedo);
vec3 CalculatePointLight(vec3 viewDir,vec3 normalDir,vec3 albedo);
vec3 CalculateSpotLight(vec3 viewDir,vec3 normalDir,vec3 albedo);


void main(){
    vec3 normalDir=normalize(Normal);
    vec3 viewDir=normalize(viewPos-WorldPos);
    vec3 albedo=texture(texture_diffuse1, TexCoords).rgb;
    

    vec3 dirColor=CalculateDirLight(viewDir,normalDir,albedo);
    vec3 pointColor=CalculatePointLight(viewDir,normalDir,albedo);
    vec3 spotColor=CalculateSpotLight(viewDir,normalDir,albedo);

    FragColor=vec4(dirColor+pointColor+spotColor,1.0);
    //FragColor=vec4(pointColor,1.0);
   // FragColor=vec4(spotColor,1.0);
}


vec3 CalculateDirLight(vec3 viewDir,vec3 normalDir,vec3 albedo){
    vec3 LightDir=normalize(-dirlight.lightDir);
    vec3 LightColor=dirlight.lightColor;
    vec3 ambient=0.05*albedo*LightColor;

    float diff=max(dot(normalDir,LightDir),0.0);
    vec3 diffuse=diff*albedo;

    vec3 halfDir=normalize(LightDir+normalDir);
    float spec=pow(max(dot(halfDir,viewDir),0),32.0);
    vec3 specular=spec*LightColor*0.3;
    return ambient+diffuse+specular;
}

vec3 CalculatePointLight(vec3 viewDir,vec3 normalDir,vec3 albedo){
    vec3 LightDir=normalize(pointlight.lightPos-WorldPos);
    vec3 LightColor=pointlight.lightColor;

    vec3 ambient=0.05*albedo*LightColor;

    float diff=max(dot(normalDir,LightDir),0.0);
    vec3 diffuse=diff*albedo;

    vec3 halfDir=normalize(LightDir+normalDir);
    float spec=pow(max(dot(halfDir,viewDir),0),32.0);
    vec3 specular=spec*LightColor*0.3;

    float distance=length(pointlight.lightPos-WorldPos);
    float atten=1.0/(pointlight.kc+pointlight.kl*distance+pointlight.kq*distance*distance);
    return atten*(ambient+diffuse+specular);
}

vec3 CalculateSpotLight(vec3 viewDir,vec3 normalDir,vec3 albedo){
    vec3 LightDir=normalize(spotlight.lightPos-WorldPos);
    vec3 LightColor=spotlight.lightColor;

    vec3 ambient=0.25*albedo*LightColor;

    float theta = dot(LightDir, normalize(-spotlight.direction));

    if(theta>spotlight.cutoff){
      float diff=max(dot(normalDir,LightDir),0.0);
      vec3 diffuse=diff*albedo;

      vec3 halfDir=normalize(LightDir+normalDir);
      float spec=pow(max(dot(halfDir,viewDir),0),32.0);
      vec3 specular=spec*LightColor*0.3;

      float distance=length(spotlight.lightPos-WorldPos);
      float atten=1/(pointlight.kc+pointlight.kl*distance+pointlight.kq*distance*distance);

      return atten*(ambient+diffuse+specular);
    }else{
      return ambient;
    }
}