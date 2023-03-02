#include "Octal.h"


//!!! Замечания аналогичны Hex. Исправил

Octal::Octal(size_t pSize, unsigned char* pOct) : Array (pSize, pOct)
{}

const int Octal::toDecimal() const
{
	int result = 0, pow = 1;
	for (unsigned int i = 0; i < mSize; i++) {
		result += static_cast <int> (mArray[i]) * pow;
		pow *= 8;
	}
	return result;
}

Octal Octal::fromDecimal(unsigned int value)
{
	int tmp = value;
	unsigned int size = 0;
	while (tmp != 0) {
		tmp /= 8;
		size++;
	}
	if (size > MAX_SIZE || size <= 0) {
		throw OutOfRangeException();
	}
	Octal result;
	result.mSize = size;
	result.mArray = new unsigned char[size];
	unsigned int i = 0;
	while (value != 0) {
		unsigned int v = value % 8;
		result.mArray[i] = v;
		value /= 8;
		i++;
	}
	return result;
}

void Octal::sum(const Array* otherArray, Array* resultArray) const
{
	const Octal* newOther = dynamic_cast <const Octal*> (otherArray);
	if (newOther != nullptr) {
		int decSum = this->toDecimal() + newOther->toDecimal();
		*dynamic_cast <Octal*> (resultArray) = fromDecimal(decSum);
	}
	else {
		throw string("Bad 'Array to Octal' cast");
	}
}

Octal& Octal::operator=(const Octal& otherOct)
{
	if (this != &otherOct) {
		if (mSize != otherOct.mSize) {
			delete[] mArray;
			mSize = otherOct.mSize;
			mArray = new unsigned char[mSize];
		}
		for (unsigned int i = 0; i < mSize; i++) {
			mArray[i] = otherOct.mArray[i];
		}
	}
	return *this;
}

Octal Octal::operator-(const Octal& otherOct)
{	
	return fromDecimal(toDecimal() - otherOct.toDecimal());
}

Octal Octal::operator/(const Octal& otherOct)
{
	if (otherOct.toDecimal() == 0) {
		throw string("Zero division!");
	}
	return fromDecimal(toDecimal() / otherOct.toDecimal());
}

Octal Octal::operator*(const Octal& otherOct)
{
	return fromDecimal(toDecimal() * otherOct.toDecimal());
}

bool Octal::operator==(const Octal& otherOct) 
{
	return toDecimal() == otherOct.toDecimal();
}

bool Octal::operator<=(const Octal& otherOct) 
{
	return toDecimal() <= otherOct.toDecimal();
}

bool Octal::operator<(const Octal& otherOct) 
{
	return toDecimal() < otherOct.toDecimal();
}

bool Octal::operator>=(const Octal& otherOct)
{
	return toDecimal() >= otherOct.toDecimal();
}

bool Octal::operator>(const Octal& otherOct)
{
	return toDecimal() > otherOct.toDecimal();
}

bool Octal::operator!=(const Octal& otherOct)
{
	return toDecimal() != otherOct.toDecimal();
}

istream& operator>>(istream& is, Octal& oct)
{
	string s;
	is >> s;
	if (oct.mSize != s.size()) {
		delete[] oct.mArray;
		oct.mArray = new unsigned char[s.size()];
		oct.mSize = s.size();
	}
	for (unsigned int i = 0; i < s.size(); i++) {
		oct.mArray[i] = s[s.size() - 1 - i] - '0';
	}
	return is;
}

ostream& operator<<(ostream& os, const Octal& oct)
{
	for (unsigned int i = 0; i < oct.mSize; i++) {
		os << static_cast <int> (oct[oct.mSize - 1 - i]);
	}
	return os;
}
