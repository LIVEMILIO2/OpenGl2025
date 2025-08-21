#include "Application.h"
#include "ShaderFuncs.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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
	std::string vertexShader{ loadTextFile("Shaders/vertexTexture.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTexture.glsl") };

	shaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);

	uniforms["projection"] = glGetUniformLocation(shaders["transforms"], "projection");
	uniforms["accumTrans"] = glGetUniformLocation(shaders["transforms"], "accumTrans");
	uniforms["camera"] = glGetUniformLocation(shaders["transforms"], "camera");
	uniforms["time"] = glGetUniformLocation(shaders["transforms"], "time");
	uniforms["frecuency"] = glGetUniformLocation(shaders["transforms"], "frecuency");
	uniforms["amplitude"] = glGetUniformLocation(shaders["transforms"], "amplitude");
	uniforms["tex0"] = glGetUniformLocation(shaders["transforms"], "tex0");
	// Obtener locations para los colores
	uniforms["VertexColors"] = glGetUniformLocation(shaders["transforms"], "vertexColors");
	//vertexColorValues = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

}
void Application::SetupShaders()
{
	SetupShadersTransforms();
}

void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle{
		-1.0f, 1.0f, -1.0f, 1.0f,  // v�rtice 0
		//1.0f,1.0f,-1.0f,1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f, // v�rtice 1
		1.0f, -1.0f, -1.0f, 1.0f,   // v�rtice 2
		-1.0f, 1.0f, -1.5f, 1.0f,  // v�rtice 0
		//1.0f,1.0f,-1.0f,1.0f,
		-1.0f, -1.0f, -1.5f, 1.0f, // v�rtice 1
		1.0f, -1.0f, -0.5f, 1.0f,
		/*- 1.0, 1.0f,-1.0,1.0f,
		1.0f,-1.0f, -1.0f,1.0f,*/
	};

	colors = {
		1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (v�rtice 0)
		/*1.0f, 1.0f, 1.0f, 1.0f,*/
		0.0f, 1.0f, 0.0f, 1.0f,   // Verde (v�rtice 1)
		0.0f, 0.0f, 1.0f, 1.0f,    // Azul (v�rtice 2)
		1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (v�rtice 0)
		/*1.0f, 1.0f, 1.0f, 1.0f,*/
		0.0f, 1.0f, 0.0f, 1.0f,   // Verde (v�rtice 1)
		0.0f, 0.0f, 1.0f, 1.0f,    // Azul (v�rtice 2)
		//1.0f, 0.0f, 0.0f, 1.0f,  // Rojo (v�rtice 0)
		//0.0f, 1.0f, 0.0f, 1.0f,   // Verde (v�rtice 1)
	};
	// Generar y bindear el VAO
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	// Buffer de v�rtices
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * triangle.size(),
		&triangle[0], GL_STATIC_DRAW);


	int stride = 8 * sizeof(GLfloat);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), triangle.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
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

		// Buffer de v�rtices (ahora con posiciones y colores)
		glGenBuffers(1, &VBO_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), triangle.data(), GL_STATIC_DRAW);

		// Atributos de posici�n (stride = 8 floats)
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		// Atributos de color (stride = 8 floats, offset = 4 floats)
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
}
void Application::SetupPlane()
{
	plane.createPlane(1);

}
GLuint Application::SetUpTexture(const std::string& filename)
{
	int width, height, channels;
	unsigned char * img = stbi_load(filename.c_str(), &width, &height, &channels, 4);
	if (img == nullptr)
		return -1;
	
	GLuint texID = -1;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	stbi_image_free(img);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texID;

}	
void Application::Setup()
{
	SetupShaders();
	SetupPlane();
	//SetupGeometry();
	textures["lenna"] = SetUpTexture("Textures/Lenna.png");
	// Configuraci�n inicial de la c�mara
	eye = glm::vec3(0.0f, 0.0f, 2.0f); // Posici�n inicial de la c�mara
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	
	projection = glm::perspective(
		glm::radians(45.0f),    
		1020.0f / 720.0f,       
		0.1f,                  
		200.0f                 
	);
	accumTrans = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glEnable(GL_DEPTH_TEST); 
	/*glDepthFunc(GL_GREATER);*/
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
}
void Application::Update()
{
	time += 0.0001f; 

	
	eye = glm::vec3(0.0f, 0.0f, 5.0f);
	center = glm::vec3(0.0f, 0.0f, 1.0f);
	/*glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); */

	// Matriz de vista correctamente calculada
	camera = glm::lookAt(eye, center, glm::vec3(0.0f,1.0f,0.0f));
	
}

void Application::Draw()
{
	// Limpiar buffers
	
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Color de fondo

	glUseProgram(shaders["transforms"]);
	glUniform1f(uniforms["time"], time);
	glUniform1f(uniforms["frecuency"], frecuency);
	glUniform1f(uniforms["amplitude"], amplitude);
	// Configurar matrices
	glUniformMatrix4fv(uniforms["camera"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniforms["accumTrans"], 1, GL_FALSE, glm::value_ptr(accumTrans));
	// Configurar colores
	glUniform4fv(uniforms["VertexColors"], 1, &vertexColorValues[0]);
	// Dibujar
	glBindTexture(GL_TEXTURE_2D, textures["lenna"]);
	glUniform1i(uniforms["tex0"], 0);
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(plane.vao);
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());

}
void Application::Keyboard(int key, int scancode, int action, int mods)
{
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		//activar el flag de salida del programa
		glfwSetWindowShouldClose(window, 1);


	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		//ChangeVertexColor(0); // Cambiar v�rtice 0
		amplitude += 0.05f;

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		//ChangeVertexColor(1); // Cambiar v�rtice 1
		//amplitude -= 0.05f;
		frecuency += 1.0f;

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		//ChangeVertexColor(2); // Cambiar v�rtice 2
		amplitude += 0.05f;
	//std::cout << "Application::Keyboard()" << std::endl;
}