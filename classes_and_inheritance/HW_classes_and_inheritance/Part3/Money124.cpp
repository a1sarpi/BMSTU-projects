#include "Money124.h"

float Money::toFloat() const
{
	return mFirst + static_cast <float> (mSecond) / 100;
}

Money::Money(long pRoubles, unsigned char pKopeck)
	  : Pair (pRoubles, pKopeck)
{}

void Money::sum(const Pair* other, Pair* res)
{
	const Money* otherMoney = dynamic_cast <const Money*> (other);
	Money* result = dynamic_cast <Money*> (res);
	if (result == nullptr || otherMoney == nullptr) {
		throw string("Bad 'Pair to Money' cast");
	}
	result->mFirst = mFirst + otherMoney->mFirst; 
	result->mSecond = mSecond + otherMoney->mSecond;
	if (mSecond + otherMoney->mSecond > 0) {
		result->mFirst += 1;
		result->mSecond -= 100;
	}
}

void Money::sub(const Pair* other, Pair* res)
{
	const Money* otherMoney = dynamic_cast <const Money*> (other);
	Money* result = dynamic_cast <Money*> (res);
	if (result == nullptr || otherMoney == nullptr) {
		throw string("Bad 'Pair to Money' cast");
	}
	result->mFirst = mFirst - otherMoney->mFirst;
	result->mSecond += mSecond - otherMoney->mSecond;
	if (mSecond - otherMoney->mSecond < 0) {
		result->mFirst -= 1;
		result->mSecond += 100;
	}	
}

float Money::mult(const Pair* other) // Не знаю как в реальности можно перемножать деньги, но сделал так
{
	const Money* otherMoney = dynamic_cast <const Money*> (other);
	if (otherMoney == nullptr) {
		throw string("Bad 'Pair to Money' cast");
	}
	return this->toFloat() * otherMoney->toFloat();
}

void Money::mult(float multiplier, Pair* res)
{
	Money* result = dynamic_cast <Money*> (res);
	if (result == nullptr) {
		throw string("Bad 'Pair to Money' cast");
	}
	float fRes = toFloat();
	fRes *= multiplier;
	result->mFirst = floor(fRes);
	result->mSecond = (fRes - floor(fRes)) * 100;
	while (result->mSecond >= 100) {
		result->mSecond -= 100;
		result->mFirst += 1;
	}
}

float Money::div(const Pair* other)
{
	const Money* otherMoney = dynamic_cast <const Money*> (other);
	if (otherMoney == nullptr) {
		throw string("Bad 'Pair to Money' cast");
	}
	return this->toFloat() / otherMoney->toFloat();
}

void Money::div(float divider, Pair* res)
{
	Money* result = dynamic_cast <Money*> (res);
	if (result == nullptr) {
		throw string("Bad 'Pair to Money' cast");
	}
	float fRes = toFloat();
	fRes /= divider;
	result->mFirst = floor(fRes);
	result->mSecond = (fRes - floor(fRes)) * 100;
	while (result->mSecond >= 100) {
		result->mSecond -= 100;
		result->mFirst += 1;
	}
}

bool Money::operator<(const Money& other)
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

bool Money::operator==(const Money& other)
{
	return (mFirst == other.mFirst) 
		&& (mSecond  == other.mSecond);
}

bool Money::operator>(const Money& other)
{
	return !(*this == other || *this < other);
}

bool Money::operator<=(const Money& other)
{
	return (*this < other || *this == other);
}

bool Money::operator>=(const Money& other)
{
	return (*this > other || *this == other);
}

istream& operator>>(istream& is, Money& money)
{
	float amount = .0;
	is >> amount;
	money.mFirst = floor(amount);
	money.mSecond = floor((amount - floor(amount)) * 100);
	return is;
}

ostream& operator<<(ostream& os, const Money& money)
{
	float obj = money.toFloat();
	os << obj;
	return os;
}
