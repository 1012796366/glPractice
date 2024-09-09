#include "inputProc.h"

void processInput(basicWindow& basicWindowObj)
{
	if (glfwGetKey(basicWindowObj.window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		glfwGetKey(basicWindowObj.window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(basicWindowObj.window, true);
	}
}