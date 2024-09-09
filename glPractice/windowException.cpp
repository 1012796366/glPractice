#include "windowException.h"

unreadyWindowException::unreadyWindowException()
{
	eMessage = "Failed to switch to an unready window object.";
}

unreadyWindowException::unreadyWindowException(std::string exceptionMessage)
{
	eMessage = exceptionMessage;
}

char const* unreadyWindowException::what()
{
	return eMessage.c_str();
}
