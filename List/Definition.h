#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H

#include "List.h"
using namespace List;

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
    if (ITR.pointed_ == nullptr) {
        cerr << "Cannot insert at a NULL position" << endl;
        return;
    }

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
    while (count < N && ITR.pointed_ != nullptr) {
        insert(ITR, DATA);
        ++count;
    }
}

template <typename T>
void list<T>::assign(const iterator<T>& ITR, const T DATA) {
    if (ITR.pointed_ == head_ ||
        ITR.pointed_ == tail_ ||
        ITR.pointed_ == nullptr) {
        cerr << "Cannot assign new value at invalid position" << endl;
        return;
    }

    ITR.pointed_->data_ = DATA;
}

template <typename T>
void list<T>::assign(const iterator<T>& BEGIN, const iterator<T>& END, const T DATA) {
    iterator<T> temp = BEGIN;
    while (temp.pointed_ != END.pointed_->next_ && temp.pointed_ != nullptr) {
        temp.pointed_->data_ = DATA;
        ++temp;
    }
}

template <typename T>
void list<T>::erase(const iterator<T>& ITR) {
    if (ITR.pointed_ == head_ ||
        ITR.pointed_ == tail_ ||
        ITR.pointed_ == nullptr) {
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
    while (BEGIN.pointed_ != END.pointed_ && BEGIN.pointed_ != nullptr) {
        iterator<T> temp = BEGIN;
        ++BEGIN;
        erase(temp);
    }
}

template <typename T>
void list<T>::clear() {
    iterator<T> itr = begin();
    while (size_ != 0 && itr.pointed_ != nullptr) {
        node<T>* temp = itr.pointed_;
        ++itr;
        delete temp;
        --size_;
    }

    head_->next_ = tail_;
    tail_->prev_ = head_;
}

#endif // !DEFINITION_H

