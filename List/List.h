#pragma once
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <ostream>

using std::cerr;
using std::cout;
using std::endl;
using std::size_t;
using std::ostream;

namespace List {
	// FORWARD DECLARATION OF CLASSES
	template <typename T> class list;
	template <typename T> class node;
	template <typename T> class iterator;

	/*-----node CLASS-----*/
	template <typename T>
	class node {
		// FRIEND CLASSES AND OPERATORS
		friend class list<T>;
		friend ostream& operator<<(ostream& os, const list<T>&);

		friend class iterator<T>;

	private:
		T data_;
		node<T> *prev_, *next_;

		node() :															// DEFAULT CONSTRUCTOR
			data_(), 
			prev_(nullptr), 
			next_(nullptr) {}					
		node(const node<T>& OTHER) :										// COPY CONSTRUCTOR
			data_(OTHER.Data), 
			prev_(OTHER.Prev ? new node<T>(*(OTHER.prev_)) : nullptr), 
			next_(OTHER.Next ? new node<T>(*(OTHER.next_)) : nullptr) {}
	};

	/*-----iterator CLASS-----*/
	template <typename T>
	class iterator {
		// FRIEND CLASSES AND OPERATORS
		friend class list<T>;
		friend ostream& operator<<(ostream& os, const list<T>&);

	private:
		static T defaultValue;							// STATIC MEMBER TO CALL 'T' TYPE DEFAULT CONSTRUCTOR
		node<T> *pointed_, *head_, *tail_;

	public:
		iterator() :									// DEFAULT CONSTRUCTOR
			pointed_(nullptr),					
			head_(nullptr), 
			tail_(nullptr) {}				
		iterator(const iterator<T>& OTHER) :			// COPY CONSTRUCTOR
			pointed_(OTHER.pointed_),
			head_(OTHER.head_),
			tail_(OTHER.tail_) {}
		iterator(const list<T>& LIST) :					// CONSTRUCTOR WITH list CLASS ARGS
			pointed_(LIST.head_->next_),
			head_(LIST.head_),
			tail_(LIST.tail_) {}

		// OVERLAODED OPERATORS
		iterator<T>& operator=(const iterator<T>& RHS);
		bool operator==(const iterator<T>& RHS) const;
		bool operator!=(const iterator<T>& RHS) const;
		iterator<T>& operator++();
		iterator<T>& operator++(int);
		iterator<T>& operator+(const size_t);
		iterator<T>& operator+=(const size_t);
		iterator<T>& operator--();
		iterator<T>& operator--(int);
		iterator<T>& operator-(const size_t);
		iterator<T>& operator-=(const size_t);
		T& operator*() const;

		iterator<T> begin() { 
			return *this; 
		}
		iterator<T> end() {
			pointed_ = tail_->prev_;
			return *this;
		}
	};

	/*-----list CLASS-----*/
	template <typename T>
	class list {
		// FRIEND CLASSES AND OPERATORS
		friend class iterator<T>;
		friend ostream& operator<<(ostream& os, const list<T>& RHS) {
			iterator<T> itr(RHS);
			if (itr.pointed_ == RHS.head_ || itr.pointed_ == RHS.tail_)
				os << ' ';
			else {
				while (itr.pointed_ != nullptr) {
					os << itr.pointed_->data_ << ' ';
					++itr;
				}
			}

			return os;
		}

	private:
		node<T> *head_, * tail_;
		size_t size_;

	public:
		list() :													// DEFAULT CONSTRUCTOR
			size_(0), 
			head_(new node<T>), 
			tail_(new node<T>) 
		{			
			head_->next_ = tail_;
			tail_->prev_ = head_;
		}
		list(const list<T>& OTHER) :								// COPY CONSTRUCTOR
			size_(OTHER.size_), 
			head_(new node<T>), 
			tail_(new node<T>)
		{
			head_->next_ = tail_;
			tail_->prev_ = head_;

			iterator<T> itr = OTHER.begin();
			size_t counter = 0;
			while (counter < size_ && itr.pointed_ != nullptr) {
				push_back(*itr);
				++itr;
				++counter;
			}
		}
		~list() {
			clear();
			delete head_;
			delete tail_;
		}

		// OPERATIONS FOR list CLASS
		void push_front(const T);
		void push_back(const T);
		void insert(const iterator<T>&, const T);
		void insert(const iterator<T>&, const size_t, const T);
		void assign(const iterator<T>&, const T);
		void assign(const iterator<T>&, const iterator<T>&, const T);

		void erase(const iterator<T>&);
		void erase(iterator<T>, iterator<T>);
		void clear();

		constexpr size_t size() const { return size_; }
		constexpr T front() const { return *(iterator<T>(*this).begin()); }
		constexpr T back() const { return *(iterator<T>(*this).end()); }

		iterator<T> begin() const { return iterator<T>(*this).begin(); }
		iterator<T> end() const { return iterator<T>(*this).end(); }
	};

#include "iterator.h"		// DEFINITIONS FOR iterator<T> CLASS
#include "Definition.h"		// DEFINITIONS FOR list<T> CLASS
}

#endif // !LIST_H
