#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include <iostream>

class primitive
{
public:
	GLuint vaoID = 0;
	GLuint vboID = 0;
	GLuint eboID = 0;
	GLuint shaderID = 0;
	GLuint textureUnit[16] = { 0 };
	GLuint textureCount = 0;
	GLsizei vertexCount = 0;
	GLsizei indiceCount = 0;

	glm::mat4 transform = glm::mat4(1.0f);
};

GLuint genVAO();
GLuint genVBO();
GLuint genEBO();

// buffer verticles data to a primitive
// will bind this primitive's own VAO / VBO
// will NOT bind this primitive's own EBO
// array will be passed as pointer and length data will be lost
// so verticlesLength = sizeof(verticles) is necessary for solving this problem
// texture property will be treated as a property with 2 GLfloat
// { position, color, texture }
void buffVerticles(
	primitive* object, GLfloat* verticles, GLsizei verticlesLength, GLenum usages = GL_STATIC_DRAW
);

// buffer indices data to a primitive
// will bind this primitive's own VAO / EBO
// will NOT bind this primitive's own EBO
// array will be passed as pointer and length data will be lost
// so verticlesLength = sizeof(verticles) is necessary for solving this problem
void buffIndices(
	primitive* object, GLuint* indices, GLsizei indicesLength, GLenum usages = GL_STATIC_DRAW
);

// will load a pic file
GLuint loadTextureFromFile(
	std::string pathToImg
);

void drawPrimitive(
	primitive* object
);

// will move the primitive relative to the given transform
void translatePrimitive(
	primitive* object, glm::vec3 translateValue
);

// will rotate the primitive relative to the given transform
// angleMode = "rad" or "deg"
void rotatePrimitive(
	primitive* object, GLfloat rotateValue, glm::vec3 rotateAxis,
	char const* angleMode = "deg"
);

// will scale the primitive relative to the given transform
void scalePrimitive(
	primitive* object, glm::vec3 scaleValue
);

void addTexture(
	primitive* object, GLuint texture
);