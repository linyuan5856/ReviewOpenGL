#version 330 core

in VS_OUT{
 vec3 WorldPos;
 vec3 Normal;
 vec2 TexCoords;
}frag_in;

out vec4 FragColor;
uniform sampler2D diffuse;

void main(){
FragColor=texture(diffuse,frag_in.TexCoords);
}