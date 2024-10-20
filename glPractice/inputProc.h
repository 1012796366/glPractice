#pragma once
#include "initWin.h"
#include "camera.h"

// inputProc.cpp
void processInput(basicWindow* opsWindow);

// inputProc.cpp
void mouseCall(GLFWwindow* opsWindow, GLdouble xpos, GLdouble ypos);

// inputProc.cpp
void scrollCall(GLFWwindow* opsWindow, GLdouble xoffset, GLdouble yoffset);
