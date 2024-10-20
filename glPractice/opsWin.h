#pragma once
#include "initWin.h"
#include "inputProc.h"

// set the background color without flush the window
void setBackgroundColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha=1.0f);

// clear the background
void clearBackground();

// will call glfwSwapBuffers with this->window passed as argument
void swapBuffer(basicWindow* opsWindow);

// will call glfwPollEvents
void pollEvents();

// OpenGL Window Initializer
// size_callback will use default function when it's set to nullptr or NULL
// window will appear as this function successfully initialized
// value for scrFlag can be found in preFlag.h
void initWindow(basicWindow* opsObject, char const* title, int scrFlag = GLBW_SCREEN_WINDOWED, int width = 800, int height = 600,
	void (*size_callback)(GLFWwindow*, int, int) = nullptr);

// call initWindow instead
void initGLFW(basicWindow* opsObject, char const* title, int width, int height, int scrFlag);


// call initWindow instead
void initGLAD();

// return FALSE as the window should CLOSE
// return TRUE as the window should NOT CLOSE
bool isWindowAlive(basicWindow* opsObject);

// will call glfwTerminate
// will not be called automatically when basicWindow object is destroyed
// need to manually call glfwTerminate if no basicWindow object is still alive
void shutWindow(basicWindow* opsObject);