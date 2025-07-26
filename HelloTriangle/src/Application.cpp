#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>
#include <vector>
//Application::Application() {}
void Application::SetupShaders()
{
	//std::cout << "Application::Setup()" << std::endl;
	//cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl")};
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl")};
	//crear programa
	shaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shader compilados" << std::endl;

	timeID = glGetUniformLocation(shaders["passthru"], "time");
}

void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f,1.0f,-1.0f,1.0f, //vertice 0
		-1.0f,-1.0f,-1.0f,1.0f,//vertice 1
		1.0f,-1.0f,-1.0f,1.0f,//vertice 2
	};
	std::vector<GLfloat> colors
	{
		1.0f,0.0f,0.0f,1.0f,//Rojo
		0.0f,1.0f,0.0f,1.0f,//verde
		0.0f,0.0f,1.0f,1.0f,//Azul
	};
	//crear VAO
	GLuint VAO_id, VBO_id, VBO_colorsID;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;
	//crear VBO
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(GLfloat) * triangle.size(), 
		&triangle[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//crear VBO de colores
	glGenBuffers(1, &VBO_colorsID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colorsID);  
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * colors.size(),
		&colors[0], GL_STATIC_DRAW);
	//Pasar arreglo de vertices
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);//colores
	glEnableVertexAttribArray(1);
}
void Application::SetupGeometrySingleArray()
{
	std::vector<GLfloat> triangle
	{
		-1.0f,1.0f,-1.0f,1.0f, //vertice 0
		-1.0f,-1.0f,-1.0f,1.0f,//vertice 1
		1.0f,-1.0f,-1.0f,1.0f,//vertice 2

		1.0f,0.0f,0.0f,1.0f,//Rojo
		0.0f,1.0f,0.0f,1.0f,//verde
		0.0f,0.0f,1.0f,1.0f,//Azul	
	};
	{

	//crear VAO
	GLuint VAO_id, VBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;
	//crear VBO
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * triangle.size(),
		&triangle[0], GL_STATIC_DRAW);

	}
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)&triangle[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)&triangle[4]);//colores
	glEnableVertexAttribArray(1);
}
void Application::Setup()
{
	SetupShaders();
	SetupGeometry();
	//SetupGeometrySingleArray();
}
void Application::Update()
{
	time += 0.01f;
	//std::cout << "Application::Update()" << std::endl;
}

void Application::Draw()
{
	//std::cout << "Application::Draw()" << std::endl;
	glUseProgram(shaders["passthru"]);
	glUniform1f(timeID, time);
	glBindVertexArray(geometry["triangulo"]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Application::Keyboard()
{
	//std::cout << "Application::Keyboard()" << std::endl;
}