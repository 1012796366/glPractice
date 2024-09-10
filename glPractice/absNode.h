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

// 导入顶点
// verticesLength 必须为 sizeof(顶点数组)
// xxDimension 代表一个属性是多少维，设置为 0 则禁用该属性
void buffVerticles(
	primitive* object, GLfloat* vertices, GLsizei verticeLength, GLenum usages = GL_STATIC_DRAW,
	GLuint verticeDimension = 3, GLuint colorDimension = 3, GLuint textureDimension = 2
);

// 导入序列
// indiceLength 必须为 sizeof(序列数组)
void buffIndices(primitive* object, GLuint* indices, GLsizei indiceLength, GLenum usages = GL_STATIC_DRAW);

// 加载图片，返回纹理 ID
GLuint loadTextureFromFile(std::string pathToImg);

// 为图元增添纹理
void addTexture(primitive* object, GLuint texture);

// 绘制图元
void drawPrimitive(primitive* object);

// 移动图元
void translatePrimitive(primitive* object, glm::vec3 translateValue);

// 旋转图元
// angleMode 只能为 "deg" 或 "rad"
void rotatePrimitive(primitive* object, GLfloat rotateValue, glm::vec3 rotateAxis, char const* angleMode = "deg");

// 缩放图元
void scalePrimitive(primitive* object, glm::vec3 scaleValue);