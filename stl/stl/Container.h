// TODO: В данном файле должен быть реализован шаблонный класс контейнера.
//       В отличие от обычных классов, реализацию шаблонных классов нельзя разбить на .h и .cpp файлы.
//       Поэтому все методы реализуются непосредственно внутри шаблонного класса.

#pragma once
#include <iostream>
#include <initializer_list>
#include "Iterator.h"
#include "Exceptions.h"

template <typename _It>
concept _Iter = requires(_It a, _It b) {
	{ a++ }    -> std::same_as<_It>;
	{ a-- }    -> std::same_as<_It>;

	{ a < b }  -> std::convertible_to<bool>;
	{ a > b }  -> std::convertible_to<bool>;

	{ a != b } -> std::convertible_to<bool>;
	{ a == b } -> std::convertible_to<bool>;

	{ *a }     -> std::same_as<iter_reference_t<_It>>;
};

template<typename _DataType>
class Vector
{
private: 
	_DataType* mArray;
	_DataType* mVecEnd;
	_DataType* mMemEnd;

public: 
	friend			 VectorIterator<_DataType>;
	using Iterator = VectorIterator<_DataType>;

	// Конструкторы

	// Конструктор по умолчанию
	Vector() : mArray(nullptr), mVecEnd(nullptr), mMemEnd(nullptr)
	{}

	// Конструктор, принимающий количество элементов и значения
	explicit Vector(int size, const _DataType& initValue = _DataType())
	{
		if (size <= 0) {
			throw OutOfRangeException("constructor that accepts the number of elements");
		}
		mArray  = new _DataType[size * 2];
		mVecEnd = mArray + size;
		mMemEnd = mArray + size * 2;
		for (unsigned int i = 0; i < size; ++i) {
			mArray[i] = initValue;
		}
	}

	// Конструктор, принимающий интервал [beg, end), заданный итераторами
	template<_Iter _IterType>
	Vector(_IterType beg, _IterType end)
	{
		mArray  = new _DataType[end - beg];
		mVecEnd = array + (end - beg);
		mMemEnd = array + (end - beg);
		unsigned int i = 0;
		while (beg != end) {
			mArray[i] = *beg;
			++i;
			++beg;
		}
	}

	// Конструктор, принимающий список инициализации std::initializer_list
	Vector(const std::initializer_list<_DataType>& list)
	{
		mArray  = new _DataType[list.size() * 2];
		mVecEnd = mArray + list.size();
		mMemEnd = mArray + list.size() * 2;
		unsigned int i = 0;
		for (const auto& elem : list) {
			mArray[i] = elem;
			++i;
		}
	}

	// Копирующий конструктор
	Vector(const Vector& vector)
	{
		mArray  = new _DataType[vector.capacity()];
		mVecEnd = mArray + vector.size();
		mMemEnd = mArray + vector.capacity();
		for (unsigned int i = 0; i < size; ++i) {
			mArray[i] = vector.mArray[i];
		}
	}

	// Конструктор переноса
	Vector(Vector&& vector)
	{
		mArray  = vector.mArray;
		mVecEnd = vector.mVecEnd;
		mMemEnd = vector.mMemEnd;

		vector.mArray  = nullptr;
		vector.mVecEnd = nullptr;
		vector.mMemEnd = nullptr;
	}

	// Деструктор
	~Vector()
	{
		delete[] mArray;
	}

	// Операторы

	// Операция присваивания с копированием
	Vector& operator=(const Vector& vector)
	{
		if (this != &vector) {
			if (size() != vector.size()) {
				delete[] mArray;
				mArray = new _DataType[vector.capacity()];
			}
			mVecEnd = mArray + vector.size();
			mMemEnd = mArray + vector.capacity();
			for (unsigned int i = 0; i < capacity(); ++i) {
				mArray[i] = vector.mArray[i];
			}
		}
		return *this;
	}

	// Операция присваивания с переносом
	Vector& operator=(Vector&& vector)
	{
		if (this != &vector) {
			delete[] mArray;

			mArray  = vector.mArray;
			mVecEnd = vector.mVecEnd;
			mMemEnd = vector.mMemEnd;

			vector.mArray  = nullptr;
			vector.mVecEnd = nullptr;
			vector.mMemEnd = nullptr;
		}
		return *this;
	}

	// Операции индексирования, возвращающие ссылку на соответствующий 
	// элемент
	_DataType& operator[](unsigned int index)
	{
		return mArray[index];
	}

	const _DataType& operator[](unsigned int index) const
	{
		return mArray[index];
	}

	// Методы

