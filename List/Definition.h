#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H

#include "List.h"
using namespace List;

template <typename T> 
void LinkedList<T>::PushFront(const T DATA) {
	Node<T>* newNode = new Node<T>();
    newNode->Data = DATA;
    newNode->Prev = Head;
    newNode->Next = Head->Next;
    Head->Next->Prev = newNode;
    Head->Next = newNode;
}

template <typename T>
void LinkedList<T>::PushBack(const T DATA) {
    Node<T>* newNode = new Node<T>();
    newNode->Data = DATA;
    newNode->Prev = Tail->Prev;
    newNode->Next = Tail;
    Tail->Prev->Next = newNode;
    Tail->Prev = newNode;
}

template<typename T>
void LinkedList<T>::Insert(const Iterator<T>& ITR, const T DATA) {
    if (ITR.Pointed == Head->Next)
        PushFront(DATA);
    else if (ITR.Pointed == Tail->Prev)
        PushBack(DATA);
    else {
        Node<T>* newNode = new Node<T>();
        newNode->Data = DATA;
        newNode->Prev = ITR.Pointed->Prev;
        newNode->Next = ITR.Pointed;
        ITR.Pointed->Prev->Next = newNode;
        ITR.Pointed->Prev = newNode;
    }
}

#endif // !DEFINITION_H

