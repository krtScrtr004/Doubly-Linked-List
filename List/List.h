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
	// FORWARD DECLARATION
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
		node<T>* prev_, * next_;

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
		static T defaultValue;							// DEFAULT VALUE FOR T
		node<T> *pointed_, *head_, *tail_;

	private:

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

		// OVERLOADED OPERATORS

		// EQUALS OPERATOR
		iterator<T>& operator=(const iterator<T>& RHS) {
			if (*this != RHS) {
				pointed_ = RHS.pointed_;
				head_ = RHS.head_;
				tail_ = RHS.tail_;
			}

			return *this;
		}

		// EUQALITY OPERATOR
		bool operator==(const iterator<T>& RHS) const {
			return (pointed_ == RHS.pointed_);
		}

		// NON-EQUALITY OPERATOR
		bool operator!=(const iterator<T>& RHS) const {
			return (pointed_ != RHS.pointed_);
		}

		// PRE-INCREMENT OPERATOR
		iterator<T>& operator++() {
			if ((pointed_ == tail_) || (pointed_->next_ == tail_))
				pointed_ = tail_;
			else
				pointed_ = pointed_->next_;

			return *this;
		}

		// POST-INCREMENT OPERATOR
		iterator<T>& operator++(int) {
			iterator<T>* itr(this);
			if ((pointed_ == tail_) || (pointed_->next_ == tail_))
				pointed_ = tail_;
			else
				pointed_ = pointed_->next_;

			return *itr;
		}

		// ADDITION OPERATOR
		iterator<T>& operator+(const size_t N) {
			size_t count = 0;
			while (count < N && pointed_ != tail_) {
				++(*this);
				++count;
			}

			return *this;
		}

		// ADDITION ASSIGNMENT OPERATOR
		iterator<T>& operator+=(const size_t N) { 
			return (*this) + N; 
		}

		// PRE-DECREMENT OPERATOR
		iterator<T>& operator--() {
			if ((pointed_ == head_) || (pointed_->prev_ == head_))
				pointed_ = head_;
			else
				pointed_ = pointed_->prev_;

			return *this;
		}

		// POST-DECREMENT OPERATOR
		iterator<T>& operator--(int) {
			iterator<T>* itr(this);
			if ((pointed_ == head_) || (pointed_->prev_ == head_))
				pointed_ = head_;
			else
				pointed_ = pointed_->prev_;

			return *itr;
		}

		// SUBTRACTION OPERATOR
		iterator<T>& operator-(const size_t N) {
			size_t count = 0;
			while (count < N && pointed_ != head_) {
				--(*this);
				++count;
			}

			return *this;
		}

		// SUCTRACTION ASSIGNMENT OPERATOR
		iterator<T>& operator-=(const size_t N) { 
			return (*this) - N; 
		}

		// ARROW OPERATOR
		node<T>* operator->() { 
			return this->pointed_; 
		}

		// DEREFENCE OPERATOR
		T& operator*() const { 
			return (pointed_ ? pointed_->data_ : defaultValue); 
		}

		// TYPE CONVERSION OPERATOR (to node<T>*)
		operator node<T>*() const { 
			return this->pointed_; 
		}

		// BEGIN ITERATOR
		iterator<T> begin() { 
			return *this; 
		}

		// END ITERATOR (One node past last element)
		iterator<T> end() {
			pointed_ = tail_;
			return *this;
		}
	};

	// CALL 'T' TYPE DEFAULT CONSTRUCTOR
	template <typename T>
	T iterator<T>::defaultValue = T();

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
				while (itr.pointed_ != RHS.tail_) {
					os << itr.pointed_->data_ << ' ';
					++itr;
				}
			}

			return os;
		}

	private:
		node<T>* head_, * tail_;
		size_t size_;

	private:
		// SORT FUNCTION
		node<T>* sort(node<T>* first) {
			if (first == tail_ || first->next_ == tail_)
				return first;

			node<T>* second = split(first);
			first = sort(first);
			second = sort(second);

			return merge(first, second);
		}

		// SPLIT FUNCTION (UTILITY FOR SORT FUNCION)
		node<T>* split(node<T>* head) {
			if (head == tail_ || head->next_ == tail_)
				return nullptr;

			node<T>* slow = head;
			node<T>* fast = head;

			while (fast != nullptr && fast->next_ != nullptr &&
				fast != tail_ && fast->next_ != tail_) {
				slow = slow->next_;
				fast = fast->next_->next_;
			}

			// ADJUST BOUNDS OF SPLIT LIST
			node<T>* second = slow;
			slow->prev_->next_ = tail_;
			second->prev_ = head_;

			return second;
		}

		// MERGE FUNCTION (UTILITY FOR SORT FUNCTION)
		node<T>* merge(node<T>* n1, node<T>* n2) {
			if (n1 == nullptr || n1 == head_ || n1 == tail_) return n2;
			if (n2 == nullptr || n2 == head_ || n2 == tail_) return n1;

			if (n1->data_ <= n2->data_) {
				n1->next_ = merge(n1->next_, n2);
				n1->next_->prev_ = n1;
				return n1;
			}
			else {
				n2->next_ = merge(n1, n2->next_);
				n2->next_->prev_ = n2;
				return n2;
			}

			return nullptr;
		}

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
			size_(0), 
			head_(new node<T>), 
			tail_(new node<T>)
		{
			head_->next_ = tail_;
			tail_->prev_ = head_;
			*this = OTHER;
		}
		list(const size_t SIZE) :									// CONSTRUCTOR WITH SIZE ARGS
			size_(0),
			head_(new node<T>),
			tail_(new node<T>)
		{									
			head_->next_ = tail_;
			tail_->prev_ = head_;

			size_t count = 0;
			while (count != SIZE) {
				push_back(T());
				++count;
			}
		}
		list(const size_t SIZE, const T DATA) :						// CONSTRUCTOR WITH SIZE AND DATA ARGS
			size_(0),
			head_(new node<T>),
			tail_(new node<T>)
		{
			head_->next_ = tail_;
			tail_->prev_ = head_;

			size_t count = 0;
			while (count != SIZE) {
				push_back(DATA);
				++count;
			}
		}
		~list() {
			clear();
			delete head_;
			delete tail_;
		}

		// OVERLOADED OPERATORS FOR list CLASS

		// EQUALS OPERATOR
		list<T>& operator=(const list<T>& RHS) {
			if (*this != RHS) {
				iterator<T> itr = RHS.begin();
				while (itr != RHS.tail_) {
					push_back(*itr);
					++itr;
				}
			}

			return *this;
		}

		// EQUALITY OPERATOR
		bool operator==(const list<T>& OTHER) const {
			if (head_ != OTHER.head_ && tail_ != OTHER.tail_)
				return false;

			if (size_ != OTHER.size_)
				return false;

			iterator<T> temp(*this), temp1(OTHER);
			while (temp != tail_) {
				if (temp != temp1) return false;
				++temp;
				++temp1;
			}

			return true;
		}

		// NON EQUALITY OPERATOR
		bool operator!=(const list<T>& OTHER) const {
			if (head_ == OTHER.head_ && tail_ == OTHER.tail_)
				return false;

			if (size_ == OTHER.size_)
				return false;

			iterator<T> temp(*this), temp1(OTHER);
			while (temp != tail_) {
				if (temp == temp1) return false;
				++temp;
				++temp1;
			}

			return true;
		}

		// GREATER THAN OPERATOR
		bool operator>(const list<T>& RHS) const {
			iterator<T> temp(*this), temp1(RHS);
			while (temp != tail_ && temp1 != temp1.tail_) {
				if (*temp < *temp1) return false;
				++temp;
				++temp1;
			}

			return (size_ > RHS.size_);
		}

		// GREATER THAN OR EQUAL TO OPERATOR
		bool operator>=(const list<T>& RHS) const {
			iterator<T> temp(*this), temp1(RHS);
			while (temp != tail_ && temp1 != temp1.tail_) {
				if (*temp < *temp1) return false;
				++temp;
				++temp1;
			}

			return (size_ >= RHS.size_);
		}

		// LESS THAN OPERATOR
		bool operator<(const list<T>& RHS) const {
			iterator<T> temp(*this), temp1(RHS);
			while (temp != tail_ && temp1 != temp1.tail_) {
				if (*temp > *temp1) return false;
				++temp;
				++temp1;
			}

			return (size_ < RHS.size_);
		} 

		// LESS THAN OR EQUAL TO OPERATOR
		bool operator<=(const list<T>& RHS) const {
			iterator<T> temp(*this), temp1(RHS);
			while (temp != tail_ && temp1 != temp1.tail_) {
				if (*temp > *temp1) return false;
				++temp;
				++temp1;
			}

			return (size_ <= RHS.size_);
		}

		// FUNCTIONS FOR list CLASS

		// NODE INSERTION / ASSIGNMENT OPERATIONS

		// PUSH FRONT FUNCTION
		void push_front(const T DATA) {
			iterator<T> itr = begin();
			insert(itr, DATA);
		}

		// PUSH BACK FUNCTION
		void push_back(const T DATA) {
			iterator<T> itr = end();
			insert(itr++, DATA);
		}

		// INSERT FUNCTION
		void insert(iterator<T>& ITR, const T DATA) {
			node<T>* newNode = new node<T>();
			newNode->data_ = DATA;
			newNode->prev_ = ITR->prev_;
			newNode->next_ = ITR;
			ITR->prev_->next_ = newNode;
			ITR->prev_ = newNode;
			++size_;
		}

		// RANGE INSERT FUNCTION
		void insert(iterator<T>& ITR, const size_t N, const T DATA) {
			size_t count = 0;
			while (count < N && (ITR != head_ || ITR == tail_)) {
				insert(ITR, DATA);
				++count;
			}
		}

		// ASSIGN FUNCTION
		void assign(iterator<T>& ITR, const T DATA) {
			if (ITR == head_ || ITR == tail_) {
				cerr << "Cannot assign new value at invalid position" << endl;
				return;
			}

			ITR->data_ = DATA;
		}

		// RANGE ASSIGN FUNCTION
		void assign(iterator<T>& BEGIN, iterator<T>& END, const T DATA) {
			iterator<T> temp = BEGIN;
			while (temp != END->next_ && temp != tail_) {
				temp->data_ = DATA;
				++temp;
			}
		}

		// MERGE LISTS FUNCTION
		void merge(list<T>& other) {
			// LINK other TO tail_'s PREV
			tail_->prev_->next_ = other.head_->next_;
			other.head_->next_->prev_ = tail_->prev_;
			tail_->prev_ = other.tail_->prev_;
			tail_->prev_->next_ = tail_;

			other.head_->next_ = other.tail_;
			other.tail_->prev_ = other.head_;

			size_ += other.size_;
			other.size_ = 0;

			sort();
		}

		// NODE DELETION / REMOVAL OPERATIONS
		
		// POP FRONT FUNCTION
		void pop_front() {
			iterator<T> itr = begin();
			erase(itr);
		}


		// POP BACK FUNCTION
		void pop_back() {
			iterator<T> itr = end();
			erase(itr);
		}

		// WHOLE LIST SPLICE FUNCTION 
		void splice(iterator<T>& ITR, list<T>& other) {
			if (ITR == head_ || ITR == tail_) {
				cerr << "Cannot splice data to an invalid position" << endl;
				return;
			}

			size_ += other.size_;

			// LINK other NEXT TO SPECIFIED ITERATOR
			ITR->prev_->next_ = other.head_->next_;
			ITR->prev_->next_->prev_ = ITR->prev_;
			ITR->prev_ = other.tail_->prev_;
			ITR->prev_->next_ = ITR;

			other.head_->next_ = other.tail_;
			other.tail_->prev_ = other.head_;
			other.size_ = 0;
		}

		// SINGLE ENDED SPLICE FUNCTION
		void splice(iterator<T>& POS, list<T>& other, iterator<T>& BEGIN) {
			if (POS == head_ || POS == tail_) {
				cerr << "Cannot splice data to an invalid position" << endl;
				return;
			}

			if (BEGIN == head_ || BEGIN == tail_) {
				cerr << "Cannot splice data from an invalid position" << endl;
				return;
			}

			node<T>* temp = BEGIN->prev_;
			size_t addedSize = other.size_;

			// UPDATE this' & other's size_
			for (node<T>* temp = BEGIN; temp != other.tail_; ) {
				--other.size_;
				++size_;
				temp = temp->next_;
			}

			// LINK other's SPECIFIED BEGIN TO SPECIFIED POSITION
			POS->prev_->next_ = BEGIN;
			POS->prev_->next_->prev_ = POS->prev_;
			POS->prev_ = other.tail_->prev_;
			POS->prev_->next_ = POS;

			temp->next_ = other.tail_;
			other.tail_->prev_ = temp;
		}

		// DOUBLE ENDED RANGE SPLICE FUNCTION
		void splice(iterator<T>& POS, list<T>& other, iterator<T>& BEGIN, iterator<T>& END) {
			if (POS == head_ || POS == tail_) {
				cerr << "Cannot splice data to an invalid position" << endl;
				return;
			}

			if ((BEGIN == head_ || BEGIN == tail_) ||
				(END == head_ || END == tail_)) {
				cerr << "Cannot splice data from an invalid position" << endl;
				return;
			}

			node<T>* tempBack = BEGIN->prev_,
				* tempNext = END->next_;

			// UPDATE this' & other's size_
			for (node<T>* temp = BEGIN; temp != tempNext; ) {
				--other.size_;
				++size_;
				temp = temp->next_;
			}

			POS->prev_->next_ = BEGIN;
			POS->prev_->next_->prev_ = POS->prev_;
			POS->prev_ = END;
			END->next_ = POS;


			// UPDATE BORDERED NODES FROM other
			tempBack->next_ = tempNext;
			tempNext->prev_ = tempBack;
		}

		// SINGLE ERASE FUNCTION
		void erase(iterator<T>& ITR) {
			if (ITR == head_ || ITR == tail_) {
				cerr << "Cannot erase at invalid position" << endl;
				return;
			}

			ITR->prev_->next_ = ITR->next_;
			ITR->next_->prev_ = ITR->prev_;
			delete ITR;
			--size_;
		}

		// RANGE ERASE FUNCTION
		void erase(iterator<T> BEGIN, iterator<T> END) {
			++END;
			while (BEGIN != END && BEGIN != tail_) {
				iterator<T> temp = BEGIN;
				++BEGIN;
				erase(temp);
			}
		}

		// CLEAR FUNCTION
		void clear() {
			if (!head_ || !tail_)
				return;

			iterator<T> itr = begin();
			while (size_ != 0 && itr != tail_) {
				node<T>* temp = itr;
				++itr;
				delete temp;
				--size_;
			}

			head_->next_ = tail_;
			tail_->prev_ = head_;
		}

		// NODE ARRAGEMENT OPERATIONS
		
		// REVERSE FUNCTION
		void reverse() {
			node<T>* current = head_;
			node<T>* temp = nullptr;

			while (current != nullptr) {
				temp = current->prev_;
				current->prev_ = current->next_;
				current->next_ = temp;

				current = current->prev_;
			}

			if (temp != nullptr) {
				temp = temp->prev_;
				tail_ = head_;
				head_ = temp;
			}
		}

		// SORT FUNCTION
		void sort() {
			head_->next_ = sort(head_);

			node<T>* temp = head_->next_;
			while (temp->next_ != tail_)
				temp = temp->next_;

			temp->next_->prev_ = temp;
		}

		// UTILITY / HELPER FUNCTIONS
		inline constexpr size_t size() const { 
			return size_; 
		}

		// FRONT FUNCTION
		inline constexpr T front() const { 
			return *(iterator<T>(*this).begin()); 
		}

		// BACK FUNCTION
		inline constexpr T back() const { 
			return *(iterator<T>(*this).end()); 
		}

		// BEGIN FUNCTION
		inline iterator<T> begin() const { 
			return iterator<T>(*this).begin(); 
		}

		// END FUNCTION
		inline iterator<T> end() const { 
			return iterator<T>(*this).end(); 
		}
	};
}

#endif // !LIST_H
