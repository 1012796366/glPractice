#pragma once
#include <exception>
#include <string>

class shaderException : public std::exception
{
public:
	shaderException();
	shaderException(std::string exceptionMessage);

	// exception message function
	char const* what();
private:
	std::string eMessage;
};

class vertexShaderException : public shaderException
{
public:
	vertexShaderException();
	vertexShaderException(std::string exceptionMessage);

	// use parent's what() function instead
private:
};

class fragmentShaderException : public shaderException
{
public:
	fragmentShaderException();
	fragmentShaderException(std::string exceptionMessage);

	// use parent's what() function instead
};

class programException : public shaderException
{
public:
	programException();
	programException(std::string exceptionMessage);

	// use parent's what() function instead
};