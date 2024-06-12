#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H

#include "List.h"
using namespace List;

template <typename T> 
void LinkedList<T>::push_front(const T DATA) {
    Iterator<T> itr = begin();
    insert(itr, DATA);
}

template <typename T>
void LinkedList<T>::push_back(const T DATA) {
    Iterator<T> itr = end();
    insert(itr, DATA);
}

template<typename T>
void LinkedList<T>::insert(const Iterator<T>& ITR, const T DATA) {
    if (ITR.Pointed == nullptr) {
        cerr << "Cannot insert at a NULL iterator position" << endl;
        return;
    }

    Node<T>* newNode = new Node<T>();
    newNode->Data = DATA;
    newNode->Prev = ITR.Pointed->Prev;
    newNode->Next = ITR.Pointed;
    ITR.Pointed->Prev->Next = newNode;
    ITR.Pointed->Prev = newNode;
    ++Size;
}

template<typename T>
void List::LinkedList<T>::insert(const Iterator<T>& ITR, const size_t N, const T DATA) {
    size_t count = 0;
    while (count < N && ITR.Pointed != nullptr) {
        insert(ITR, DATA);
        ++count;
    }
}

#endif // !DEFINITION_H

