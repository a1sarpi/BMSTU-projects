#pragma once

#include <iostream>
#include "Pair.h"
#include <iostream>

using namespace std;

class Money : public Pair {
private:
	float toFloat() const;

public:
	Money() = default;
	Money(long pRoubles, unsigned char pKopeck);

	void sum(const Pair* other, Pair* res) override;
	void sub(const Pair* other, Pair* res) override;
	float mult(const Pair* other) override;
	void mult(float multiplier, Pair* res) override;
	float div(const Pair* other) override;
	void div(float divider, Pair* res) override;

	bool operator<(const Money& other);
	bool operator>(const Money& other);
	bool operator<=(const Money& other);
	bool operator>=(const Money& other);
	bool operator==(const Money& other);

	friend istream& operator>>(istream& is, Money& money);
	friend ostream& operator<<(ostream& os, const Money& money);

};
