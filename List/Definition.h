#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H

#include "List.h"
using namespace List;

/*-----PRIVATE-----*/

// SORT FUNCTION (TRUE OPERATION)
template <typename T>
node<T>* list<T>::sort(node<T>* first) {
    if (first == tail_ || first->next_ == tail_)
        return first;

    node<T>* second = split(first);
    first = sort(first);
    second = sort(second);

    return merge(first, second);
}

// SPLIT FUNCTION (PRIV SORT FUNCTION UTILITY)
template <typename T>
node<T>* list<T>::split(node<T>* head) {
    if (head == tail_ ||  head->next_ == tail_)
        return nullptr;

    node<T>* slow = head;
    node<T>* fast = head;

    while (fast != nullptr && fast->next_ != nullptr &&
           fast != tail_ && fast->next_ != tail_) {
        slow = slow->next_;
        fast = fast->next_->next_;
    }

    node<T>* second = slow;
    slow->prev_->next_ = tail_;
    second->prev_ = head_;

    return second;
}

// MERGE FUNCTION (PRIV SORT FUNCTION UTILITY)
template<typename T>
inline node<T>* List::list<T>::merge(node<T>* n1, node<T>* n2) {
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

/*-----PUBLIC-----*/

// NODE INSERTION / ASSIGNMENT OPERATIONS

// PUSH FRONT FUNCTION
template <typename T>
void list<T>::push_front(const T DATA) {
    iterator<T> itr = begin();
    insert(itr, DATA);
}

// PUSH BACK FUNCTION
template <typename T>
void list<T>::push_back(const T DATA) {
    iterator<T> itr = end();
    insert(itr++, DATA);
}

// SINLGE INSERT FUNCTION
template <typename T>
void list<T>::insert(iterator<T>& ITR, const T DATA) {
    node<T>* newNode = new node<T>();
    newNode->data_ = DATA;
    newNode->prev_ = ITR->prev_;
    newNode->next_ = ITR;
    ITR->prev_->next_ = newNode;
    ITR->prev_ = newNode;
    ++size_;
}

// MULTIPLE INSERT FUNCTION
template <typename T>
void list<T>::insert(iterator<T>& ITR, const size_t N, const T DATA) {
    size_t count = 0;
    while (count < N && (ITR != head_ || ITR == tail_)) {
        insert(ITR, DATA);
        ++count;
    }
}

// SINGLE ASSIGN FUNCTION
template <typename T>
void list<T>::assign(iterator<T>& ITR, const T DATA) {
    if (ITR == head_ || ITR == tail_) {
        cerr << "Cannot assign new value at invalid position" << endl;
        return;
    }

    ITR->data_ = DATA;
}

// RANGE ASSIGN FUNCTION
template <typename T>
void list<T>::assign(iterator<T>& BEGIN, iterator<T>& END, const T DATA) {
    iterator<T> temp = BEGIN;
    while (temp != END->next_ && temp != tail_) {
        temp->data_ = DATA;
        ++temp;
    }
}

// MERGE LISTS FUNCTION
template<typename T>
void List::list<T>::merge(list<T>& other) {
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
template <typename T>
void list<T>::pop_front() {
    iterator<T> itr = begin();
    erase(itr);
}

// POP BACK FUNCTION
template <typename T>
void list<T>::pop_back() {
    iterator<T> itr = end();
    erase(itr);
}

// WHOLE LIST SPLICE FUNCTION 
template <typename T>
void list<T>::splice(iterator<T>& ITR, list<T>& other) {
    if (ITR == head_ || ITR == tail_) {
        cerr << "Cannot splice data to an invalid position" << endl;
        return;
    }

    size_ += other.size_;

    ITR->prev_->next_ = other.head_->next_;
    ITR->prev_->next_->prev_ = ITR->prev_;
    ITR->prev_ = other.tail_->prev_;
    ITR->prev_->next_ = ITR;

    other.head_->next_ = other.tail_;
    other.tail_->prev_ = other.head_;
    other.size_ = 0;
}

// SINGLE ENDED SPLICE FUNCTION
template <typename T>
void list<T>::splice(iterator<T>& POS, list<T>& other, iterator<T>& BEGIN) {
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

    POS->prev_->next_ = BEGIN;
    POS->prev_->next_->prev_ = POS->prev_;
    POS->prev_ = other.tail_->prev_;
    POS->prev_->next_ = POS;

    temp->next_ = other.tail_;
    other.tail_->prev_ = temp;
}

// DOUBLE ENDED RANGE SPLICE FUNCTION
template <typename T>
void list<T>::splice(iterator<T>& POS, list<T>& other, iterator<T>& BEGIN, iterator<T>& END) {
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
template <typename T>
void list<T>::erase(iterator<T>& ITR) {
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
template <typename T>
void list<T>::erase(iterator<T> BEGIN, iterator<T> END) {
    ++END;       
    while (BEGIN != END && BEGIN != tail_) {
        iterator<T> temp = BEGIN;
        ++BEGIN;
        erase(temp);
    }
}

// CLEAR FUNCTION
template <typename T>
void list<T>::clear() {
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
template <typename T>
void list<T>::reverse() {
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
template <typename T>
void list<T>::sort() {
    head_->next_ = sort(head_);

    node<T>* temp = head_->next_;
    while (temp->next_ != tail_)
        temp = temp->next_;

    temp->next_->prev_ = temp;
}

#endif // !DEFINITION_H

    