#include "shader.h"


void basicShader::loadShaderFromFile(char const* vertexPath, char const* fragmentPath)
{
	// keep the shader source code latest
	vcode.clear();
	fcode.clear();

	// vertex shader file and fragment shader file
	std::ifstream vfile;
	std::ifstream ffile;

	// throw exception if needed
	vfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	ffile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// read shader source code from file
		vfile.open(vertexPath);
		ffile.open(fragmentPath);

		// vertex shader stream and fragment shader stream
		std::stringstream vsstream, fsstream;

		// source code will be stored in string stream
		vsstream << vfile.rdbuf();
		fsstream << ffile.rdbuf();

		// close file
		vfile.close();
		ffile.close();

		// write the code to std::string object
		vcode = vsstream.str();
		fcode = fsstream.str();
	}
	catch (std::ifstream::failure iE)
	{
		failFlag = true;
		throw iE;
	}
	this->loadShaderFromStr(vcode.c_str(), fcode.c_str());
}

void basicShader::loadShaderFromStr(char const* vertexStr, char const* fragmentStr)
{
	// vertex shader ID and fragment shader ID
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex shader part
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexStr, nullptr);
	glCompileShader(vertex);

	// check if compiled successfully
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// vertex shader compile has failed
		failFlag = true;
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		throw vertexShaderException(infoLog);
	}
	// end of vertex shader part

	// fragment shader part
	fragment = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragment, 1, &fragmentStr, nullptr);
	glCompileShader(fragment);

	// check if compiled successfully
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// fragment shader compile has failed
		failFlag = true;
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		throw fragmentShaderException(infoLog);
	}
	// end of fragment shader part

	// program part
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);

	// check if program linked successfully
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		failFlag = true;
		glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
		throw programException(infoLog);
	}
	// end of program link part

	// delete shader as it's already linked to our program and no longer needed
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	// ready flag should only be set to TRUE while fail flag is FALSE
	setFlag = !failFlag;
}

void basicShader::use()
{
	if (setFlag)
	{
		glUseProgram(shaderID);
	}
	else
	{
		throw shaderException("A shader program hasn't finished compiled and linked.");
	}
}
