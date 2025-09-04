#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 accumTrans;
uniform vec3 eye;
out vec4 newPosition;
out vec2 texCoord;

void main()
{
    texCoord = vTextCoord;
    newPosition = camera * accumTrans * vPosition;
    gl_Position = projection * newPosition;
}