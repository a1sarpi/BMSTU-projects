#pragma once
#ifndef __OUTOFRANGEEXCEPTION_H__
#define __OUTOFRANGEEXCEPTION_H__

#include <iostream>
#include <exception>

using namespace std;

class OutOfRangeException : public exception {
private: 
	string errorMessage;

public: 
	OutOfRangeException(const string& error = "You're out of range!") : errorMessage(error) {};
	const char* what() const noexcept override;
};

#endif