	_DataType& at(unsigned int index)
	{
		if ((index < 0) || (index > size())) {
			throw OutOfRangeException("method Vector::at");
		}
		return mArray(index); 
	}

	Iterator begin()
	{
		return Iterator(this, 0);
	}

	Iterator end()
	{
		return Iterator(this, size());
	}

	void pushBack(const _DataType& element)
	{
		int Size = 0;
		if (mArray == nullptr) {
			mArray  = new _DataType[2];
			mVecEnd =	  mArray + 1;
			mMemEnd =	  mArray + 2;
		}
		else {
			Size	= size();
			mVecEnd = mVecEnd + 1;
		}
		mArray[Size] = element;
		if (capacity() == size()) {
			unsigned int newSize     = size();
			unsigned int newCapacity = capacity();
			_DataType* newArray = new _DataType[newCapacity * 2];
			for (unsigned int i = 0; i < size(); ++i) {
				newArray[i] = mArray[i];
			}
			_DataType* tmp = mArray;
			mArray = newArray;
			mVecEnd = mArray + newSize;
			mMemEnd = mArray + newCapacity * 2;
			delete[] tmp;
		}
	}

	void popBack()
	{
		if (size() != 0) {
			mArray[size() - 1] = _DataType();
			mVecEnd = mArray + size() - 2;
		}
	}

	Iterator insert(Iterator pos, const _DataType& elem)
	{
		if (this != pos.mVector) {
			throw IteratorException("method Vector::insert(pos, elem)");
		}
		mVecEnd = mArray + size() + 1;
		int curPos = pos.mCurrentI;
		for (unsigned int i = size() - 1; i > curPos; --i) {
			mArray[i] = mArray[i - 1];
		}
		mArray[curPos] = elem;
		return pos;
	}
	
	template <_Iter _IterType>
	Iterator insert(Iterator pos, _IterType beg, _IterType end)
	{
		if ((this != pos.mVector) || (beg.mVector != end.mVector) || (beg.mCurrentI > end.mCurrentI)) {
			throw exception("CONTAINER OR ITERATOR ERROR at Vector::insert method");
		}
		for (auto val = beg; val != end; val++) {
			insert(pos, *val);
		}
		Iterator newPos(pos);
		for (auto i = beg; i != end ; i++) {
			--newPos;
		}
		return newPos;
	}

	Iterator erase(Iterator pos)
	{
		for (unsigned int i = pos.mCurrentI; i < size() - 1; ++i) {
			mArray[i] = mArray[i + 1];
		}
		mArray[size - 1] = _DataType();
		mVecEnd = array + size() - 2;
	}

	void reserve(unsigned int num) 
	{
		if (num <= 0) {
			throw string("Vector::reserve method"); // Заменить, когда добавлю исключения
		}
		unsigned int newCapacity = capacity() + num;
		unsigned int newSize     = size();
		_DataType* oldArray = mArray; 
		mArray  = new _DataType[newCapacity];
		mVecEnd = mArray + newSize - 1;
		mMemEnd = mArray + newCapacity - 1;
		for (unsigned int i = 0; i < size(); ++i) {
			mArray[i] = oldArray[i];
		}
		delete[] oldArray;
	}

	void resize(unsigned int num)
	{
		if (num <= 0) {
			throw IteratorException("Vector::resize method"); // Заменить, когда добавлю исключения
		}
		if (mArray == nullptr) {
			mArray  = new _DataType[num * 2];
			mVecEnd = mArray + num - 1;
			mMemEnd = mArray + num * 2 - 1;
			for (unsigned int i = 0; i < size() - 1; ++i) {
				mArray[i] = _DataType();
			}
		}
		else {
			unsigned int newSize     = size();
			unsigned int newCapacity = capacity();
			if (num >= capacity()) {
				newCapacity *= 2;
			}
			_DataType* oldArray = mArray;
			mArray  = new _DataType[newCapacity];
			mVecEnd = mArray + newSize	   - 1;
			mMemEnd = mArray + newCapacity - 1;
			for (unsigned int i = 0; i < newSize; ++i) {
				mArray[i] = oldArray[i];
			}
			for (unsigned int i = size(); i < newSize; ++i) {
				mArray[i] = _DataType();
			}
			delete[] oldArray;
		}
	}

	bool empty()
	{
		return mArray == mVecEnd;
	}

	unsigned int size()
	{
		return mVecEnd - mArray;
	}

	unsigned int capacity()
	{
		return mMemEnd - mArray;
	}

	void clear()
	{
		for (unsigned int i = 0; i < size(); ++i) {
			mArray[i] = _DataType();
		}
		mVecEnd = mArray;
	}

};
