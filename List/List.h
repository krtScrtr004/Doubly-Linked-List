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

		Node() : Data(), Prev(nullptr), Next(nullptr) {}					// DEFAULT CONSTRUCTOR
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
		Iterator() : Pointed(nullptr), Head(nullptr), Tail(nullptr) {}				// DEFAULT CONSTRUCTOR
		Iterator(const Iterator<T>& OTHER) {
			Pointed = OTHER.Pointed;
			Head = OTHER.Head;
			Tail = OTHER.Tail;
		}
		Iterator(const LinkedList<T>& LIST) {									// CONSTRUCTOR WITH LinkedList CLASS ARGS
			Pointed = LIST.Head->Next;
			Head = LIST.Head;
			Tail = LIST.Tail;
		}

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

		Iterator<T> Begin() const { return *this; }
	};

	/*-----LINKEDLIST CLASS-----*/
	template <typename T>
	class LinkedList {
		// FRIEND CLASSES AND OPERATORS
		friend class Iterator<T>;
		friend ostream& operator<<(ostream& os, const LinkedList<T>& RHS) {
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
		LinkedList() : Size(0), Head(new Node<T>), Tail(new Node<T>) {			// DEFAULT CONSTRUCTOR
			Head->Next = Tail;
			Tail->Prev = Head;
		}
		LinkedList(const LinkedList<T>& OTHER) {}

		// OPERATIONS FOR LinkedList CLASS
		void PushFront(const T);
		void PushBack(const T);
		void Insert(const Iterator<T>&, const T);

		Iterator<T> Begin() {
			Iterator<T> begin(*this);
			return begin;
		}

		Iterator<T> End() {
			Iterator<T> end(*this);
			return end;
		}
	};

#include "Iterator.h"		// DEFINITIONS FOR Iterator<T> CLASS
#include "Definition.h"		// DEFINITIONS FOR LinkedList<T> CLASS
}

#endif // LIST_H
