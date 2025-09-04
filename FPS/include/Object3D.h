#pragma once

#include <iostream>
#include "glad.h"
#include "glm/glm.hpp"




class Object3D{
public:
	GLuint	vao, //Vertex Array Object
			vbo; //Vertex Buffer Object

	int numVertex; //numero de vertices para este objeto

	GLuint shader; //referencia a los shaders
	GLuint uniform; //para almacenar el angulo
	float angleX; //<-----------------------------------------
	float angleY;
	float angleZ;
	//Object3D();

};

