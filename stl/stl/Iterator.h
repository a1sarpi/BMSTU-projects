#pragma once
#include "Container.h"
#include "Exceptions.h"

// TODO: В данном файле должен быть реализован класс итератора.

template<typename _DataType>
class Vector;

template<typename _DataType>
class VectorIterator
{
private:
	Vector<_DataType>* mVector;
	unsigned int	   mCurrentI;

public: 
	friend class   Vector<_DataType>;
	using Vector = Vector<_DataType>;

	// Конструктор,   принимающий ссылку на   контейнер Vector и 
	// указатель на текущий элемент или индекс текущего элемента
	VectorIterator(Vector* pVector, unsigned int pCurrentI)
		: mVector(pVector), mCurrentI(pCurrentI)
	{}

	// Копирующий конструктор
	VectorIterator(const VectorIterator& iter)
		: mVector(iter.mVector), mCurrentI(iter.mCurrentI)
	{}

	// Деструктор
	~VectorIterator()
	{
		mVector = nullptr;
	}

	// Функции-операции

	VectorIterator& operator++() {
		if ((mCurrentI + 1) > (mVector->capacity())) {
			throw IteratorException("VectorIterator::operator++"); 
		}
		mCurrentI++;
		return *this;
	}

	VectorIterator operator++(int) {
		if ((mCurrentI + 1) > (mVector->capacity())) {
			throw IteratorException("VectorIterator::operator++(int)");
		}
		VectorIterator tmp(*this);
		mCurrentI++;
		return tmp;
	}

	VectorIterator& operator--() {
		if (mCurrentI - 1 < 0) {
			throw IteratorException("VectorIterator::operator--");
		}
		mCurrentI--;
		return *this;
	}

	VectorIterator operator--(int) {
		if (mCurrentI - 1 < 0) {
			throw IteratorException("VectorIterator::operator--(int)");
		}
		VectorIterator tmp(*this);
		mCurrentI--;
		return tmp;
	}

	_DataType& operator*() const
	{
		return mVector->mArray[mCurrentI];
	}

	VectorIterator& operator=(const VectorIterator& otherIter)
	{
		if (this == &otherIter) {
			return *this;
		}
		mCurrentI = otherIter.mCurrentI;
		mVector   = otherIter.mVector;
		return *this;
	}

	VectorIterator operator+(const int num)
	{
		if (mCurrentI - num < 0) {
			throw IteratorException("VectorIterator::operator+");
		}
		VectorIterator tmp(*this);
		tmp.mCurrentI += num;
		return tmp;
	}	
	
	VectorIterator operator-(const int num)
	{
		if (mCurrentI - num < 0) {
			throw IteratorException("VectorIterator::operator+");
		}
		VectorIterator tmp(*this);
		tmp.mCurrentI -= num;
		return tmp;
	}

	bool operator==(const VectorIterator& otherIter) const
	{
		return (mVector   ==   otherIter.mVector)
			&& (mCurrentI == otherIter.mCurrentI);
	}
	
	bool operator!=(const VectorIterator& otherIter) const
	{
		return (mVector	  !=   otherIter.mVector)
			|| (mCurrentI != otherIter.mCurrentI);
	}

	bool operator<(const VectorIterator& otherIter) const
	{
		if (mVector != otherIter.mVector) {
			throw IteratorException("VectorIterator::operator<");
		}
		return mCurrentI < otherIter.mCurrentI;
	}

	bool operator>(const VectorIterator& otherIter) const
	{
		if (mVector != otherIter.mVector) {
			throw IteratorException("VectorIterator::operator>");
		}
		return mCurrentI > otherIter.mCurrentI;
	}

	bool operator<=(const VectorIterator& otherIter) const
	{
		if (mVector != otherIter.mVector) {
			throw IteratorException("VectorIterator::operator<=");
		}
		return mCurrentI <= otherIter.mCurrentI;
	}

	bool operator>=(const VectorIterator& otherIter) const
	{
		if (mVector != otherIter.mVector) {
			throw IteratorException("VectorIterator::operator>=");
		}
		return mCurrentI >= otherIter.mCurrentI;
	}

	VectorIterator& operator+=(const int num)
	{
		if ((mVector->capacity()) <= (mCurrentI + num)) {
			throw IteratorException("VectorIterator::operator+=");
		}
		mCurrentI += num;
		return *this;
	}

	VectorIterator& operator-=(const int num)
	{
		if ((mVector->capacity()) <= (mCurrentI + num)) {
			throw IteratorException("VectorIterator::operator-=");
		}
		mCurrentI -= num;
		return *this;
	}

	_DataType* operator->() const
	{
		return &(mVector->mArray[mCurrentI]);
	}

	explicit operator _DataType()
	{
		return mVector->mArray(mCurrentI);
	}

};