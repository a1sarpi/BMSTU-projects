#include <iostream>
#include "IncompatibleDimException.h"

using namespace std;

const char* IncompatibleDimException::what() const noexcept
{
	return errorMessage.c_str();
}
