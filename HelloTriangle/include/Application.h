#pragma once
#include "glad.h"
#include <map>
#include <vector>
#include <string>
class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
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
public:

	void Setup();
	void Update();
	void Draw();
	void Keyboard();
	void ChangeVertexColor(int vertexIndex);
};