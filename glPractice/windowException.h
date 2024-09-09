#pragma once
#include <exception>
#include <string>

class unreadyWindowException : public std::exception
{
public:
	unreadyWindowException();
	unreadyWindowException(std::string exceptionMessage);

	// exception message function
	char const* what();
private:
	std::string eMessage;
};