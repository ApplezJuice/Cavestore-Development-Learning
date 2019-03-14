#version 460

in vec4 fragColor;

//outputs a vector3 RGB (r,g,b,a)
out vec4 color;

void main(){
    color = fragColor;
}