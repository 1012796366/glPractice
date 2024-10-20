#include "inputProc.h"

void processInput(basicWindow* opsWindow)
{
	static GLfloat deltaTime = 0.0f;			// 当前帧和上一帧的时间差
	static GLfloat lastFrame = 0.0f;			// 上一帧用时
	GLfloat currentFrame = (GLfloat)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	GLfloat cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(opsWindow->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(opsWindow->window, true);
	}
	if (glfwGetKey(opsWindow->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		defaultCamera.cameraPosition += cameraSpeed * defaultCamera.cameraDirection ;
	}
	if (glfwGetKey(opsWindow->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		defaultCamera.cameraPosition -= cameraSpeed * defaultCamera.cameraDirection;
	}
	if (glfwGetKey(opsWindow->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		defaultCamera.cameraPosition -= glm::normalize(glm::cross(defaultCamera.cameraDirection, defaultCamera.cameraYaxis)) * cameraSpeed;
	}
	if (glfwGetKey(opsWindow->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		defaultCamera.cameraPosition += glm::normalize(glm::cross(defaultCamera.cameraDirection, defaultCamera.cameraYaxis)) * cameraSpeed;
	}
	if (glfwGetKey(opsWindow->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		defaultCamera.cameraPosition += cameraSpeed * defaultCamera.cameraYaxis;
	}
	if (glfwGetKey(opsWindow->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		defaultCamera.cameraPosition -= cameraSpeed * defaultCamera.cameraYaxis;
	}
}

void mouseCall(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
{
	static GLfloat lastX = 400;
	static GLfloat lastY = 300;
	static GLboolean firstMouse = true;		// 可以解决初次切屏的时候会卡一下的问题

	if (firstMouse)
	{
		lastX = (GLfloat)xpos;
		lastY = (GLfloat)ypos;
		firstMouse = false;
	}
	GLfloat xoffset = (GLfloat)xpos - lastX;
	GLfloat yoffset = lastY - (GLfloat)ypos;

	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;

	float sensitivity = 0.05f;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	defaultCamera.yaw += xoffset;
	defaultCamera.pitch += yoffset;
	
	if (defaultCamera.pitch >= 89.0f)
	{
		defaultCamera.pitch = 89.0f;
	}
	else if (defaultCamera.pitch < -89.0f)
	{
		defaultCamera.pitch = -89.0f;
	}

	static glm::vec3 front;
	front.x = cos(glm::radians(defaultCamera.yaw)) * cos(glm::radians(defaultCamera.pitch));
	front.y = sin(glm::radians(defaultCamera.pitch));
	front.z = sin(glm::radians(defaultCamera.yaw)) * cos(glm::radians(defaultCamera.pitch));
	defaultCamera.cameraDirection = glm::normalize(front);
}

void scrollCall(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{
	auto xoff = (GLfloat)xoffset;
	auto yoff = (GLfloat)yoffset;

	defaultCamera.zoom -= yoff;
	if (defaultCamera.zoom <= 1.0f)
	{
		defaultCamera.zoom = 1.0f;
	}
	if (defaultCamera.zoom >= 120.0f)
	{
		defaultCamera.zoom = 120.0f;
	}

}