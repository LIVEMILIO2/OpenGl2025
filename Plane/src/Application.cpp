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
	/*selectColorRojo = glGetUniformLocation(shaders["passthru"], "outColorRed");
	selectColorVerde = glGetUniformLocation(shaders["passthru"], "outColorGreen");
	selectColorAzul = glGetUniformLocation(shaders["passthru"], "outColorBlue");*/
}
void Application::SetupShadersTransforms()
{
	std::string vertexShader{ loadTextFile("Shaders/vertexTrans.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTrans.glsl") };

	shaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);

	uniforms["projection"] = glGetUniformLocation(shaders["transforms"], "projection");
	uniforms["camera"] = glGetUniformLocation(shaders["transforms"], "camera");
	timeID = glGetUniformLocation(shaders["transforms"], "time");

	// Obtener locations para los colores
	vertexColorLocs[0] = glGetUniformLocation(shaders["transforms"], "vertexColors[0]");
	vertexColorLocs[1] = glGetUniformLocation(shaders["transforms"], "vertexColors[1]");
	vertexColorLocs[2] = glGetUniformLocation(shaders["transforms"], "vertexColors[2]");

	// Valores iniciales de color
	vertexColorValues[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // Rojo
	vertexColorValues[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); // Verde
	vertexColorValues[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); // Azul
}
void Application::SetupShaders()
{
	SetupShadersTransforms();
	//SetupShadersPassThru();
	//uniforms["camera"] = glGetUniformLocation(shaders[""]);
}

void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle{
		-1.0f, 1.0f, -1.0f, 1.0f,  // vértice 0
		//1.0f,1.0f,-1.0f,1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f, // vértice 1
		1.0f, -1.0f, -1.0f, 1.0f,   // vértice 2
		-1.0f, 1.0f, -1.5f, 1.0f,  // vértice 0
		//1.0f,1.0f,-1.0f,1.0f,
		-1.0f, -1.0f, -1.5f, 1.0f, // vértice 1
		1.0f, -1.0f, -0.5f, 1.0f,
		/*- 1.0, 1.0f,-1.0,1.0f,
		1.0f,-1.0f, -1.0f,1.0f,*/
	};

	colors = {
		1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (vértice 0)
		/*1.0f, 1.0f, 1.0f, 1.0f,*/
		0.0f, 1.0f, 0.0f, 1.0f,   // Verde (vértice 1)
		0.0f, 0.0f, 1.0f, 1.0f,    // Azul (vértice 2)
		1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (vértice 0)
		/*1.0f, 1.0f, 1.0f, 1.0f,*/
		0.0f, 1.0f, 0.0f, 1.0f,   // Verde (vértice 1)
		0.0f, 0.0f, 1.0f, 1.0f,    // Azul (vértice 2)
		//1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (vértice 0)
		//0.0f, 1.0f, 0.0f, 1.0f,   // Verde (vértice 1)
	};
	//std::vector<GLfloat> triangle
	//{
	//	-1.0f,1.0f,-1.0f,1.0f, //vertice 0
	//	1.0f,0.0f,0.0f,1.0f,//Rojo
	//	-1.0f,-1.0f,-1.0f,1.0f,//vertice 1
	//	0.0f,1.0f,0.0f,1.0f,//verde
	//	1.0f,-1.0f,-1.0f,1.0f,//vertice 2
	//	0.0f,0.0f,1.0f,1.0f,//Azul	

	//};
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
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(4 * sizeof(GLfloat)));//colores
	//glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), triangle.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

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
		glGenVertexArrays(1, &VAO_id);
		glBindVertexArray(VAO_id);
		geometry["triangulo"] = VAO_id;

		// Buffer de vértices (ahora con posiciones y colores)
		glGenBuffers(1, &VBO_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), triangle.data(), GL_STATIC_DRAW);

		// Atributos de posición (stride = 8 floats)
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		// Atributos de color (stride = 8 floats, offset = 4 floats)
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	}
void Application::Setup()
{
	SetupShaders();
	SetupGeometry();

	// Configuración inicial de la cámara
	eye = glm::vec3(0.0f, 0.0f, 2.0f); // Posición inicial de la cámara
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	
	projection = glm::perspective(
		glm::radians(45.0f),    
		1020.0f / 720.0f,       
		0.1f,                  
		100.0f                 
	);

	//glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_GREATER);
}
void Application::Update()
{
	time += 0.0001f; 

	
	eye = glm::vec3(0.0f, 0.0f, 2.0f); 
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	/*glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); */

	// Matriz de vista correctamente calculada
	camera = glm::lookAt(eye, center, glm::vec3(0.0f,1.0f,0.0f));
	
}

void Application::Draw()
{
	// Limpiar buffers
	
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Color de fondo

	glUseProgram(shaders["transforms"]);

	// Configurar matrices
	glUniformMatrix4fv(uniforms["camera"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, glm::value_ptr(projection));

	// Configurar colores
	glUniform4fv(vertexColorLocs[0], 1, glm::value_ptr(vertexColorValues[0]));
	glUniform4fv(vertexColorLocs[1], 1, glm::value_ptr(vertexColorValues[1]));
	glUniform4fv(vertexColorLocs[2], 1, glm::value_ptr(vertexColorValues[2]));

	// Dibujar
	glBindVertexArray(geometry["triangulo"]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
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

	// Cambiar a un color aleatorio
	vertexColorValues[vertexIndex] = glm::vec4(
		static_cast<float>(rand()) / RAND_MAX,
		static_cast<float>(rand()) / RAND_MAX,
		static_cast<float>(rand()) / RAND_MAX,
		1.0f
	);
}