#pragma once
#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <iostream>
#include <exception>

using namespace std;

class OutOfRangeException : public exception 
{
private:
	string errorMessage;

public:
	OutOfRangeException(const string& error);
	const char* what() const noexcept override;

};

class IteratorException : public exception
{
private:
	string errorMessage;

public:
	IteratorException(const string& error);
	const char* what() const noexcept override;

};

#endif