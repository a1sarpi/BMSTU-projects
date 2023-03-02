#include <iostream>
#include "Vector.h"
#include <cmath>
#include "OutOfRangeException.h"
#include "IncompatibleDimException.h"

using namespace std;

Vector::Vector() : vectorSize(0), vector(nullptr) {}

Vector::Vector(int Size) : vectorSize(Size), vector(nullptr)
{
	if (Size < 1) {
		throw OutOfRangeException();
	}
	else {
		vector = new double[Size];
		for (unsigned int i = 0; i < Size; i++) {
			vector[i] = 0;
		}
	}

}

Vector::Vector(const Vector& otherVector)
{
	vectorSize = otherVector.vectorSize;
	vector = new double[vectorSize];
	for (unsigned int i = 0; i < vectorSize; i++) {
		vector[i] = otherVector.vector[i];
	}
}

Vector::~Vector()
{
	delete[] vector;
}

Vector& Vector::operator=(const Vector& otherVector)
{
	if (this != &otherVector) {
		if (this->vectorSize != otherVector.vectorSize) {
			delete[] vector;
			vectorSize = otherVector.vectorSize;
			vector = new double[vectorSize];
		}
		for (unsigned int i = 0; i < vectorSize; i++) {
			vector[i] = otherVector.vector[i];
		}
		//!!! Потерян return. Исправил.
		return *this;
	}
	else {
		return *this;
	}
}

Vector& Vector::operator+=(const Vector& otherVector)
{
	if (vectorSize != otherVector.vectorSize) {
		throw IncompatibleDimException();
	}
	else {
		for (unsigned int i = 0; i < vectorSize; i++) {
			vector[i] += otherVector.vector[i];
		}
	}
	return *this;
}

Vector& Vector::operator-=(const Vector& otherVector)
{
	if (vectorSize != otherVector.vectorSize) {
		throw IncompatibleDimException();
	}
	else {
		for (unsigned int i = 0; i < vectorSize; i++) {
			vector[i] -= otherVector.vector[i];
		}
	}
	return *this;
}

Vector Vector::operator+(const Vector& otherVector)
{
	if (vectorSize != otherVector.vectorSize) {
		throw IncompatibleDimException();
	}
	Vector tmp(this->vectorSize);
	for (unsigned int i = 0; i < tmp.vectorSize; i++) {
		tmp.vector[i] = this->vector[i] + otherVector.vector[i];
	}
	return tmp;
}

Vector Vector::operator-(const Vector& otherVector)
{
	if (vectorSize != otherVector.vectorSize) {
		throw IncompatibleDimException();
	}
	Vector tmp(this->vectorSize);
	for (unsigned int i = 0; i < tmp.vectorSize; i++) {
		tmp.vector[i] = this->vector[i] - otherVector.vector[i];
	}
	return tmp;
}

Vector &Vector::operator+() //!!! Лишнее копирование при возврате. Исправил.
{
	return *this;
}

Vector Vector::operator-()
{
	Vector tmp(*this);
	for (unsigned int i = 0; i < tmp.vectorSize; i++) {
		tmp.vector[i] *= (-1);
	}
	return tmp;
}

Vector Vector::operator*(const double number) 
{
	Vector tmp(*this);
	for (unsigned int i = 0; i < tmp.vectorSize; i++) {
		tmp.vector[i] = vector[i] * number;
	}
	return tmp;
}

double Vector::operator*(const Vector& otherVector)
{
	if (this->vectorSize != otherVector.vectorSize) {
		throw IncompatibleDimException();
	}
	double result = 0;
	for (unsigned int i = 0; i < this->vectorSize; i++) {
		result += this->vector[i] * otherVector.vector[i];
	}
	return result;
}

Vector operator*(const double number, const Vector& otherVector)
{
	Vector tmp(otherVector.vectorSize);
	for (unsigned int i = 0; i < tmp.vectorSize; i++) {
		tmp.vector[i] = number * otherVector.vector[i];
	}
	return tmp;
}

//!!! Должно быть 2 версии: для четния и для записи. Эта версия не будет работать для const Vector&. Добавил вторую версию.

double& Vector::operator[](const unsigned int indexOfElement)
{
	if (indexOfElement > vectorSize) {
		throw OutOfRangeException();
	}
	return this->vector[indexOfElement];
}

const double& Vector::operator[](const unsigned int indexOfElement) const
{
	if ((indexOfElement > vectorSize) || (indexOfElement < 0)) {
		throw OutOfRangeException();
	}
	return vector[indexOfElement];
}

double Vector::length() const
{
	double result = .0;
	for (int i = 0; i < vectorSize; i++) {
		result += vector[i] * vector[i];
	}
	return sqrt(result);
}

int Vector::size() const
{
	return vectorSize;
}

ostream& operator<<(ostream& os, const Vector& tmp)
{
	for (unsigned int i = 0; i < tmp.vectorSize; i++) {
		os << tmp.vector[i] << ' ';
	}
	return os;
}

istream& operator>>(istream& is, Vector& tmp)
{
	int userSize;
	cout << "Enter vector size: ";
	is >> userSize;
	if (userSize != tmp.vectorSize) {
		cout << "Memory were overwright" << endl;
		delete[] tmp.vector;
		tmp.vectorSize = userSize;
		tmp.vector = new double[tmp.vectorSize];
	}
	cout << "Enter coordinate values: " << endl;
	for (int i = 0; i < tmp.vectorSize; i++) {
		is >> tmp.vector[i];
	}
	return is;
}

Vector::operator double *() const 
{
	return vector;
}