#version 460 core

layout(location = 0) in vec4 vPosition;
out vec4 color;
out vec4 colorADS;
uniform float time;
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 accumTrans;
uniform float frecuency;
uniform float amplitude;
uniform vec4 vertexColors;
uniform vec4 ColorChange;
uniform vec3 eye;

float F(float x, float z,float amplitude, float phase, float frecuency)
{
    //Amplitud
    return amplitude * cos(phase+ frecuency * (x * x + z * z));
}
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
};
vec4 ambient(Light L, Material M)
{
    return L.ambient * M.ambient;
}

vec4 diffuse(Light L, Material M,vec3 Normal)
{
    return L.diffuse * M.diffuse*max(0.0f,dot(normalize(L.position),normalize(Normal)));
}
vec4 specular(vec3 eye, vec3 vertexPos, Light L, vec3 Normal, Material M,float SH)
{
    vec4 specular;
    vec3 view = normalize(eye) -normalize(vertexPos);
    vec3 RE = normalize(reflect((eye - L.position),Normal));
    if(dot(L.position,view)>0.0)
    {
        specular = L.specular * M.specular * pow(max(0.0f,dot(view,RE)),SH);
    }
    return specular;
}

//vec4 specular(Light L, Material M)
//{
//    return L.specular*M.specular*(vec4 R * vec4 E)
//}
//float height(float x, float z, float time)
//{
//    return 0.125 * F(x, z, time);
//}
void main()
{
    vec3 Normal = vec3(0.0,1.0f,0);
    Light light;
    light.ambient = vec4(0.1f,1.0f,0.1f,1.0f);
    light.position = vec3(cos(time), 2.0f, sin(time));
    light.diffuse = vec4(1.0f, 0.1f, 1.0f, 1.0f);
    light.specular = vec4(0.0f, 0.5f,0.0f,1.0f);
    Material material;
    material.ambient = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material.diffuse = vec4(0.1f, 0.5f, 1.0f, 1.0f);
    material.specular = vec4(0.0f, 0.5f,0.0f,1.0f);
    //color = vertexColors;
    vec4 newPosition = vPosition;
    newPosition = camera * accumTrans * newPosition;
    color = vec4(0, 0, 0, 1.0);
    vec3 vertexPos = vec3(newPosition.x,newPosition.y,newPosition.z);
    colorADS = ambient(light, material)+diffuse(light,material,Normal)+specular(eye,newPosition.xyz,
    light,Normal,material,8.0f);
    gl_Position = projection *  newPosition;
    // gl_Position = vPosition;
}