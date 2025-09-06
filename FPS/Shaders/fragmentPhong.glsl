#version 460 core
in vec2 texCoord;
in vec4 newPosition;
vec4 colorADS;
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
vec4 ambient(Light L, Material M)
{
    return L.ambient * M.ambient;
}

vec4 diffuse(Light L, Material M, vec3 Normal)
{
    return L.diffuse * M.diffuse * max(0.0f, dot(normalize(L.position), normalize(Normal)));
}

vec4 specular(vec3 eye, vec3 vertexPos, Light L, vec3 Normal, Material M, float SH)
{
    vec4 specular = vec4(0.0f, 0.0, 0.0f, 1.0f);
    vec3 view = normalize(eye - vertexPos);
    vec3 RE = normalize(reflect((eye - L.position), Normal));

    if (dot(L.position, view) > 0.0)
    {
        specular = L.specular * M.specular * pow(max(0.0f, dot(view, RE)), SH);
    }
    return specular;

}
//out vec3 normal;

void main()
{
    
    vec4 fragPos = newPosition;
  
    vec4 textureDiffuse = texture(DiffuseMap, texCoord);
    vec4 textureNormal = normalize(texture(NormalMap, texCoord));

    Light light;
    light.ambient = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    light.position = vec3(0, 3.0f, 0);
    light.diffuse = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    light.specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);

    Material material;
    material.ambient = textureDiffuse;
    material.diffuse = textureDiffuse;
    material.specular = textureDiffuse;

    mat4 matforNormals = transpose(inverse(camera * accumTrans));
    textureNormal = normalize(matforNormals * textureNormal);

    
  /*  vec4 ambient = light.ambient * material.ambient;
    float diff = max(dot(textureNormal, lightDir), 0.0);
    vec4 diffuse = light.diffuse * (diff * material.diffuse);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 40);
    vec4 specular = light.specular * (spec * material.specular);*/

    colorADS =
        ambient(light, material) +
        diffuse(light, material, textureNormal.xyz) +
        specular(eye, fragPos.xyz, light, textureNormal.xyz, material, 12.0f);
    fragcolor = colorADS;
   
}