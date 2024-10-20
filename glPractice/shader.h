#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderException.h"

// vertexPath: path to vertex shader source code file
// fragmentPath: path to fragment shader source code file
// may throw std::ifstream::failure
GLuint loadShaderFromFile(char const* vertexPath, char const* fragmentPath);

// vertexStr: vertex shader source code in c string
// fragmentStr: fragment shader source code in c string
GLuint loadShaderFromStr(char const* vertexStr, char const* fragmentStr);

// Uniform setter
void setBool(GLuint shaderID, const std::string& name, GLboolean value);
void setInt(GLuint shaderID, const std::string& name, GLint value);
void setFloat(GLuint shaderID, const std::string& name, GLfloat value);
void setVec3(GLuint shaderID, const std::string& name, glm::vec3 value);
void setMat4(GLuint shaderID, const std::string& name, glm::mat4 value);