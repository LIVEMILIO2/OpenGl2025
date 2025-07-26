#pragma once
#include "glad.h"
#include <map>
#include <string>
class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	void SetupShaders();
	void SetupGeometry();
	void SetupGeometrySingleArray();

	float time{ 0.0f };
	GLuint timeID;
public:

	void Setup();
	void Update();
	void Draw();
	void Keyboard();
};