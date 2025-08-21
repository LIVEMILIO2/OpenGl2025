#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 color;
uniform float time;
uniform vec4 outColorAzul;
uniform vec4 outColorVerde;
uniform vec4 outColorRojo;

void main ()
{  
	color = vColor;
	vec4 outPosition = vPosition;
	outPosition.x;// = outPosition.x * cos(time);
	vec4 finalColor = vColor + outColorAzul + outColorRojo +  outColorVerde;
	color = finalColor;
	gl_Position = outPosition; 
