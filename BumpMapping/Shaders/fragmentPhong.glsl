#version 460 core
in vec2 texCoord;
in vec4 newPosition;
out vec4 fragcolor;

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 accumTrans;
uniform float time;
uniform vec3 eye;
uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;

struct Light
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

void main()
{
    vec4 textureDiffuse = texture(DiffuseMap, texCoord);
    vec3 textureNormal = texture(NormalMap, texCoord).rgb;
    vec3 normal = normalize(textureNormal * 2.0 - 1.0);

    vec3 fragPos = newPosition.xyz;

    Light light;
    light.ambient = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    light.diffuse = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    light.specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    light.position = vec3(cos(time), 1.0f, sin(time));

    Material material;
    material.ambient = textureDiffuse;
    material.diffuse = textureDiffuse;
    material.specular = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    vec3 lightDir = normalize(light.position - fragPos);
    vec3 viewDir = normalize(eye - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec4 ambient = light.ambient * material.ambient;
    float diff = max(dot(normal, lightDir), 0.0);
    vec4 diffuse = light.diffuse * (diff * material.diffuse);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = light.specular * (spec * material.specular);

    fragcolor = ambient + diffuse + specular;
}