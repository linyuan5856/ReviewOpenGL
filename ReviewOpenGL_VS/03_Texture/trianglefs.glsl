#version 330 core 
out vec4 FragColor;

in vec2  TexCoords;
in vec3 Normal;
uniform sampler2D diffuse;
void main(){
    FragColor=texture(diffuse,TexCoords);
}