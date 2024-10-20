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
	glm::vec3 cameraDirection;		// ���������������Ҳ���Գ䵱ǰ����

	GLfloat pitch;
	GLfloat yaw;
	GLfloat zoom;

	glm::vec3 cameraXaxis;			// �������������
	glm::vec3 cameraYaxis;			// �������������

	camera();
	glm::mat4 view;
};

glm::mat4 getView(camera* cam);

extern camera defaultCamera;