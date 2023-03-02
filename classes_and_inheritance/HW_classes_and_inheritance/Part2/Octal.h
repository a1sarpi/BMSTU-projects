#pragma once
// ������� ����� Octal ��� ������ � ������������ ������ ������������� �������, ��������� ��� ������������� 
// ����� ������ �� 100 ��������� ���� unsigned char, ������ ������� �������� �������� ������������ ������.
// ������� ����� ����� ������� ������ (������� - � ������� �������� �������). �������� ������ ������� �������� 
// ��� �������� ������������ �������������. ����������� �������������� ��������, ����������� ���������� ��� 
// ����� � C++, � �������� ���������.

// !!! ������ ���� ���������� ��� ����������� �� Array 

#include <iostream>
#include "Array.h"
#include "OutOfRangeException.h"

using namespace std;

class Octal : public Array
{
public:
	Octal();
	Octal(size_t pSize, unsigned char* pOct);

	const int toDecimal() const;
	static Octal fromDecimal(unsigned int value);

	void sum(const Array* otherArray, Array* resultArray) const override;

	Octal& operator=(const Octal& otherOct);

	Octal operator-(const Octal& otherOct);
	Octal operator/(const Octal& otherOct);
	Octal operator*(const Octal& otherOct);

	bool operator==(const Octal& otherOct);
	bool operator<=(const Octal& otherOct);
	bool operator<(const Octal& otherOct);
	bool operator>=(const Octal& otherOct);
	bool operator>(const Octal& otherOct);
	bool operator!=(const Octal& otherOct);

	friend istream& operator>>(istream& is, Octal& oct);
	friend ostream& operator<<(ostream& os, const Octal& oct);
};