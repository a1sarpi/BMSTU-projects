#include "Array.h"
#include <iostream>

using namespace std;

Array::Array() : mSize(0), mArray(nullptr)
{}

Array::Array(size_t pSize, unsigned char* pArray) : mSize(pSize), mArray(new unsigned char[pSize])
{
	for (unsigned int i = 0; i < pSize; i++) {
		mArray[i] = pArray[i];
	}
}

Array::Array(const Array& other)
{
	mArray = new unsigned char[other.mSize];
	mSize = other.mSize;
	for (unsigned int i = 0; i < mSize; i++)
	{
		mArray[i] = other.mArray[i];
	}
}

Array::~Array()
{
	delete[] mArray;
}

size_t Array::size() const
{
	return this->mSize;
}

ostream& operator<<(ostream& os, const Array& array)
{
	string s;
	for (unsigned int i = 0; i < array.mSize; i++) {
		s += array.mArray[i];
	}
	os << s;
	return os;
}

istream& operator>>(istream& is, Array& array)
{
	cout << "Array[" << array.mSize << "]: ";
	for (unsigned int i = 0; i < array.mSize; i++) {
		is >> array.mArray[i];
	}
	return is;
}

const unsigned char& Array::operator[](const unsigned int index) const
{
	if (!(index >= 0 && index < mSize)) {
		throw OutOfRangeException();
	}
	return mArray[index];
}

unsigned char& Array::operator[](const unsigned int index)
{
	if (!(index > 0 && index <= mSize)) {
		throw OutOfRangeException();
	}
	return mArray[index];
}

void Array::sum(const Array* otherArray, Array* resultArray) const
{
	cout << "Array sum: " << endl;
	if (mSize != otherArray->mSize) {
		throw OutOfRangeException();
	}
	if (mSize != resultArray->mSize) {
		delete[] resultArray->mArray;
		resultArray->mArray = new unsigned char[mSize];
	}
	for (unsigned int i = 0; i < mSize; i++) {
		resultArray->mArray[i] = otherArray->mArray[i] + mArray[i];
	}
}