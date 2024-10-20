#include "initWin.h"
#include <iostream>
#include "preFlag.h"
#include "opsWin.h"
#include "inputProc.h"
#include "shader.h"
#include "absNode.h"

int screenWidth = 800;
int screenHeight = 600;

int main()
{
	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,		// 0
	//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,		// 1
	//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		// 2
	//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,		// 3
	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,		// 4
	//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,		// 5
	//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,		// 6
	//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,		// 7
	//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,		// 8
	//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		// 9
	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,		// 10
	//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,		// 11
	//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,		// 12
	//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,		// 13
	//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,		// 14
	//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,		// 15
	//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,		// 16
	//};
	//GLuint indices[] = {
	//	0, 1, 2,
	//	0, 2, 3,
	//	4, 5, 6,
	//	4, 6, 7,
	//	8, 9, 10,
	//	4, 8, 10,
	//	2, 11, 12,
	//	11, 12, 13,
	//	10, 14, 15,
	//	4, 10, 15,
	//	2, 3, 11,
	//	3, 11, 16
	//};
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

	addTexture(&box, loadTextureFromFile("./pic/container.jpg"));
	addTexture(&box, loadTextureFromFile("./pic/awesomeface.png"));

	setBackgroundColor(0.2f, 0.3f, 0.3f);

	setInt(box.shaderID, "cusTex1", 0);
	setInt(box.shaderID, "cusTex2", 1);

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
				rotatePrimitive(&box, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f), "deg");
			}
			else
			{
				rotatePrimitive(&box, 32.0f, glm::vec3(0.2f, 0.1f, 0.3f), "deg");
			}
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