#include "initWin.h"
#include <iostream>
#include "preFlag.h"

// inputProc.cpp
void processInput(GLFWwindow *window);

int main()
{
	basicWindow base;
	base.initWindow("LearnOpenGL", GLBW_SCREEN_FULLBORDER);
	base.setBackgroundColor(0.2f, 0.3f, 0.3f);
	
	while (base.isWindowAlive())
	{
		processInput(base.window);
		base.clearBackgroundColor();

		base.swapBuffer();
		base.pollEvents();
	}
	base.shutWindow();
	return 0;
}