#version 460 core
layout (location = 0) in vec2 pos; 
varying vec2 vPos;

void main()
{

    gl_Position = vec4(pos.xy, 0.0, 1.0);

    //posisi titik tengah
    vPos = pos.xy;

}