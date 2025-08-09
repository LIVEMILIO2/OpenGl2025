#version 460 core

layout(location = 0) in vec4 vPosition;
out vec4 color;
out vec4 colorADS;
uniform float time;
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 acumTrans;
uniform float frecuency;
uniform float amplitude;
uniform vec4 vertexColors;
uniform vec4 ColorChange;

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
    Light light;
    light.ambient = vec4(0.1f,1.0f,0.1f,1.0f);
    light.position = vec3(0.0f, 2.0f, 0.3f);
    light.diffuse = vec4(1.0f, 0.1f, 1.0f, 1.0f);
    vec3 Normal = vec3(0.0, cos(radians(45)),sin(radians(45)));
    Material material;
    material.ambient = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material.diffuse = vec4(0.1f, 0.5f, 1.0f, 1.0f);
    //color = vertexColors;
    vec4 newPosition = vPosition;
    float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
    newPosition.y = f;
    color = vec4(0, 0, 0, 1.0);
    //color = vec4(clamp(1 * f, 0.0f, 0.0f), 1, 1, 1.0);
    if (distance(vec4(0.0f, 0.0f, 0.0f, 1.0f), newPosition) < 1.0f)
    {
        color = vec4(1, 1, 1, 1.0);
    }
    colorADS = ambient(light, material)+diffuse(light,material,Normal);
    gl_Position = 
        projection * 
        camera*
        acumTrans * 
        newPosition;
    // gl_Position = vPosition;
}