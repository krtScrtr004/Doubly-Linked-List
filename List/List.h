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
	template <typename T> class LinkedList;
	template <typename T> class Node;
	template <typename T> class Iterator;

	/*-----NODE CLASS-----*/
	template <typename T>
	class Node {
		// FRIEND CLASSES AND OPERATORS
		friend class LinkedList<T>;
		friend ostream& operator<<(ostream& os, const LinkedList<T>&);

		friend class Iterator<T>;

	private:
		T Data;
		Node<T> *Prev, *Next;

		Node() :															// DEFAULT CONSTRUCTOR
			Data(), 
			Prev(nullptr), 
			Next(nullptr) {}					
		Node(const Node<T>& OTHER) :										// COPY CONSTRUCTOR
			Data(OTHER.Data), 
			Prev(OTHER.Prev ? new Node<T>(*(OTHER.Prev)) : nullptr), 
			Next(OTHER.Next ? new Node<T>(*(OTHER.Next)) : nullptr) {}
	};

	/*-----ITERATOR CLASS-----*/
	template <typename T>
	class Iterator {
		// FRIEND CLASSES AND OPERATORS
		friend class LinkedList<T>;
		friend ostream& operator<<(ostream& os, const LinkedList<T>&);

	private:
		static T DefaultValue;				// STATIC MEMBER TO CALL 'T' TYPE DEFAULT CONSTRUCTOR
		Node<T> *Pointed, *Head, *Tail;

	public:
		Iterator() :									// DEFAULT CONSTRUCTOR
			Pointed(nullptr),					
			Head(nullptr), 
			Tail(nullptr) {}				
		Iterator(const Iterator<T>& OTHER) :			// COPY CONSTRUCTOR
			Pointed(OTHER.Pointed),
			Head(OTHER.Head),
			Tail(OTHER.Tail) {}
		Iterator(const LinkedList<T>& LIST) :			// CONSTRUCTOR WITH LinkedList CLASS ARGS
			Pointed(LIST.Head->Next),
			Head(LIST.Head),
			Tail(LIST.Tail) {}									

		// OVERLAODED OPERATORS
		Iterator<T>& operator=(const Iterator<T>& RHS);
		bool operator==(const Iterator<T>& RHS) const;
		bool operator!=(const Iterator<T>& RHS) const;
		Iterator<T>& operator++();
		Iterator<T>& operator++(int);
		Iterator<T>& operator+(const size_t);
		Iterator<T>& operator+=(const size_t);
		Iterator<T>& operator--();
		Iterator<T>& operator--(int);
		Iterator<T>& operator-(const size_t);
		Iterator<T>& operator-=(const size_t);
		T& operator*() const;

		Iterator<T> begin() { 
			return *this; 
		}
		Iterator<T> end() {
			Pointed = Tail;
			return *this;
		}
	};

	/*-----LINKEDLIST CLASS-----*/
	template <typename T>
	class LinkedList {
		// FRIEND CLASSES AND OPERATORS
		friend class Iterator<T>;
		friend ostream& operator<<(ostream&, const LinkedList<T>&) {
			Iterator<T> itr(RHS);
			while (itr.Pointed != nullptr) {
				os << itr.Pointed->Data << ' ';
				++itr;
			}
			return os;
		}

	private:
		Node<T> *Head, *Tail;
		size_t Size;

	public:
		LinkedList() :													// DEFAULT CONSTRUCTOR
			Size(0), 
			Head(new Node<T>), 
			Tail(new Node<T>) 
		{			
			Head->Next = Tail;
			Tail->Prev = Head;
		}
		LinkedList(const LinkedList<T>& OTHER) :						// DEFAULT CONSTRUCTOR
			Size(OTHER.Size), 
			Head(new Node<T>), 
			Tail(new Node<T>) 
		{
			Head->Next = Tail;
			Tail->Prev = Head;

			Iterator<T> itr = OTHER.Begin();
			size_t counter = 0;
			while (counter < Size && itr.Pointed != nullptr) {
				PushBack(*itr);
				++itr;
				++counter;
			}
		}

		// OPERATIONS FOR LinkedList CLASS
		void push_front(const T);
		void push_back(const T);
		void insert(const Iterator<T>&, const T);
		void insert(const Iterator<T>&, const size_t, const T);

		constexpr size_t size() const { return Size; }

		Iterator<T> begin() const { return Iterator<T>(*this).begin(); }
		Iterator<T> end() const { return Iterator<T>(*this).end(); }
	};

#include "Iterator.h"		// DEFINITIONS FOR Iterator<T> CLASS
#include "Definition.h"		// DEFINITIONS FOR LinkedList<T> CLASS
}

#endif // !LIST_H
