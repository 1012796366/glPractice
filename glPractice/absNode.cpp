#include "absNode.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern int screenWidth;
extern int screenHeight;

GLuint genVAO()
{
	GLuint tempVAO;
	glGenVertexArrays(1, &tempVAO);
	return tempVAO;
}

GLuint genVBO()
{
	GLuint tempVBO;
	glGenBuffers(1, &tempVBO);
	return tempVBO;
}

GLuint genEBO()
{
	GLuint tempEBO;
	glGenBuffers(1, &tempEBO);
	return tempEBO;
}

void buffVerticles(
	primitive* object, GLfloat* vertices, GLsizei verticeLength,
	GLenum usages, GLuint verticeDimension, GLuint colorDimension, GLuint textureDimension, GLuint additionalDimension)
{
	glBindVertexArray(object->vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, object->vboID);
	glBufferData(GL_ARRAY_BUFFER, verticeLength, vertices, usages);

	glVertexAttribPointer(
		0, verticeDimension, GL_FLOAT, GL_FALSE,
		(verticeDimension + colorDimension + textureDimension + additionalDimension) * sizeof(GLfloat),
		(void*)0
	);
	glEnableVertexAttribArray(0);
	if (colorDimension)
	{
		// 历史遗留，懒得改了
		glVertexAttribPointer(
			1, colorDimension, GL_FLOAT, GL_FALSE,
			(verticeDimension + colorDimension + textureDimension + additionalDimension) * sizeof(GLfloat),
			(void*)(verticeDimension * sizeof(GLfloat))
		);
		glEnableVertexAttribArray(1);
	}
	if (additionalDimension)
	{
		// 已经是先法向量后纹理坐标了
		glVertexAttribPointer(
			1, additionalDimension, GL_FLOAT, GL_FALSE,
			(verticeDimension + textureDimension + additionalDimension) * sizeof(GLfloat),
			(void*)(verticeDimension * sizeof(GLfloat))
		);
		glEnableVertexAttribArray(1);
	}
	if (textureDimension)
	{
		glVertexAttribPointer(
			2, 2, GL_FLOAT, GL_FALSE,
			(verticeDimension + colorDimension + textureDimension + additionalDimension) * sizeof(GLfloat),
			(void*)((verticeDimension + colorDimension + additionalDimension) * sizeof(GLfloat))
		);
		glEnableVertexAttribArray(2);
	}
	object->vertexCount = (verticeLength / sizeof(GLfloat) / 5);
}

void buffIndices(primitive* object, GLuint* indices, GLsizei indiceLength, GLenum usages)
{
	glBindVertexArray(object->vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceLength, indices, usages);

	object->indiceCount = indiceLength / sizeof(GLuint);
}

GLuint loadTextureFromFile(std::string pathToImg)
{
	stbi_set_flip_vertically_on_load(true);

	GLsizei width, height, channels;
	GLuint texture;
	GLenum type = GL_RGB;
	unsigned char* imgData = stbi_load(pathToImg.c_str(), &width, &height, &channels, 0);

	if (imgData == nullptr)
	{
		throw std::runtime_error("Can't load image!");
	}
	if (channels == 4)
	{
		// 带 ALPHA 通道的会自动改正
		type = GL_RGBA;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imgData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imgData);
	return texture;
}

void drawPrimitive(primitive* object)
{
	glBindVertexArray(object->vaoID);
	glUseProgram(object->shaderID);

	glm::mat4 projection = glm::mat4(1.0f);
	
	projection = glm::perspective(glm::radians(defaultCamera.zoom), (float)(screenWidth / screenHeight), 0.1f, 100.0f);
	setMat4(object->shaderID, "model", object->transform);
	setMat4(object->shaderID, "view", getView(&defaultCamera));
	setMat4(object->shaderID, "projection", projection);
	setVec3(object->shaderID, "viewPos", defaultCamera.cameraPosition);


	for (GLuint i = 0; i < object->textureCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, object->textureUnit[i]);
	}
	if (object->indiceCount)
	{
		glDrawElements(GL_TRIANGLES, object->indiceCount, GL_UNSIGNED_INT, 0);
	}
	else if (object->vertexCount)
	{
		glDrawArrays(GL_TRIANGLES, 0, object->vertexCount);
	}
}

void translatePrimitive(primitive* object, glm::vec3 translateValue)
{
	glUseProgram(object->shaderID);

	object->transform = glm::translate(object->transform, translateValue);
}

void rotatePrimitive(primitive* object, GLfloat rotateValue, glm::vec3 rotateAxis, char const* angleMode)
{
	glUseProgram(object->shaderID);

	if (strcmp(angleMode, "rad"))
	{
		// RAD
		object->transform = glm::rotate(object->transform, rotateValue, rotateAxis);
	}
	else if (strcmp(angleMode, "deg"))
	{
		// DEG
		object->transform = glm::rotate(object->transform, glm::radians(rotateValue), rotateAxis);
	}
	else
	{
		// ERR
		throw std::invalid_argument("angleMode(argument of rotatePrimitive) only accepts \"deg\" or \"deg\".");
	}
}

void scalePrimitive(primitive* object, glm::vec3 scaleValue)
{
	glUseProgram(object->shaderID);

	object->transform = glm::scale(object->transform, scaleValue);
}

void addTexture(primitive* object, GLuint texture)
{
	object->textureUnit[object->textureCount] = texture;
	object->textureCount += 1;
}