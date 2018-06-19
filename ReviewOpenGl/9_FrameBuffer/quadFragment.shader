#version 330 core
in vec2 TexCoord;
out vec4 outColor;
uniform sampler2D screenTex;

void main(){
vec4 bg=texture(screenTex,TexCoord);

//灰度
float average=0.21*bg.r+0.71*bg.g+0.07*bg.b;
outColor=vec4(average,average,average,1.0);
}