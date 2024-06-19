#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H

#include "List.h"
using namespace List;

/*-----PUBLIC-----*/
template <typename T>
void list<T>::push_front(const T DATA) {
    iterator<T> itr = begin();
    insert(itr, DATA);
}

template <typename T>
void list<T>::push_back(const T DATA) {
    iterator<T> itr = end();
    itr.pointed_ = tail_;
    insert(itr, DATA);
}

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

template <typename T>
void list<T>::insert(const iterator<T>& ITR, const size_t N, const T DATA) {
    size_t count = 0;
    while (count < N && (ITR.pointed_ != head_ || ITR.pointed_ == tail_)) {
        insert(ITR, DATA);
        ++count;
    }
}

template <typename T>
void list<T>::assign(const iterator<T>& ITR, const T DATA) {
    if (ITR.pointed_ == head_ || ITR.pointed_ == tail_) {
        cerr << "Cannot assign new value at invalid position" << endl;
        return;
    }

    ITR.pointed_->data_ = DATA;
}

template <typename T>
void list<T>::assign(const iterator<T>& BEGIN, const iterator<T>& END, const T DATA) {
    iterator<T> temp = BEGIN;
    while (temp.pointed_ != END.pointed_->next_ && temp.pointed_ != tail_) {
        temp.pointed_->data_ = DATA;
        ++temp;
    }
}

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

template <typename T>
void list<T>::erase(iterator<T> BEGIN, iterator<T> END) {
    ++END;
    while (BEGIN.pointed_ != END.pointed_ && BEGIN.pointed_ != tail_) {
        iterator<T> temp = BEGIN;
        ++BEGIN;
        erase(temp);
    }
}

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

template <typename T>
void list<T>::splice(const iterator<T>& ITR, list<T>& other) {
    if (ITR.pointed_ == head_ || ITR.pointed_ == tail_) {
        cerr << "Cannot splice data from an invalid position" << endl;
        return;
    }

    other.head_->next_->prev_ = tail_->prev_;
    other.head_->next_->prev_->next_ = other.head_->next_;
    other.head_->next_ = ITR.pointed_;
    ITR.pointed_->prev_ = other.head_;

    head_->next_ = tail_;
    tail_->prev_ = head_;
    size_ = 0;
}

#endif // !DEFINITION_H

