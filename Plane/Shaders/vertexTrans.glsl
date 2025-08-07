#version 460 core

layout(location = 0) in vec4 vPosition;
out vec4 color;
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

//float height(float x, float z, float time)
//{
//    return 0.125 * F(x, z, time);
//}
void main()
{
    //color = vertexColors;
    vec4 newPosition = vPosition;
    float f = F(newPosition.x, newPosition.z, amplitude, time, frecuency);
    newPosition.y = f;
    color = vec4(clamp(0.7 * f, 0.0f, 1.0f), 0.3, 0.4, 1.0);
    //if (distance(vec4(0.0f, 0.0f, 0.0f, 1.0f), newPosition) < 0.3f)
    //{
    //    vertexColors.x = cos(time);
    //    vertexColors.y = cos(time);
    //    vertexColors.z = cos(time);
   // }
    gl_Position = 
        projection * 
        camera*
        acumTrans * 
        newPosition;
    // gl_Position = vPosition;
}