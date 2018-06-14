#version 330 core
out vec4 finalColor;
in vec2 uv;

uniform sampler2D tex1;

void main(){
 finalColor=texture(tex1,uv);
}