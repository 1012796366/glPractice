#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include "preFlag.h"
#include "windowException.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

struct basicWindow
{
public:
	GLFWwindow *window = nullptr;
	bool initFlag = false;
};

