#pragma once
#ifndef iterator_H
#define iterator_H

#include "List.h"
using namespace List;

template <typename T>
T iterator<T>::defaultValue = T();

template <typename T>
iterator<T>& iterator<T>::operator=(const iterator<T>& RHS) {
	if (*this != RHS) {
		pointed_ = RHS.pointed_;
		head_ = RHS.head_;
		tail_ = RHS.tail_;
	}
		
	return *this;
}

template <typename T>
bool iterator<T>::operator==(const iterator<T>& RHS) const {
	return (pointed_ == RHS.pointed_);
}

template <typename T>
bool iterator<T>::operator!=(const iterator<T>& RHS) const {
	return (pointed_ != RHS.pointed_);
}

template <typename T>
iterator<T>& iterator<T>::operator++() {
	if ((pointed_ == tail_) || (pointed_->next_ == tail_))
		pointed_ = tail_;
	else
		pointed_ = pointed_->next_;

	return *this;
}

template <typename T>
iterator<T>& iterator<T>::operator++(int) {
	iterator<T>* itr(this);
	if ((pointed_ == tail_) || (pointed_->next_ == tail_))
		pointed_ = tail_;
	else 
		pointed_ = pointed_->next_;

	return *itr;
}

template <typename T>
iterator<T>& iterator<T>::operator+(const size_t N) {
	size_t count = 0;
	while (count < N && pointed_ != tail_) {
		++(*this);
		++count;
	}

	return *this;
}

template <typename T>
iterator<T>& iterator<T>::operator+=(const size_t N) {
	return (*this) + N;
}

template <typename T>
iterator<T>& iterator<T>::operator--() {
	if ((pointed_ == head_) || (pointed_->prev_ == head_))
		pointed_ = head_;
	else
		pointed_ = pointed_->prev_;

	return *this;
}

template <typename T>
iterator<T>& iterator<T>::operator--(int) {
	iterator<T>* itr(this);
	if ((pointed_ == head_) || (pointed_->prev_ == head_))
		pointed_ = head_;
	else
		pointed_ = pointed_->prev_;

	return *itr;
}

template <typename T>
iterator<T>& iterator<T>::operator-(const size_t N) {
	size_t count = 0;
	while (count < N && pointed_ != head_) {
		--(*this);
		++count;
	}

	return *this;
}

template <typename T>
iterator<T>& iterator<T>::operator-=(const size_t N) {
	return (*this) - N;
}

template <typename T>
T& iterator<T>::operator*() const {
	return (pointed_ ? pointed_->data_ : defaultValue);
}

#endif // !iterator_H