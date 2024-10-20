#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class camera
{
public:
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;		// 摄像机方向向量，也可以充当前后轴

	GLfloat pitch;
	GLfloat yaw;
	GLfloat zoom;

	glm::vec3 cameraXaxis;			// 摄像机的左右轴
	glm::vec3 cameraYaxis;			// 摄像机的上下轴

	camera();
	glm::mat4 view;
};

glm::mat4 getView(camera* cam);

extern camera defaultCamera;