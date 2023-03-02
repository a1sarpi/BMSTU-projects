#pragma once

using namespace std;

class Vector {

private:
	double* vector;
	unsigned int vectorSize;

public:
	Vector();
	explicit Vector(int Size);
	Vector(const Vector& otherVector);
	~Vector();

	Vector& operator=(const Vector& otherVector);
	Vector& operator+=(const Vector& otherVector);
	Vector& operator-=(const Vector& otherVector);
	Vector operator+(const Vector& otherVector);
	Vector operator-(const Vector& otherVector);

	Vector& operator+();
	Vector operator-();

	Vector operator*(const double number);
	double operator*(const Vector& other);
	friend Vector operator*(const double number, const Vector& otherVector);

	double& operator [](const unsigned int indexOfElement);
	const double& operator [](const unsigned int indexOfElement) const;
	double length() const;
	int size() const;

	friend ostream &operator<<(ostream &os, const Vector& tmp);
	friend istream &operator>>(istream &is, Vector& tmp);

	explicit operator double* () const;
};