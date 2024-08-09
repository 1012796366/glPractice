#pragma once
#include <glad/glad.h>
#include <forward_list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shaderException.h"

class basicShader
{
public:
	// shader ID
	unsigned int shaderID;

	// vertex shader code and fragment shader code
	std::string vcode;
	std::string fcode;

	// failure flag
	bool failFlag = false;

	// ready flag
	bool setFlag = false;
	std::forward_list<std::string> errLog;

	// vertexPath: path to vertex shader source code file
	// fragmentPath: path to fragment shader source code file
	// may throw std::ifstream::failure
	void loadShaderFromFile(char const* vertexPath, char const* fragmentPath);

	// vertexStr: vertex shader source code in c string
	// fragmentStr: fragment shader source code in c string
	void loadShaderFromStr(char const* vertexStr, char const* fragmentStr);

	// enable current shader
	void use();
};