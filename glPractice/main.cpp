#include "initWin.h"
#include <iostream>
#include "preFlag.h"

// inputProc.cpp
void processInput(GLFWwindow *window);

int main()
{
	basicWindow base;
	base.initWindow("LearnOpenGL", GLBW_SCREEN_FULLSCREEN, 1920, 1200);
	while (base.isWindowAlive())
	{
		processInput(base.window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		base.swapBuffer();
		base.pollEvents();
	}
	base.shutWindow();
	return 0;
}