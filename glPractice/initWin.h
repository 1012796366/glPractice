#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <initializer_list>
#include "preFlag.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

class basicWindow
{
public:
	GLFWwindow *window = nullptr;
	bool initFlag = false;

	// OpenGL Window Initializer
	// size_callback will use default function when it's set to nullptr or NULL
	// window will appear as this function successfully initialized
	// value for scrFlag can be found in preFlag.h
	void initWindow(char const* title, int scrFlag = GLBW_SCREEN_WINDOWED, int width = 800, int height = 600,
					void (*size_callback)(GLFWwindow*, int, int) = nullptr);

	// call initWindow instead
	void initGLFW(char const* title, int width, int height, int scrFlag);
	

	// call initWindow instead
	void initGLAD();
	
	// return FALSE as the window should CLOSE
	// return TRUE as the window should NOT CLOSE
	bool isWindowAlive();

	// will call glfwSwapBuffers with this->window passed as argument
	void swapBuffer();

	// will call glfwPollEvents
	void pollEvents();
	
	// will call glfwTerminate
	// will not be called automatically when basicWindow object is destroyed
	// need to manually call glfwTerminate if no basicWindow object is still alive
	void shutWindow();
};

