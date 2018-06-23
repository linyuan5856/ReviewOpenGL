#version 330 core

in VS_OUT{
 vec3 WorldPos;
 vec3 Normal;
 vec2 TexCoords;
 vec4 LightSpacePos;
}fs_in;

out vec4 FragColor;
uniform sampler2D diffuse;
uniform sampler2D depthMap;

uniform vec3 viewPos;
uniform vec3 lightPos;

float CalculateShadow(vec4 lightspacePos){
  vec3 projCoords=lightspacePos.xyz/lightspacePos.w;
   projCoords=projCoords*0.5+0.5;
  float closetDepth=texture(depthMap,projCoords.xy).r;
  float currentDepth=projCoords.z;
  float shadow=currentDepth-0.005>closetDepth?1.0:0.0;
 // shadow=closetDepth;
  return  shadow;
 }

void main(){
    vec3 color = texture(diffuse, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.WorldPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.WorldPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // calculate shadow
    float shadow = CalculateShadow(fs_in.LightSpacePos);
    vec3 lighting = (ambient +  (1.0 - shadow) *(diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);
    //FragColor=vec4(vec3(shadow),1.0);
}