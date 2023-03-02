#pragma once
// Создать класс Octal для работы с беззнаковыми целыми восьмеричными числами, используя для представления 
// числа массив из 100 элементов типа unsigned char, каждый элемент которого является восьмеричной цифрой.
// Младшая цифра имеет меньший индекс (единицы - в нулевом элементе массива). Реальный размер массива задается 
// как аргумент конструктора инициализации. Реалтзовать арифметические операции, аналогичные встроенным для 
// целых в C++, и операции сравнения.

// !!! Должен быть реализован как производный от Array 

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