#include "initWin.h"

void basicWindow::shutWindow()
{
	glfwTerminate();
}

void basicWindow::initWindow(char const* title, int scrFlag, int width, int height,
	void (*size_callback)(GLFWwindow*, int, int))
{
	if (initFlag)
	{
		return;
	}
	// GLFW Initialization
	try
	{
		initGLFW(title, width, height, scrFlag);
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
	glfwSetFramebufferSizeCallback(this->window, size_callback);
	initFlag = true;
}

void basicWindow::initGLFW(char const* title, int width, int height, int scrFlag)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (monitor == nullptr)
	{
		shutWindow();
		throw std::runtime_error("Failed to get primary monitor.");
	}
	GLFWvidmode const* vidMode = glfwGetVideoMode(monitor);
	if (vidMode == nullptr)
	{
		shutWindow();
		throw std::runtime_error("Failed to get video mode.");
	}

	switch (scrFlag)
	{
		// Fullscreen
	case GLBW_SCREEN_FULLSCREEN:
		this->window = glfwCreateWindow(width, height, title, monitor, nullptr);
		break;
		// Fullscreen Borderless
	case GLBW_SCREEN_FULLBORDER:
		this->window = glfwCreateWindow(vidMode->width, vidMode->height, title, monitor, nullptr);
		break;
		// Windowed Borderless
	case GLBW_SCREEN_BORDERLESS:
		glfwWindowHint(GLFW_DECORATED, false);
		this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		break;
		// Windowed
	case GLBW_SCREEN_WINDOWED:
		this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		break;
	}
	if (this->window == nullptr)
	{
		shutWindow();
		throw std::runtime_error("Failed to init GLFW window.");
	}
	glfwMakeContextCurrent(this->window);
}

void basicWindow::initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to init GLAD.");
	}
}

bool basicWindow::isWindowAlive()
{
	return !glfwWindowShouldClose(this->window);
}

void basicWindow::swapBuffer()
{
	glfwSwapBuffers(this->window);
}

void basicWindow::pollEvents()
{
	glfwPollEvents();
}