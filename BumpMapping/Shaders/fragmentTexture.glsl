#version 460 core

in vec4 color;
in vec2 texCoord;
out vec4 fragcolor;
uniform sampler2D DiffuseMap;
void main()
{
  
    vec4 textureDiffuse = texture(DiffuseMap, texCoord);
    fragcolor = textureDiffuse;
}