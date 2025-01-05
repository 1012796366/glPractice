#include "initWin.h"
#include <iostream>
#include "preFlag.h"
#include "opsWin.h"
#include "inputProc.h"
#include "shader.h"
#include "absNode.h"

int screenWidth = 1600;
int screenHeight = 900;

int main()
{
	GLfloat vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	glm::vec3 cubePos[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	basicWindow base;
	initWindow(&base, "LearnOpenGL", GLBW_SCREEN_WINDOWED, screenWidth, screenHeight);

	primitive box;
	box.vaoID = genVAO();
	box.vboID = genVBO();
	box.eboID = genEBO();
	box.shaderID = loadShaderFromFile("./Shader/shaderVert.vert", "./Shader/shaderFrag.frag");

	// ↓ 导入顶点数据与序列数据 ↓
	buffVerticles(&box, vertices, sizeof(vertices), GL_STATIC_DRAW, 3, 0, 2, 3);
	//buffIndices(&box, indices, sizeof(indices), GL_STATIC_DRAW);
	// ↑ 导入顶点数据与序列数据 ↑

	addTexture(&box, loadTextureFromFile("./pic/container2.png"));
	addTexture(&box, loadTextureFromFile("./pic/container2_specular.png"));

	setBackgroundColor(0.0f, 0.0f, 0.0f);

	setInt(box.shaderID, "material.cusTex[0]", 0);
	setInt(box.shaderID, "material.cusTex[1]", 1);
	setInt(box.shaderID, "material.cusTex[2]", 2);
	setVec3(box.shaderID, "light.color", glm::vec3(1.0f, 1.0f, 1.0f));
	setVec3(box.shaderID, "light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	setVec3(box.shaderID, "light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	setVec3(box.shaderID, "light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	setFloat(box.shaderID, "light.constant", 1.0f);
	setFloat(box.shaderID, "light.linear", 0.09f);
	setFloat(box.shaderID, "light.quadratic", 0.032f);
	setFloat(box.shaderID, "material.shiness", 64.0f);

	while (isWindowAlive(&base))
	{
		processInput(&base);
		clearBackground();
		for (GLuint i = 0; i < sizeof(cubePos) / sizeof(glm::vec3); ++i)
		{
			box.transform = glm::mat4(1.0f);
			translatePrimitive(&box, cubePos[i]);
			if (i % 3 == 0)
			{
				//rotatePrimitive(&box, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f), "deg");
			}
			else
			{
				//rotatePrimitive(&box, 32.0f, glm::vec3(0.2f, 0.1f, 0.3f), "deg");
			}
			setVec3(box.shaderID, "light.position", defaultCamera.cameraPosition);
			setVec3(box.shaderID, "light.direction", defaultCamera.cameraDirection);
			setFloat(box.shaderID, "light.cutOff", glm::cos(glm::radians(12.5f)));
			drawPrimitive(&box);
		}
		auto errID = glGetError();
		if (errID)
		{
			std::cout << "Error occured with ID: " << errID << std::endl;
		}

		swapBuffer(&base);
		pollEvents();
	}
	shutWindow(&base);
	return 0;
}