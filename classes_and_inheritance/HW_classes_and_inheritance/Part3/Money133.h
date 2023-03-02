#pragma once
#include "Pair.h"
#include <iostream>

using namespace std;

class Money_Amount : public Pair {
private:
	int mRoubles[9];
	int mKopeck[4];

	static constexpr int roublesNominal[9] = { 1, 2, 5, 10, 50, 100, 500, 1000, 5000 };
	static constexpr float kopeckNominal[4] = { 0.01, 0.05, 0.1, 0.5 };

	float toFloat() const;

public: 
	Money_Amount() = default;
	Money_Amount(long pRoubles, unsigned char pKopeck);

	void sum(const Pair* other, Pair* res) override;
	void sub(const Pair* other, Pair* res) override;
	float mult(const Pair* other) override;
	void mult(float multiplier, Pair* res) override;
	float div(const Pair* other) override;
	void div(float divider, Pair* res) override;

	bool operator<(const Money_Amount& other);
	bool operator>(const Money_Amount& other);
	bool operator<=(const Money_Amount& other);
	bool operator>=(const Money_Amount& other);
	bool operator==(const Money_Amount& other);

	friend istream& operator>>(istream& is, Money_Amount& ma);
	friend ostream& operator<<(ostream& os, const Money_Amount& ma);

};