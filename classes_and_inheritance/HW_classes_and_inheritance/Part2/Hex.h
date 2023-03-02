#pragma once
#include "Array.h"

using namespace std;

class Hex : public Array {
private:

public:
	Hex() = default; // Исправил
	Hex(size_t pSize, unsigned char* pArray);

	const int toDecimal() const;
	static Hex fromDecimal(unsigned int value);

	void sum(const Array* otherArray, Array* resultArray) const override;

	Hex& operator=(const Hex& otherHex);

	Hex operator-(const Hex& otherHex);
	Hex operator/(const Hex& otherHex);
	Hex operator*(const Hex& otherHex);

	bool operator==(const Hex& otherHex);
	bool operator!=(const Hex& otherHex);
	bool operator>=(const Hex& otherHex);
	bool operator<=(const Hex& otherHex);
	bool operator>(const Hex& otherHex);
	bool operator<(const Hex& otherHex);

	friend istream& operator>>(istream& is, Hex& hex);
	friend ostream& operator<<(ostream& os, const Hex& hex);
};