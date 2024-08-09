#include "shaderException.h"

shaderException::shaderException()
{
	eMessage = "A shader exception has occured.";
}

shaderException::shaderException(std::string exceptionMessage)
{
	eMessage = exceptionMessage;
}

char const* shaderException::what()
{
	return eMessage.c_str();
}

vertexShaderException::vertexShaderException()
{
	// pass
}

vertexShaderException::vertexShaderException(std::string exceptionMessage)
	: shaderException(exceptionMessage)
{
	// pass
}

fragmentShaderException::fragmentShaderException()
{
	// pass
}

fragmentShaderException::fragmentShaderException(std::string exceptionMessage)
	: shaderException(exceptionMessage)
{
	// pass
}

programException::programException()
{
	// pass
}

programException::programException(std::string exceptionMessage)
	: shaderException(exceptionMessage)
{
	// pass
}