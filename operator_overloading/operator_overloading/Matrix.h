#pragma once
#include <iostream>
#include <iomanip>
#include "Vector.h"
#include "IncompatibleDimException.h"
#include "OutOfRangeException.h"

using namespace std;

class CSRMatrix
{
private:
	unsigned int size;
	unsigned int* iptr;
	unsigned int* jptr;
	double* aelem;

public:
	CSRMatrix();
	CSRMatrix(unsigned int size, unsigned int nonZeroCount, 
			  unsigned int *rowIndex, unsigned int *columnIndex, 
			  double *aelem);
	CSRMatrix(const CSRMatrix& otherMatrix);
	~CSRMatrix();
	unsigned int nonZeroElCount() const;
	unsigned int Size() const;
	
	CSRMatrix operator*(const double multiplier) const;
	//!!! Где произведение числа на матрицу? Добавил
	friend CSRMatrix operator* (const double multiplier, const CSRMatrix& matrix);

	Vector operator*(const Vector& otherVector) const;
	friend istream& operator>>(istream& is, CSRMatrix& matrix);
	friend ostream& operator<<(ostream& os, const CSRMatrix& matrix);
};