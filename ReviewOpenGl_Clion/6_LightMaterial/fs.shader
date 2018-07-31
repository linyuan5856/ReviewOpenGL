#version 330 core
out vec4 finalColor;
in vec2 uv;
in vec3 normal;
in vec3 worldPos;


struct Material{
sampler2D diffuse;
sampler2D  specular;
float shininess;
};

struct Light{
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main(){
    vec3 lightDir=normalize(light.position-worldPos);
    vec3 viewDir=normalize(viewPos-worldPos);
    vec3 normalDir=normalize(normal);

    vec3 albedo=texture(material.diffuse,uv).rgb;

    vec3 ambient = light.ambient * albedo;

    float diff=dot(normalDir,lightDir)*0.5f+0.5f;
    vec3 diffuse=diff*light.diffuse*albedo;

    vec3 reflectDir=reflect(viewDir,normalDir);
    float spec=pow(max(dot(reflectDir,lightDir),0.0f),material.shininess);
    vec3 specularMask=texture(material.specular,uv).rgb;
    vec3 specular=light.specular*spec*albedo*specularMask;

     vec3 color=ambient+diffuse+specular;
    finalColor=vec4(color,1.0f);
}