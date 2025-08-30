#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTextCoord;

out vec2 texCoord;
out vec4 textureHeight;

uniform float time;
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 accumTrans;
uniform sampler2D HeightMap;


float Luminosity(vec4 color)
{
	return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

void main()
{
	vec4 newPosition = vPosition;
	//float L = ()
	texCoord = vTextCoord;
	textureHeight = texture(HeightMap, texCoord);
	newPosition.y = Luminosity(textureHeight);


	gl_Position = projection * camera * accumTrans * newPosition;

}