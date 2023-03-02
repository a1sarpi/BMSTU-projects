#include "Matrix.h"


CSRMatrix::CSRMatrix() : size(0), iptr(nullptr), 
						 jptr(nullptr), aelem(nullptr) {}

CSRMatrix::CSRMatrix(unsigned int size, unsigned int nonZeroCount,
					 unsigned int* iptr, unsigned int* jptr,
					 double* aelem)
	: size(size),
	  iptr(new unsigned int[size + 1]),
	  jptr(new unsigned int[nonZeroCount]),
	  aelem(new double[nonZeroCount])
{
	if (aelem != nullptr) {
		for (unsigned int i = 0; i < nonZeroCount; i++) {
			this->aelem[i] = aelem[i];
		}
	}
	if (jptr != nullptr) {
		for (unsigned int i = 0; i < nonZeroCount; i++) {
			this->jptr[i] = jptr[i];
		}
	}
	if (iptr != nullptr) {
		for (unsigned int i = 0; i < size + 1; i++) {
			this->iptr[i] = iptr[i];
		}
	}
}

CSRMatrix::CSRMatrix(const CSRMatrix& otherMatrix)
	: size(otherMatrix.size),
	  iptr(new unsigned int[otherMatrix.size + 1]),
	  jptr(new unsigned int[otherMatrix.nonZeroElCount()]),
	  aelem(new double[otherMatrix.nonZeroElCount()])
{
	for (unsigned int i = 0; i < otherMatrix.nonZeroElCount(); i++) {
		aelem[i] = otherMatrix.aelem[i];
	}
	if (otherMatrix.jptr != nullptr) {
		for (unsigned int i = 0; i < otherMatrix.nonZeroElCount(); i++) {
			jptr[i] = otherMatrix.jptr[i];
		}
	}
	if (otherMatrix.iptr != nullptr) {
		for (unsigned int i = 0; i < (otherMatrix.size + 1); i++) {
			iptr[i] = otherMatrix.iptr[i];
		}
	}
}

unsigned int CSRMatrix::nonZeroElCount() const
{
	return iptr[size];
}

unsigned int CSRMatrix::Size() const
{
	return size;
}

CSRMatrix CSRMatrix::operator*(const double multiplier) const
{
	CSRMatrix result(*this);
	for (unsigned int i = 0; i < nonZeroElCount(); i++) {
		result.aelem[i] *= multiplier;
	}
	return result;
}

CSRMatrix operator*(const double multiplier, const CSRMatrix& matrix)
{
	CSRMatrix result(matrix);
	return result * multiplier;
}

Vector CSRMatrix::operator*(const Vector& otherVector) const //!!! Не хватает const  для otherVector. Исправил
{
	if (otherVector.size() != size) {
		throw IncompatibleDimException();
	}
	Vector result(size);
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = iptr[i]; j < iptr[i + 1] - 1; j++) {
			result[i] = result[i] + otherVector[jptr[j]] * aelem[j];
		}
	}
	return result;
}

ostream& operator<<(ostream& os, const CSRMatrix& matrix)
{
	os << "Values: [";
	for (unsigned int i = 0; i < matrix.nonZeroElCount() - 1; i++) {
		os << matrix.aelem[i] << ", ";
	}
	os << matrix.aelem[matrix.nonZeroElCount() - 1] << "]" << endl;
	os << "Indexes of columns: [";
	for (unsigned int i = 0; i < matrix.nonZeroElCount() - 1; i++) {
		os << matrix.jptr[i] << ", ";
	}
	os << matrix.jptr[matrix.nonZeroElCount() - 1] << "]" << endl;
	os << "Indexes of rows: [";
	for (unsigned int i = 0; i < matrix.size + 1; i++) {
		os << matrix.iptr[i] << ", ";
	}
	os << matrix.iptr[matrix.size + 1] << "]" << endl;
	int rowIndex = 0, jptrElem = 0, iptrElems = 0;
	for (unsigned int i = 0; i < matrix.size; i++) {

		for (unsigned int j = 0; j < matrix.size; j++) {\
			if ((matrix.jptr[jptrElem] == j) &&
				(matrix.iptr[iptrElems + 1] - 
				 matrix.iptr[iptrElems] > rowIndex)) {
				os << setw(4) << matrix.aelem[jptrElem];
				rowIndex++;
				jptrElem++;
			}
			else {
				os << setw(4) << 0.0;
			}
		}
		os << endl;
		iptrElems++;
		rowIndex = 0;
	}
	return os;
}

istream& operator>>(istream& is, CSRMatrix& matrix)
{
	cout << "Enter size: ";
	unsigned int size;
	is >> size;
	if (size != matrix.size) {
		matrix.size = size;
		delete[] matrix.iptr;
		matrix.iptr = new unsigned int[size];
	}
	cout << "Number of nonzero elements: ";
	unsigned int nonZero;
	is >> nonZero;
	if (nonZero != matrix.nonZeroElCount()) {
		delete[] matrix.aelem;
		delete[] matrix.iptr;
		matrix.aelem = new double[nonZero];
		matrix.jptr = new unsigned int[nonZero];
	}
	cout << "iptr[" << matrix.size + 1 << "]: ";
	for (unsigned int j = 0; j < matrix.size + 1; j++) {
		is >> matrix.iptr[j];
	}
	cout << "jptr[" << matrix.nonZeroElCount() << "]: ";
	for (unsigned int j = 0; j < matrix.nonZeroElCount(); j++) {
		is >> matrix.jptr[j];
	}
	cout << "aelem[" << matrix.nonZeroElCount() << "]: ";
	for (unsigned int j = 0; j < matrix.nonZeroElCount(); j++) {
		is >> matrix.aelem[j];

	}
	return is;
}

CSRMatrix::~CSRMatrix()
{
	delete aelem;
	delete[] iptr;
	delete[] jptr;
}