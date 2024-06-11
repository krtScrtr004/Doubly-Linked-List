#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H

#include "List.h"
using namespace List;

template <typename T> 
void LinkedList<T>::PushFront(const T DATA) {
    Iterator<T> itr = Begin();
    Insert(itr, DATA);
}

template <typename T>
void LinkedList<T>::PushBack(const T DATA) {
    Iterator<T> itr = End();
    Insert(itr, DATA);
}

template<typename T>
void LinkedList<T>::Insert(const Iterator<T>& ITR, const T DATA) {
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
}

#endif // !DEFINITION_H

