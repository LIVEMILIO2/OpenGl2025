#include "Application.h"
#include "ShaderFuncs.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <iostream>
#include <vector>
//Application::Application() {}
void Application::SetupShaderPassthru()
{
	//std::cout << "Application::Setup()" << std::endl;
	//cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl") };
	//crear programa
	shaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shader compilados" << std::endl;

    timeID = glGetUniformLocation(shaders["passthru"], "time");
}
void Application::SetupShadersTransforms()
{
	//std::cout << "Application::Setup()" << std::endl;
//cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexTrans.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTrans.glsl") };
	//crear programa
	shaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shader compilados" << std::endl;

	uniforms["projection"] = glGetUniformLocation(shaders["transforms"], "projection");
	uniforms["camera"] = glGetUniformLocation(shaders["transforms"], "camera");
}
void Application::SetupShaders()
{
	SetupShadersTransforms();
	//SetupShadersPassThru();
	//uniforms["camera"] = glGetUniformLocation(shaders[""]);
}

void Application::SetupGeometry()
{
	//std::vector<GLfloat> triangle{
	//	-1.0f, 1.0f, -1.0f, 1.0f,  // vértice 0
	//	1.0f,1.0f,-1.0f,1.0f,
	//	-1.0f, -1.0f, -1.0f, 1.0f, // vértice 1
	//	1.0f, -1.0f, -1.0f, 1.0f,   // vértice 2

	//	/*- 1.0, 1.0f,-1.0,1.0f,
	//	1.0f,-1.0f, -1.0f,1.0f,*/
	//};

	//colors = {
	//	1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (vértice 0)
	//	1.0f, 1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 0.0f, 1.0f,   // Verde (vértice 1)
	//	0.0f, 0.0f, 1.0f, 1.0f,    // Azul (vértice 2)

	//	//1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (vértice 0)
	//	//0.0f, 1.0f, 0.0f, 1.0f,   // Verde (vértice 1)
	//};
	std::vector<GLfloat> triangle
	{
		-1.0f,1.0f,-1.0f,1.0f, //vertice 0
		1.0f,0.0f,0.0f,1.0f,//Rojo
		-1.0f,-1.0f,-1.0f,1.0f,//vertice 1
		0.0f,1.0f,0.0f,1.0f,//verde
		1.0f,-1.0f,-1.0f,1.0f,//vertice 2
		0.0f,0.0f,1.0f,1.0f,//Azul	

	};
	// Generar y bindear el VAO
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	// Buffer de vértices
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * triangle.size(),
		&triangle[0], GL_STATIC_DRAW);


	int stride = 8 * sizeof(GLfloat);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(4 * sizeof(GLfloat)));//colores
	glEnableVertexAttribArray(1);
	/*glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), triangle.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);*/

	//// Buffer de colores
	//glGenBuffers(1, &VBO_colorsID);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_colorsID);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), colors.data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(1);
}
void Application::SetupGeometrySingleArray()
{
	std::vector<GLfloat> triangle
	{
		-1.0f,1.0f,-1.0f,1.0f, //vertice 0
		1.0f,0.0f,0.0f,1.0f,//Rojo
		-1.0f,-1.0f,-1.0f,1.0f,//vertice 1
		0.0f,1.0f,0.0f,1.0f,//verde
		1.0f,-1.0f,-1.0f,1.0f,//vertice 2
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
	int stride = 8 * sizeof(GLfloat);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(4*sizeof(GLfloat)));//colores
	glEnableVertexAttribArray(1);
}
void Application::Setup()
{
	SetupShaders();
	SetupGeometry();
	//SetupGeometrySingleArray();

	//inicializar camara
	eye = glm::vec3(0.0f, 0.0f, 2.0f);
	center = glm::vec3(0.0f, 0.0f,1.0f);
	projection = glm::perspective(glm::radians(45.0f), (1020.0f / 720.0f), 0.1f,10.0f);
}
void Application::Update()
{
	time += 0.0001f;
	//actualizar ojo
	eye = glm::vec3(0.0f, 0.0f, cos(time));
	//actualizar center
	center = glm::vec3(0.0f, 0.0f, 1.0f);
	//actualizar camara
	camera = glm::lookAt(eye,center,glm::vec3(0.0f,1.0f,0.0f));
	//std::cout << "Application::Update()" << std::endl;
}

void Application::Draw()
{
	glUseProgram(shaders["transforms"]);
	glUniform1f(timeID, time);
	glUniformMatrix4fv(uniforms["camera"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, glm::value_ptr(projection));
	glUniform4f(VBO_colorsID,r,g,b,a);
	glBindVertexArray(geometry["triangulo"]);

	/*if (colorChanged)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO_colorsID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), colors.data(), GL_STATIC_DRAW);
		colorChanged = false;
	}*/

	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Application::Keyboard(int key, int scancode, int action, int mods)
{
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		//activar el flag de salida del programa
		glfwSetWindowShouldClose(window, 1);


	}
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