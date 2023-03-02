#include "Money133.h"
#include <cmath>

float Money_Amount::toFloat() const
{
	return mFirst + static_cast <float> (mSecond) / 100;
}

Money_Amount::Money_Amount(long pRoubles, unsigned char pKopeck)
			 : Pair(pRoubles, pKopeck)
{
	memset(mRoubles, 0, 9 * sizeof(unsigned int));
	memset(mKopeck, 0, 4 * sizeof(unsigned int));
}

void Money_Amount::sum(const Pair* other, Pair* res)
{
	const Money_Amount* other_M_A = dynamic_cast <const Money_Amount*> (other);
	Money_Amount* result = dynamic_cast <Money_Amount*> (res);
	if (result == nullptr || other_M_A == nullptr) {
		throw string("Bad 'Pair to Money_Amount' cast");
	}
	result->mFirst = mFirst + other_M_A->mFirst;
	result->mSecond = mSecond + other_M_A->mSecond;
	/*for (unsigned int i = 0; i < 9; i++) {
		result->mRoubles[i] = mRoubles[i] + other_M_A->mRoubles[i];
	}
	for (unsigned int i = 0; i < 4; i++) {
		result->mKopeck[i] = mKopeck[i] + other_M_A->mKopeck[i];
	}*/
}

void Money_Amount::sub(const Pair* other, Pair* res)
{
	const Money_Amount* other_M_A = dynamic_cast <const Money_Amount*> (other);
	Money_Amount* result = dynamic_cast <Money_Amount*> (res);
	if (result == nullptr || other_M_A == nullptr) {
		throw string("Bad 'Pair to Money_Amount' cast");
	}
	result->mFirst = mFirst - other_M_A->mFirst;
	if (mSecond > other_M_A->mSecond) {
		result->mSecond = mSecond - other_M_A->mSecond;
	}
	else {
		result->mSecond = other_M_A->mSecond - mSecond;
	}
	/*for (unsigned int i = 0; i < 9; i++) {
		result->mRoubles[i] = mRoubles[i] - other_M_A->mRoubles[i];
	}
	for (unsigned int i = 0; i < 4; i++) {
		result->mKopeck[i] = mKopeck[i] - other_M_A->mKopeck[i];
	}*/
}

float Money_Amount::mult(const Pair* other)
{
	const Money_Amount* other_M_A = dynamic_cast <const Money_Amount*> (other);
	if (other_M_A == nullptr) {
		throw string("Bad 'Pair to Money_Amount' cast");
	}
	/*for (unsigned int i = 0; i < 9; i++) {
		mRoubles[i] *= other_M_A->mRoubles[i];
	}
	for (unsigned int i = 0; i < 4; i++) {
		mKopeck[i] *= other_M_A->mKopeck[i];
	}*/
	return this->toFloat() * other_M_A->toFloat();
}

void Money_Amount::mult(float multiplier, Pair* res)
{
	Money_Amount* result = dynamic_cast <Money_Amount*> (res);
	if (result == nullptr) {
		throw string("Bad 'Pair to Money_Amount' cast");
	}
	float fRes = toFloat();
	fRes *= multiplier;
	result->mFirst = floor(fRes);
	result->mSecond = (fRes - floor(fRes)) * 100;
	/*for (unsigned int i = 0; i < 9; i++) {
		result->mRoubles[i] = mRoubles[i] * floor(fRes);
	}
	for (unsigned int i = 0; i < 4; i++) {
		result->mKopeck[i] = mKopeck[i] * (fRes - floor(fRes)) * 100;
	}*/
}

float Money_Amount::div(const Pair* other)
{
	const Money_Amount* other_M_A = dynamic_cast <const Money_Amount*> (other);
	if (other_M_A == nullptr) {
		throw string("Bad 'Pair to Money_Amount' cast");
	}
	/*for (unsigned int i = 0; i < 9; i++) {
		mRoubles[i] /= other_M_A->mRoubles[i];
	}
	for (unsigned int i = 0; i < 4; i++) {
		mKopeck[i] /= other_M_A->mKopeck[i];
	}*/
	return this->toFloat() / other_M_A->toFloat();
}

void Money_Amount::div(float divider, Pair* res)
{
	Money_Amount* result = dynamic_cast <Money_Amount*> (res);
	if (result == nullptr) {
		throw string("Bad 'Pair to Money_Amount' cast");
	}
	float fRes = toFloat();
	fRes /= divider;
	result->mFirst = floor(fRes);
	result->mSecond = (fRes - floor(fRes)) * 100;
	while (result->mSecond >= 100) {
		result->mSecond -= 100;
		result->mFirst += 1;
	}
	/*for (unsigned int i = 0; i < 9; i++) {
		result->mRoubles[i] = mRoubles[i] / floor(fRes);
	}
	for (unsigned int i = 0; i < 4; i++) {
		result->mKopeck[i] = mKopeck[i] / (fRes - floor(fRes)) * 100;
	}*/
}

bool Money_Amount::operator<(const Money_Amount& other)
{
	if (mFirst < other.mFirst) {
		return true;
	}
	else if (mFirst == other.mFirst) {
		if (mSecond < other.mSecond) {
			return true;
		}
		else return false;
	}
	else return false;
}

bool Money_Amount::operator==(const Money_Amount& other)
{
	return (mFirst == other.mFirst)
		&& (mSecond == other.mSecond);
}

bool Money_Amount::operator>(const Money_Amount& other)
{
	return !(*this == other || *this < other);
}

bool Money_Amount::operator<=(const Money_Amount& other)
{
	return (*this < other || *this == other);
}

bool Money_Amount::operator>=(const Money_Amount& other)
{
	return (*this > other || *this == other);
}

istream& operator>>(istream& is, Money_Amount& ma)
{
	cout << "Enter number of bills of each nominal for roubles: " << endl;
	cout << "Roubles: " << endl;
	ma.mFirst = 0;
	ma.mSecond = 0;
	for (unsigned int i = 0; i < 9; i++) {
		cout << ma.roublesNominal[i] << ": ";
		is >> ma.mRoubles[i];
		ma.mFirst += ma.mRoubles[i] * ma.roublesNominal[i];
	}
	cout << "Kopeck: " << endl;
	for (unsigned int i = 0; i < 4; i++) {
		cout << ma.kopeckNominal[i] << ": ";
		is >> ma.mKopeck[i];
		ma.mSecond += ma.mKopeck[i] * (ma.kopeckNominal[i] * 100);
	}
	return is;
}

ostream& operator<<(ostream& os, const Money_Amount& ma)
{
	float obj = ma.toFloat();
	os << obj;
	return os;
}
