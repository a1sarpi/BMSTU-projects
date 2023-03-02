#pragma once
#include <iostream>

// TODO: В данном файле должны быть реализованы шаблонные функции для алгоритмов.
//       Как и в случае шаблонных классов, реализацию шаблонных функций нельзя разбить на .h и .cpp файлы.

template <typename _It>
concept ConceptIterator = requires(_It a, _It b) {
	{ ++a }    -> std::same_as<_It&>;
	{ --a }	   -> std::same_as<_It&>;
				  
	{ a++ }	   -> std::same_as<_It>;
	{ a-- }    -> std::same_as<_It>;

	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
	{ a < b }  -> std::convertible_to<bool>;
	{ a > b }  -> std::convertible_to<bool>;
				  
	{ *a }     -> std::same_as<iter_reference_t<_It>>;
};

template <typename _PredType, typename _IterType>
concept ConceptPredicate = requires(_PredType pred, _IterType i) {
	{ pred(i) } -> convertible_to<bool>;
};

template <typename _Lambda, typename _IterType>
concept ConceptLambda    = requires(_Lambda   func, _IterType i) {
	func(i);
};

template <ConceptIterator _IterType, 
	ConceptPredicate<iter_reference_t<_IterType>> _PredType>
_IterType findIf(_IterType beg, _IterType end, _PredType pred) {
	while (beg != end) {
		if (pred(*beg)) {
			break;
		}
		++beg;
	}
	_IterType result(beg);
	return result;
}

template<ConceptIterator _IterType, 
	ConceptPredicate<iter_reference_t<_IterType>> _PredType>
_IterType minElement(_IterType beg, _IterType end, _PredType pred) // Добавил для реализации сортировки с предикатом
																   // minElem с предикатом
{
	_IterType result = beg;
	while (beg != end)
	{
		if (pred(*beg, *result))
		{
			result = beg;
		}
		beg++;
	}
	return result;
}

template<ConceptIterator _IterType>
_IterType minElement(_IterType beg, _IterType end)  {
	auto minElem = beg;
	while (beg != end) {
		if (*beg < minElem) {
			minElem = beg;
		}
		++beg;
	}
	return minElem;
}


template <ConceptIterator _IterType>
_IterType maxElement(_IterType beg, _IterType end) {
	auto maxElem = beg;
	while (beg != end) {
		if (*beg > maxElem) {
			maxElem = beg;
		}
		++beg;
	}
	return maxElem;
}

template <ConceptIterator _IterType, 
	ConceptLambda<iter_reference_t<_IterType>> _OperationType>
void forEach(_IterType beg, _IterType end, _OperationType op) {
	while (beg != end) {
		op(*beg);
		beg++;
	}
}

template <ConceptIterator _IterType>
void Sort(_IterType beg, _IterType end) {                   //!!! Должна быть версия с бинарным предикатом
	for (auto iter = beg; iter != end ; ++iter) {
		iter_swap(iter, minElement(iter, end));
	}
}

template <ConceptIterator _IterType, 
	ConceptPredicate<iter_reference_t<_IterType>> _PredType> 
void Sort(_IterType beg, _IterType end, _PredType pred)		//!!! Добавил.
{
	for (; beg != end; ++beg)
	{
		std::iter_swap(beg, minElement(beg, end, pred));
	}
}


template <ConceptIterator _IterTypeA, ConceptIterator _IterTypeB, 
		  ConceptPredicate<iter_reference_t<_IterTypeA>> _PredType>
_IterTypeB copyIf(_IterTypeA sourceBeg, _IterTypeA sourceEnd, 
				  _IterTypeB destBeg,	_PredType		pred) {
	while (sourceBeg != sourceEnd) {
		if (pred(*sourceBeg)) {
			*destBeg = *sourceBeg;
			++destBeg;
		}
		++sourceBeg;
	}
	return destBeg;
}


