#include "Hex.h"

Hex::Hex(size_t pSize, unsigned char* pArray) : Array(pSize, pArray)
{ }

const int Hex::toDecimal() const
{
	int result = 0, pow = 1;
	for (unsigned int i = 0; i < mSize; i++) {
		result += static_cast <int> (mArray[i]) * pow;
		pow *= 16;
	}
	return result;
}

Hex Hex::fromDecimal(unsigned int value)
{
	int tmp = value;
	unsigned int size = 0;
	while (tmp != 0) {
		tmp /= 16;
		size++;
	}
	if (size > MAX_SIZE || size <= 0) {
		throw OutOfRangeException();
	}
	Hex result;
	result.mSize = size;
	result.mArray = new unsigned char[size];
	unsigned int i = 0;
	while (value != 0) {
		unsigned int v = value % 16;
		result.mArray[i] = v;
		value /= 16;
		i++;
	}
	return result;
}

void Hex::sum(const Array* otherArray, Array* resultArray) const
{
    //!!! Где проверка правильности приведения? Нельзя писать dynamic_cast <const Hex*> (otherArray)->toDecimal() !!
	const Hex* newOther = dynamic_cast <const Hex*> (otherArray);
	if (newOther != nullptr) {
		int decSum = this->toDecimal() + newOther->toDecimal();
		*dynamic_cast <Hex*> (resultArray) = fromDecimal(decSum);
	}
	else {
		throw string("Bad 'Array to Hex' cast");
	}
}

Hex& Hex::operator=(const Hex& otherHex)
{
    //!!! Где проверка на самоприсваивание. Добавил
	if (this != &otherHex) {
		if (mSize != otherHex.mSize) {
			delete[] mArray;
			mSize = otherHex.mSize;
			mArray = new unsigned char[mSize];
		}
		for (unsigned int i = 0; i < mSize; i++) {
			mArray[i] = otherHex.mArray[i];
		}
	}
	return *this;
}

Hex Hex::operator-(const Hex& otherHex)
{
	return fromDecimal(toDecimal() - otherHex.toDecimal());
}

Hex Hex::operator/(const Hex& otherHex)
{
	if (otherHex.toDecimal() == 0) {
		throw string("Zero division!");
	}
	return fromDecimal(toDecimal() / otherHex.toDecimal());
}

Hex Hex::operator*(const Hex& otherHex)
{
	return fromDecimal(toDecimal() * otherHex.toDecimal());
}

bool Hex::operator==(const Hex& otherHex)
{
	return toDecimal() == otherHex.toDecimal();
}

bool Hex::operator!=(const Hex& otherHex)
{
	return toDecimal() != otherHex.toDecimal();
}

bool Hex::operator>=(const Hex& otherHex)
{
	return toDecimal() >= otherHex.toDecimal();
}

bool Hex::operator<=(const Hex& otherHex)
{
	return toDecimal() <= otherHex.toDecimal();
}

bool Hex::operator>(const Hex& otherHex)
{
	return toDecimal() > otherHex.toDecimal();
}

bool Hex::operator<(const Hex& otherHex)
{
	return toDecimal() < otherHex.toDecimal();
}

istream& operator>>(istream& is, Hex& hex)
{
	string s;
	is >> s;
	if (hex.mSize != s.size()) {
		delete[] hex.mArray;
		hex.mArray = new unsigned char[s.size()];
		hex.mSize = s.size();
	}
	for (unsigned int i = 0; i < s.size(); i++) {
		if (s[s.size() - 1 - i] >= '0' && s[s.size() - 1 - i] <= '9') {
			hex.mArray[i] = s[s.size() - 1 - i] - '0';
		}
		else {
			hex.mArray[i] = s[s.size() - 1 - i] - 'A' + 10;
		}
	}
	return is;
}

ostream& operator<<(ostream& os, const Hex& hex)
{
	for (unsigned int i = 0; i < hex.mSize; i++) {
		if (hex[hex.mSize - 1 - i] >= 0 && hex[hex.mSize - 1 - i] < 10) {
			os << static_cast <int> (hex[hex.mSize - 1 - i]);
		}
		else {
			os << static_cast <unsigned char> (static_cast <int> (hex[hex.mSize - 1 - i] - 10) + 'A');
		}
	}
	return os;
}
