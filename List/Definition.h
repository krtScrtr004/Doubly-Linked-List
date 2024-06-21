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
void list<T>::insert(const iterator<T>& ITR, const T DATA) {
    node<T>* newNode = new node<T>();
    newNode->data_ = DATA;
    newNode->prev_ = ITR.pointed_->prev_;
    newNode->next_ = ITR.pointed_ ;
    ITR.pointed_->prev_->next_ = newNode;
    ITR.pointed_->prev_ = newNode;
    ++size_;
}

// MULTIPLE INSERT FUNCTION
template <typename T>
void list<T>::insert(const iterator<T>& ITR, const size_t N, const T DATA) {
    size_t count = 0;
    while (count < N && (ITR.pointed_ != head_ || ITR.pointed_ == tail_)) {
        insert(ITR, DATA);
        ++count;
    }
}

// SINGLE ASSIGN FUNCTION
template <typename T>
void list<T>::assign(const iterator<T>& ITR, const T DATA) {
    if (ITR.pointed_ == head_ || ITR.pointed_ == tail_) {
        cerr << "Cannot assign new value at invalid position" << endl;
        return;
    }

    ITR.pointed_->data_ = DATA;
}

// RANGE ASSIGN FUNCTION
template <typename T>
void list<T>::assign(const iterator<T>& BEGIN, const iterator<T>& END, const T DATA) {
    iterator<T> temp = BEGIN;
    while (temp.pointed_ != END.pointed_->next_ && temp.pointed_ != tail_) {
        temp.pointed_->data_ = DATA;
        ++temp;
    }
}

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
void list<T>::splice(const iterator<T>& ITR, list<T>& other) {
    if (ITR.pointed_ == head_ || ITR.pointed_ == tail_) {
        cerr << "Cannot splice data to an invalid position" << endl;
        return;
    }

    size_ += other.size_;

    ITR.pointed_->prev_->next_ = other.head_->next_;
    ITR.pointed_->prev_->next_->prev_ = ITR.pointed_->prev_;
    ITR.pointed_->prev_ = other.tail_->prev_;
    ITR.pointed_->prev_->next_ = ITR.pointed_;

    other.head_->next_ = other.tail_;
    other.tail_->prev_ = other.head_;
    other.size_ = 0;
}

// SINGLE ENDED SPLICE FUNCTION
template <typename T>
void list<T>::splice(const iterator<T>& POS, list<T>& other, const iterator<T>& BEGIN) {
    if (POS.pointed_ == head_ || POS.pointed_ == tail_) {
        cerr << "Cannot splice data to an invalid position" << endl;
        return;
    }

    if (BEGIN.pointed_ == head_ || BEGIN.pointed_ == tail_) {
        cerr << "Cannot splice data from an invalid position" << endl;
        return;
    }

    node<T>* temp = BEGIN.pointed_->prev_;
    size_t addedSize = other.size_;

    // UPDATE this' & other's size_
    for (node<T>* temp = BEGIN.pointed_; temp != other.tail_; ) {
        --other.size_;
        ++size_;
        temp = temp->next_;
    }

    POS.pointed_->prev_->next_ = BEGIN.pointed_;
    POS.pointed_->prev_->next_->prev_ = POS.pointed_->prev_;
    POS.pointed_->prev_ = other.tail_->prev_;
    POS.pointed_->prev_->next_ = POS.pointed_;

    temp->next_ = other.tail_;
    other.tail_->prev_ = temp;
}

// DOUBLE ENDED RANGE SPLICE FUNCTION
template <typename T>
void list<T>::splice(const iterator<T>& POS, list<T>& other, const iterator<T>& BEGIN, const iterator<T>& END) {
    if (POS.pointed_ == head_ || POS.pointed_ == tail_) {
        cerr << "Cannot splice data to an invalid position" << endl;
        return;
    }

    if ((BEGIN.pointed_ == head_ || BEGIN.pointed_ == tail_) ||
        (END.pointed_ == head_ || END.pointed_ == tail_)) {
        cerr << "Cannot splice data from an invalid position" << endl;
        return;
    }

    node<T>* tempBack = BEGIN.pointed_->prev_,
           * tempNext = END.pointed_->next_;
    
    // UPDATE this' & other's size_
    for (node<T>* temp = BEGIN.pointed_; temp != tempNext; ) {
        --other.size_;
        ++size_;
        temp = temp->next_;
    }

    POS.pointed_->prev_->next_ = BEGIN.pointed_;
    POS.pointed_->prev_->next_->prev_ = POS.pointed_->prev_;
    POS.pointed_->prev_ = END.pointed_;
    END.pointed_->next_ = POS.pointed_;


    // UPDATE BORDERED NODES FROM other
    tempBack->next_ = tempNext;
    tempNext->prev_ = tempBack;
}

// SINGLE ERASE FUNCTION
template <typename T>
void list<T>::erase(const iterator<T>& ITR) {
    if (ITR.pointed_ == head_ || ITR.pointed_ == tail_) {
        cerr << "Cannot erase at invalid position" << endl;
        return;
    }

    ITR.pointed_->prev_->next_ = ITR.pointed_->next_;
    ITR.pointed_->next_->prev_ = ITR.pointed_->prev_;
    delete ITR.pointed_;
    --size_;
}

// RANGE ERASE FUNCTION
template <typename T>
void list<T>::erase(iterator<T> BEGIN, iterator<T> END) {
    ++END;       
    while (BEGIN.pointed_ != END.pointed_ && BEGIN.pointed_ != tail_) {
        iterator<T> temp = BEGIN;
        ++BEGIN;
        erase(temp);
    }
}

// CLEAR FUNCTION
template <typename T>
void list<T>::clear() {
    iterator<T> itr = begin();
    while (size_ != 0 && itr.pointed_ != tail_) {
        node<T>* temp = itr.pointed_;
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

    