#pragma once
#ifndef ITERATOR_H
#define ITERATOR_H

#include "List.h"
using namespace List;

template <typename T>
T Iterator<T>::DefaultValue = T();

template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& RHS) {
	if (*this != RHS) {
		Pointed = RHS.Pointed;
		Head = RHS.Head;
		Tail = RHS.Tail;
	}
		
	return *this;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& RHS) const {
	return (Pointed == RHS.Pointed);
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& RHS) const {
	return (Pointed != RHS.Pointed);
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
	if ((Pointed == Tail) || (Pointed->Next == Tail))
		Pointed = nullptr;
	else
		Pointed = Pointed->Next;

	return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++(int) {
	Iterator<T>* itr(this);
	if ((Pointed == Tail) || (Pointed->Next == Tail)) 
		Pointed = nullptr;
	else 
		Pointed = Pointed->Next;

	return *itr;
}

template <typename T>
Iterator<T>& Iterator<T>::operator+(const size_t N) {
	size_t count = 0;
	while (count != N && this->Pointed != nullptr) {
		++(*this);
		++count;
	}

	return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::operator+=(const size_t N) {
	return (*this) + N;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--() {
	if ((Pointed == Head) || (Pointed->Prev == Head))
		Pointed = nullptr;
	else
		Pointed = Pointed->Prev;

	return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--(int) {
	Iterator<T>* itr(this);
	if ((Pointed == Head) || (Pointed->Prev == Head))
		Pointed = nullptr;
	else
		Pointed = Pointed->Prev;

	return *itr;
}

template <typename T>
Iterator<T>& Iterator<T>::operator-(const size_t N) {
	size_t count = 0;
	while (count != N && this->Pointed != nullptr) {
		--(*this);
		++count;
	}

	return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::operator-=(const size_t N) {
	return (*this) - N;
}

template <typename T>
T& Iterator<T>::operator*() const {
	return (this->Pointed ? this->Pointed->Data : DefaultValue);
}

#endif // !ITERATOR_H