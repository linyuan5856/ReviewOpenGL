#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUv;

out vec2 uv;
out vec3 normal;
out vec3 worldPos;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(){
gl_Position=P*V*M*vec4(aPos,1.0);
uv=aUv;
normal=aNormal;
worldPos=vec3(M*vec4(aPos,1.0));
}