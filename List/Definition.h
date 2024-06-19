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

    other.size_ = 0;
    iterator<T> itr(other);
    while (itr.pointed_ != BEGIN.pointed_) {
        ++other.size_;
        ++itr;
    }

    addedSize -= other.size_;

    POS.pointed_->prev_->next_ = BEGIN.pointed_;
    POS.pointed_->prev_->next_->prev_ = POS.pointed_->prev_;
    POS.pointed_->prev_ = other.tail_->prev_;
    POS.pointed_->prev_->next_ = POS.pointed_;

    temp->next_ = other.tail_;
    other.tail_->prev_ = temp;

    size_ += addedSize;
}

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
    size_t addedSize = other.size_;

    other.size_ = 0;
    iterator<T> itr(other);
    while (itr.pointed_ != BEGIN.pointed_) {
        ++other.size_;
        ++itr;
    }
    itr.pointed_ = tempNext;
    while (itr.pointed_ != other.tail_) {
        ++other.size_;
        ++itr;
    }

    addedSize -= other.size_;

    POS.pointed_->prev_->next_ = BEGIN.pointed_;
    POS.pointed_->prev_->next_->prev_ = POS.pointed_->prev_;
    POS.pointed_->prev_ = END.pointed_;
    END.pointed_->next_ = POS.pointed_;

    tempBack->next_ = tempNext;
    tempNext->prev_ = tempBack;

    size_ += addedSize;
}

#endif // !DEFINITION_H

