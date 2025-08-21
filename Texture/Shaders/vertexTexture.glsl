#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;

out vec2 texCoord;

out vec4 color;

uniform float time;
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 accumTrans;
uniform float frecuency;
uniform float amplitude;

float F(float x, float z, float amplitude, float phase, float frecuency)
{
    return amplitude * cos(phase + frecuency * (x * x + z * z));
}

void main()
{
    vec4 newPosition = vPosition;
    float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
    newPosition.y = f;
    //float Height = (f + amplitude) / (2.0 * amplitude);
    color = vec4(1.0,1.0,1.0,1.0);
    texCoord = vTextCoord;
    gl_Position = projection * camera * accumTrans * newPosition;
}