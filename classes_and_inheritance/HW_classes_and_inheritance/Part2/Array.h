#pragma once
#include <iostream>
#include "OutOfRangeException.h"

using namespace std;

class Array {
protected: 
	unsigned char* mArray;
	size_t mSize;
	static const size_t MAX_SIZE = 100;

public:
	Array();
	explicit Array(size_t pSize, unsigned char *pArray);
	Array(const Array& other);
	virtual ~Array();

	size_t size() const;

	friend ostream& operator<<(ostream& os, const Array& array);
	friend istream& operator>>(istream& is, Array& array);

	unsigned char& operator[](const unsigned int index);
	const unsigned char& operator[](const unsigned int index) const;

	virtual void sum(const Array* otherArray, Array* resultArray) const;
};
