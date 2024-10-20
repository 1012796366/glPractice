#include "shader.h"


GLuint loadShaderFromFile(char const* vertexPath, char const* fragmentPath)
{
	// keep the shader source code latest
	std::string vcode;
	std::string fcode;
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
	catch (std::ifstream::failure& iE)
	{
		throw iE;
	}
	return loadShaderFromStr(vcode.c_str(), fcode.c_str());
}

GLuint loadShaderFromStr(char const* vertexStr, char const* fragmentStr)
{
	// vertex shader ID and fragment shader ID
	GLuint vertex, fragment, shaderID;
	GLint success;
	GLchar infoLog[512];

	// vertex shader part
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexStr, nullptr);
	glCompileShader(vertex);

	// check if compiled successfully
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// vertex shader compile has failed
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		throw vertexShaderException(infoLog);
	}
	// end of vertex shader part

	// fragment shader part
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentStr, nullptr);
	glCompileShader(fragment);

	// check if compiled successfully
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// fragment shader compile has failed
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
		glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
		throw programException(infoLog);
	}
	// end of program link part

	// delete shader as it's already linked to our program and no longer needed
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return shaderID;
}

void setBool(GLuint shaderID, const std::string& name, GLboolean value)
{
	glUseProgram(shaderID);
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void setInt(GLuint shaderID, const std::string& name, GLint value)
{
	glUseProgram(shaderID);
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void setFloat(GLuint shaderID, const std::string& name, GLfloat value)
{
	glUseProgram(shaderID);
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void setVec3(GLuint shaderID, const std::string& name, glm::vec3 value)
{
	glUseProgram(shaderID);
	glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void setMat4(GLuint shaderID, const std::string& name, glm::mat4 value)
{
	glUseProgram(shaderID);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}