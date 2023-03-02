#include <iostream>
#include "OutOfRangeException.h"

using namespace std;

const char* OutOfRangeException::what() const noexcept
{
    return errorMessage.c_str();
}