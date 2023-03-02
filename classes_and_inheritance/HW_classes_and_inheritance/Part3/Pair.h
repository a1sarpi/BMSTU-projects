#pragma once

class Pair {
protected:
	unsigned int mFirst;
	unsigned int mSecond;

public: 
	Pair() = default;
	Pair(unsigned int pFirst, unsigned int pSecond);
	
	virtual void sum(const Pair* other, Pair* res) = 0;
	virtual void sub(const Pair* other, Pair* res) = 0;
	virtual float mult(const Pair* other) = 0;
	virtual void mult(float multiplier, Pair* res) = 0;
	virtual float div(const Pair* other) = 0;
	virtual void div(float divider, Pair* res) = 0;
	
	virtual ~Pair() {};
};