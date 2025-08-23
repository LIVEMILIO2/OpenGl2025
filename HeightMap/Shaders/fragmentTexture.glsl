#version 460 core

in vec4 color;
in vec2 texCoord;
out vec4 fragcolor;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float leny;

void main()
{
    vec4 textureDiffuse = texture(tex0, texCoord);
    vec4 textureHeight = texture(tex1, texCoord);
    vec4 texelColor = mix(textureDiffuse, textureHeight, leny);

    fragcolor = texelColor;
}