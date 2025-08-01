#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

out vec4 color;

uniform mat4 projection;
uniform mat4 camera;
uniform vec4 vertexColors[3];

void main()
{
    color = vertexColors[gl_VertexID];
    
    // Orden CORRECTO de multiplicación de matrices:
    gl_Position = projection * camera * vPosition;
    
    // Para debug: ver las coordenadas directamente
    // gl_Position = vPosition; // Descomenta para ver si el triángulo aparece sin transformaciones
}