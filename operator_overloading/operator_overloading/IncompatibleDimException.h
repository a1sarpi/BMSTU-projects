#pragma once
#ifndef __INCOMPATIBLEDIMEXCEPTION_H__
#define __INCOMPATIBLEDIMEXCEPTION_H__

#include <iostream>
#include <exception>

using namespace std;

class IncompatibleDimException : public exception {
private:
	string errorMessage;

public:
	IncompatibleDimException(const string& error = "There are wrong dimensions!") : errorMessage(error) {};
	const char* what() const noexcept override;
};

#endif
