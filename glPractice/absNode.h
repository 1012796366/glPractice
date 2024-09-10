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

// ���붥��
// verticesLength ����Ϊ sizeof(��������)
// xxDimension ����һ�������Ƕ���ά������Ϊ 0 ����ø�����
void buffVerticles(
	primitive* object, GLfloat* vertices, GLsizei verticeLength, GLenum usages = GL_STATIC_DRAW,
	GLuint verticeDimension = 3, GLuint colorDimension = 3, GLuint textureDimension = 2
);

// ��������
// indiceLength ����Ϊ sizeof(��������)
void buffIndices(primitive* object, GLuint* indices, GLsizei indiceLength, GLenum usages = GL_STATIC_DRAW);

// ����ͼƬ���������� ID
GLuint loadTextureFromFile(std::string pathToImg);

// ΪͼԪ��������
void addTexture(primitive* object, GLuint texture);

// ����ͼԪ
void drawPrimitive(primitive* object);

// �ƶ�ͼԪ
void translatePrimitive(primitive* object, glm::vec3 translateValue);

// ��תͼԪ
// angleMode ֻ��Ϊ "deg" �� "rad"
void rotatePrimitive(primitive* object, GLfloat rotateValue, glm::vec3 rotateAxis, char const* angleMode = "deg");

// ����ͼԪ
void scalePrimitive(primitive* object, glm::vec3 scaleValue);