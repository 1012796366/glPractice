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
	GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,		// 0
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,		// 1
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		// 2
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,		// 3
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,		// 4
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,		// 5
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,		// 6
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,		// 7
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,		// 8
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		// 9
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,		// 10
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,		// 11
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,		// 12
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,		// 13
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,		// 14
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,		// 15
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,		// 16
	};
	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		4, 8, 10,
		2, 11, 12,
		11, 12, 13,
		10, 14, 15,
		4, 10, 15,
		2, 3, 11,
		3, 11, 16
	};

	basicWindow base;
	try
	{
		initWindow(&base, "LearnOpenGL", GLBW_SCREEN_WINDOWED, screenWidth, screenHeight);
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		return 1;
	}

	primitive box;
	//primitive face;
	box.vaoID = genVAO();
	box.vboID = genVBO();
	box.eboID = genEBO();
	box.shaderID = loadShaderFromFile("./Shader/vertex.vs", "./Shader/fragment.fs");

	//face.vaoID = genVAO();
	//face.vboID = genVBO();
	//face.eboID = genEBO();
	//face.shaderID = loadShaderFromFile("./Shader/vertex.vs", "./Shader/fragment.fs");

	// ↓ 导入顶点数据与序列数据 ↓
	buffVerticles(&box, vertices, sizeof(vertices));
	buffIndices(&box, indices, sizeof(indices));
	//buffVerticles(&face, vertices, sizeof(vertices));
	//buffIndices(&face, indices, sizeof(indices));
	// ↑ 导入顶点数据与序列数据 ↑

	addTexture(&box, loadTextureFromFile("./pic/container.jpg"));
	addTexture(&box, loadTextureFromFile("./pic/awesomeface.png"));
	//addTexture(&face, loadTextureFromFile("./pic/container.jpg"));
	//addTexture(&face, loadTextureFromFile("./pic/awesomeface.png"));

	setBackgroundColor(0.2f, 0.3f, 0.3f);

	setInt(box.shaderID, "cusTex1", 0);
	setInt(box.shaderID, "cusTex2", 1);
	//setInt(face.shaderID, "cusTex1", 0);
	//setInt(face.shaderID, "cusTex2", 1);
	glEnable(GL_DEPTH_TEST);
	while (isWindowAlive(&base))
	{
		processInput(base);
		clearBackground();

		translatePrimitive(&box, glm::vec3(0.4f, 0.3f, 0.2f));
		rotatePrimitive(&box, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f), "deg");
		//scalePrimitive(&box, glm::vec3(0.5, 0.5, 0.5));

		//translatePrimitive(&face, glm::vec3(-0.4f, -0.2f, 0.1f));
		//rotatePrimitive(&face, 45.0f, glm::vec3(0.7f, 0.1f, -1.0f), "deg");
		//scalePrimitive(&face, glm::vec3(0.5, 0.5, 0.5));

		drawPrimitive(&box);
		//drawPrimitive(&face);
		
		box.transform = glm::mat4(1.0f);
		//face.transform = glm::mat4(1.0f);

		
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