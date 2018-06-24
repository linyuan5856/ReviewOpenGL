#version 330 core

in VS_OUT{
 vec3 WorldPos;
 vec3 Normal;
 vec2 TexCoords;
}fs_in;

out vec4 FragColor;
uniform sampler2D diffuse;
uniform samplerCube depthMap;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform float far_plane;

float CalculateShadow(vec3 fragPos){
   vec3 fragToLight = fragPos - lightPos;
   float closestDepth = texture(depthMap, fragToLight).r;
   closestDepth *= far_plane;
   float currentDepth = length(fragToLight);
   float bias = 0.05;
   float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
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
    float shadow = CalculateShadow(fs_in.WorldPos);
    vec3 lighting = (ambient +  (1.0 - shadow) *(diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);

//    vec3 fragToLight = fs_in.WorldPos - lightPos;
//    float closestDepth = texture(depthMap, fragToLight).r;
//    FragColor=vec4(vec3(closestDepth),1.0);
}