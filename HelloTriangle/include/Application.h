#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include <map>
#include <vector>
#include <string>
//#include "Plane.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	std::map<std::string, GLuint> uniforms;
	void SetupShaderPassthru();
	void SetupShadersTransforms();
	void SetupShaders();
	void SetupGeometry();
	void SetupGeometrySingleArray();
	std::vector<GLfloat> colors;
	bool colorChanged;
	float time{ 0.0f };
	GLuint timeID;
	GLuint VAO_id;  
	GLuint VBO_id;
	GLuint VBO_colorsID;
	glm::mat4 projection;
	glm::mat4 camera;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec4 vertexColorValues[3]; 
	GLuint vertexColorLocs[3];
	//Plane plane;
public:
	float r, g, b, a;
	GLFWwindow* window;
	void Setup();
	void Update();
	void Draw();
	void Keyboard(int key, int scancode, int action, int mods);
	void ChangeVertexColor(int vertexIndex);
};