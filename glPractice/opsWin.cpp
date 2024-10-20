#include "opsWin.h"

void setBackgroundColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
}

void clearBackground()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swapBuffer(basicWindow* opsWindow)
{
	glfwSwapBuffers(opsWindow->window);
}

void pollEvents()
{
	glfwPollEvents();
}

void shutWindow(basicWindow* opsObject)
{
	glfwTerminate();
	opsObject->initFlag = false;
}

void initWindow(basicWindow* opsObject, char const* title, int scrFlag, int width, int height,
	void (*size_callback)(GLFWwindow*, int, int))
{
	if (opsObject->initFlag)
	{
		// a basicWindow object should only manage 1 window at a time
		// will throw an unreadyWindowException with default exception message
		throw unreadyWindowException();
	}
	// GLFW Initialization
	try
	{
		initGLFW(opsObject, title, width, height, scrFlag);
	}
	catch (const std::runtime_error& glfwException)
	{
		throw glfwException;
	}
	// End of GLFW Initialization
	// GLAD Initialization
	try
	{
		initGLAD();
	}
	catch (const std::runtime_error& gladException)
	{
		throw gladException;
	}
	// End of GLAD Initialization

	// Register frame buffer size callback function
	// Will use default one if user doesn't specify any
	if (size_callback == nullptr) 
	{
		size_callback = framebuffer_size_callback;
	}
	glfwSetFramebufferSizeCallback(opsObject->window, size_callback);
	glfwSetInputMode(opsObject->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(opsObject->window, mouseCall);
	glfwSetScrollCallback(opsObject->window, scrollCall);
	glEnable(GL_DEPTH_TEST);
	opsObject->initFlag = true;

}

void initGLFW(basicWindow* opsObject, char const* title, int width, int height, int scrFlag)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
	auto monitor = glfwGetPrimaryMonitor();
	if (monitor == nullptr)
	{
		shutWindow(opsObject);
		throw std::runtime_error("Failed to get primary monitor.");
	}
	GLFWvidmode const* vidMode = glfwGetVideoMode(monitor);
	if (vidMode == nullptr)
	{
		shutWindow(opsObject);
		throw std::runtime_error("Failed to get video mode.");
	}

	switch (scrFlag)
	{
		// Fullscreen
	case GLBW_SCREEN_FULLSCREEN:
		opsObject->window = glfwCreateWindow(width, height, title, monitor, nullptr);
		break;
		// Fullscreen Borderless
	case GLBW_SCREEN_FULLBORDER:
		glfwWindowHint(GLFW_DECORATED, false);
		opsObject->window = glfwCreateWindow(vidMode->width, vidMode->height, title, nullptr, nullptr);
		break;
		// Windowed Borderless
	case GLBW_SCREEN_BORDERLESS:
		glfwWindowHint(GLFW_DECORATED, false);
		opsObject->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		break;	
		// Windowed
	case GLBW_SCREEN_WINDOWED:
		opsObject->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		break;
	}
	if (opsObject->window == nullptr)
	{
		shutWindow(opsObject);
		throw std::runtime_error("Failed to init GLFW window.");
	}
	glfwMakeContextCurrent(opsObject->window);
}

void initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to init GLAD.");
	}
}

bool isWindowAlive(basicWindow* opsObject)
{
	return !glfwWindowShouldClose(opsObject->window);
}
