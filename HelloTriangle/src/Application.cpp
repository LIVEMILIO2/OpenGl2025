#include "Application.h"
#include "ShaderFuncs.h"
#include "GLFW/glfw3.h"
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
	std::vector<GLfloat> triangle{
		-1.0f, 1.0f, -1.0f, 1.0f,  // vértice 0
		-1.0f, -1.0f, -1.0f, 1.0f, // vértice 1
		1.0f, -1.0f, -1.0f, 1.0f   // vértice 2
	};

	colors = {
		1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (vértice 0)
		0.0f, 1.0f, 0.0f, 1.0f,   // Verde (vértice 1)
		0.0f, 0.0f, 1.0f, 1.0f    // Azul (vértice 2)
	};

	// Generar y bindear el VAO
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	// Buffer de vértices
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), triangle.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Buffer de colores
	glGenBuffers(1, &VBO_colorsID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colorsID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
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
	glUseProgram(shaders["passthru"]);
	glUniform1f(timeID, time);

	if (colorChanged)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO_colorsID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), colors.data(), GL_STATIC_DRAW);
		colorChanged = false;
	}

	glBindVertexArray(VAO_id);  
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Application::Keyboard()
{
	GLFWwindow* window = glfwGetCurrentContext();

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		ChangeVertexColor(0); // Cambiar vértice 0

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		ChangeVertexColor(1); // Cambiar vértice 1

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		ChangeVertexColor(2); // Cambiar vértice 2
	//std::cout << "Application::Keyboard()" << std::endl;
}
void Application::ChangeVertexColor(int vertexIndex)
{
	if (vertexIndex < 0 || vertexIndex > 2) return;

	int baseIndex = vertexIndex * 4;
	// Cambiar a un color aleatorio
	colors[baseIndex] = static_cast<float>(rand()) / RAND_MAX;     // R
	colors[baseIndex + 1] = static_cast<float>(rand()) / RAND_MAX; // G
	colors[baseIndex + 2] = static_cast<float>(rand()) / RAND_MAX; // B

	colorChanged = true;
}