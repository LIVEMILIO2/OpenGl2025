#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 color;
uniform float time;

void main ()
{  
	color = vColor;
	vec4 outPosition = vPosition;
	outPosition.x = outPosition.x * cos(time);
	gl_Position = outPosition / 2.0;  //equivale a hacer return gl_Position
}
