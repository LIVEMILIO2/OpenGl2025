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
	std::string vertexShader{ loadTextFile("Shaders/textureVertex.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTexture.glsl") };

	shaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);

	uniforms["projection"] = glGetUniformLocation(shaders["transforms"], "projection");
	uniforms["accumTrans"] = glGetUniformLocation(shaders["transforms"], "accumTrans");
	uniforms["camera"] = glGetUniformLocation(shaders["transforms"], "camera");
	uniforms["time"] = glGetUniformLocation(shaders["transforms"], "time");
	uniforms["frecuency"] = glGetUniformLocation(shaders["transforms"], "frecuency");
	uniforms["amplitude"] = glGetUniformLocation(shaders["transforms"], "amplitude");
	uniforms["DiffuseMap"] = glGetUniformLocation(shaders["transforms"], "DiffuseMap");
	uniforms["HeightMap"] = glGetUniformLocation(shaders["transforms"], "HeightMap");
	uniforms["leny"] = glGetUniformLocation(shaders["transforms"], "leny");
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
void Application::SetupPlane()
{
	plane.createPlane(100);

	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);
	glGenBuffers(1, &plane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);


	glBufferData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes() + plane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, plane.getVertexSizeInBytes(), plane.plane);
	glBufferSubData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes(), plane.getTextureCoordsSizeInBytes(), plane.textureCoords);
	plane.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(plane.getVertexSizeInBytes()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
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
	textures["DiffuseMap"] = SetUpTexture("Textures/Diffuse.png");
	textures["HeightMap"] = SetUpTexture("Textures/Height.png");
	//Texturas = { "lenna", "Agnes" };
	// Configuración inicial de la cámara
	eye = glm::vec3(0.0f, 0.0f, 2.0f); // Posición inicial de la cámara
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	
	projection = glm::perspective(
		glm::radians(45.0f),    
		1020.0f / 720.0f,       
		0.1f,                  
		200.0f                 
	);
	//accumTransX = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	accumTransX = glm::rotate(glm::mat4(1.0f), glm::radians(eyeXRot), glm::vec3(0.0f, 1.0f, 0.0f));
	accumTransY = glm::rotate(glm::mat4(1.0f), glm::radians(eyeYRot), glm::vec3(1.0f, 0.0f, 0.0f));
	accumTrans = accumTransY * accumTransX;
	//accumTransY = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//accumTrans = accumTransX * accumTransY;
	glEnable(GL_DEPTH_TEST); 
	/*glDepthFunc(GL_GREATER);*/
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
}
void Application::Update()
{
	time += 0.0001f; 

	
	eye = glm::vec3(0.0f, 0.0f, 2.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	/*glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); */

	// Matriz de vista correctamente calculada
	camera = glm::lookAt(eye, center, glm::vec3(0.0f,1.0f,0.0f));
	accumTransX = glm::rotate(glm::mat4(1.0f), glm::radians(eyeXRot), glm::vec3(0.0f, 1.0f, 0.0f));
	accumTransY = glm::rotate(glm::mat4(1.0f), glm::radians(eyeYRot), glm::vec3(1.0f, 0.0f, 0.0f));
	accumTrans = accumTransY * accumTransX;
}

void Application::Draw()
{
	// Limpiar buffers
	
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Color de fondo

	glUseProgram(shaders["transforms"]);
	glUniform1f(uniforms["time"], time);
	glUniform1f(uniforms["frecuency"], frecuency);
	glUniform1f(uniforms["amplitude"], amplitude);
	glUniform1f(uniforms["leny"], leny);
	// Configurar matrices
	glUniformMatrix4fv(uniforms["camera"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniforms["accumTrans"], 1, GL_FALSE, glm::value_ptr(accumTrans));
	// Configurar colores
	glUniform4fv(uniforms["VertexColors"], 1, &vertexColorValues[0]);
	// Dibujar
//	std::string currentTextureName = Texturas[indexTex];
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures["DiffuseMap"]);
	glUniform1i(uniforms["DiffuseMap"], 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures["HeightMap"]);
	glUniform1i(uniforms["HeightMap"], 1);

	glBindVertexArray(plane.vao);
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());

}
void Application::Keyboard(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_RIGHT)
		{
			leny -= 0.05f;

		}
		else if (key == GLFW_KEY_LEFT)
		{
			
			leny += 0.05f;
		}
	}

	// Resto de tus controles existentes
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		amplitude += 0.05f;

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		frecuency += 1.0f;

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		amplitude += 0.05f;
	
}
void Application::MouseInput(double xpos, double ypos)
{
	eyeXRot = xpos;
	eyeYRot = ypos;
}