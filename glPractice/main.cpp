#include "initWin.h"
#include <iostream>
#include "preFlag.h"
#include "opsWin.h"
#include "inputProc.h"
#include "shader.h"
#include "absNode.h"

int screenWidth = 1280;
int screenHeight = 960;

int main()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	// positions all containers
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
	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
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

	setBackgroundColor(0.2f, 0.3f, 0.3f);

	setInt(box.shaderID, "material.cusTex[0]", 0);
	setInt(box.shaderID, "material.cusTex[1]", 1);
	setFloat(box.shaderID, "material.shiness", 64.0f);

	while (isWindowAlive(&base))
	{
		setVec3(box.shaderID, "dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		setVec3(box.shaderID, "dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		setVec3(box.shaderID, "dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		setVec3(box.shaderID, "dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		// point light 1
		setVec3(box.shaderID, "pointLights[0].position", pointLightPositions[0]);
		setVec3(box.shaderID, "pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		setVec3(box.shaderID, "pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		setVec3(box.shaderID, "pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		setFloat(box.shaderID, "pointLights[0].constant", 1.0f);
		setFloat(box.shaderID, "pointLights[0].linear", 0.09f);
		setFloat(box.shaderID, "pointLights[0].quadratic", 0.032f);
		// point light 2
		setVec3(box.shaderID, "pointLights[1].position", pointLightPositions[1]);
		setVec3(box.shaderID, "pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		setVec3(box.shaderID, "pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		setVec3(box.shaderID, "pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		setFloat(box.shaderID, "pointLights[1].constant", 1.0f);
		setFloat(box.shaderID, "pointLights[1].linear", 0.09f);
		setFloat(box.shaderID, "pointLights[1].quadratic", 0.032f);
		// point light 3
		setVec3(box.shaderID, "pointLights[2].position", pointLightPositions[2]);
		setVec3(box.shaderID, "pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		setVec3(box.shaderID, "pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		setVec3(box.shaderID, "pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		setFloat(box.shaderID, "pointLights[2].constant", 1.0f);
		setFloat(box.shaderID, "pointLights[2].linear", 0.09f);
		setFloat(box.shaderID, "pointLights[2].quadratic", 0.032f);
		// point light 4
		setVec3(box.shaderID, "pointLights[3].position", pointLightPositions[3]);
		setVec3(box.shaderID, "pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		setVec3(box.shaderID, "pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		setVec3(box.shaderID, "pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		setFloat(box.shaderID, "pointLights[3].constant", 1.0f);
		setFloat(box.shaderID, "pointLights[3].linear", 0.09f);
		setFloat(box.shaderID, "pointLights[3].quadratic", 0.032f);
		// spotLight
		setVec3(box.shaderID, "spotLight.position", defaultCamera.cameraPosition);
		setVec3(box.shaderID, "spotLight.direction", defaultCamera.cameraDirection);
		setVec3(box.shaderID, "spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		setVec3(box.shaderID, "spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		setVec3(box.shaderID, "spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		setFloat(box.shaderID, "spotLight.constant", 1.0f);
		setFloat(box.shaderID, "spotLight.linear", 0.09f);
		setFloat(box.shaderID, "spotLight.quadratic", 0.032f);
		setFloat(box.shaderID, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		setFloat(box.shaderID, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		processInput(&base);
		clearBackground();
		for (GLuint i = 0; i < sizeof(cubePos) / sizeof(glm::vec3); ++i)
		{
			box.transform = glm::mat4(1.0f);
			translatePrimitive(&box, cubePos[i]);
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