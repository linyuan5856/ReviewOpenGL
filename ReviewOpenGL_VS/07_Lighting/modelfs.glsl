#version 330 core 
out vec4 FragColor;

in vec2  TexCoords;
in vec3 Normal;
in vec3 WorldPos;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 LightColor;

void main(){
    
    vec3 LightDir=normalize(lightPos-WorldPos);
    vec3 normalDir=normalize(Normal);
    vec3 viewDir=normalize(viewPos-WorldPos);

    vec3 albedo=texture(texture_diffuse1, TexCoords).rgb;
    
    vec3 ambient=0.05*albedo*LightColor;

    float diff=max(dot(normalDir,LightDir),0.0);
    vec3 diffuse=diff*albedo;

    vec3 halfDir=normalize(LightDir+normalDir);
    float spec=pow(max(dot(halfDir,viewDir),0),32.0);
    vec3 specular=spec*LightColor*0.3;

    FragColor=vec4(ambient+diffuse+specular,1.0);
}