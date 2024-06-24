# DOUBLY LINKED LIST

This repository is my own implementation of a **templated doubly-linked-list** using the C++ language. This template include basic operations on linked-list such as creation, insertion, modification, and deletion of nodes. Moreover, this template also includes a customized iterator class inclusively for the list class. The iterator class contains various overloaded operators such as ==, !=, =, ++, --, etc. 

The interface and declaration are found in separate header files along the path. The class interfaces are in the List.h header file, while the definitions for iterator<T> and list<T> classes are in Iterator.h and Definition.h, respectively. However, including these class templates doesn't require including all the preceding header files, as the definition .h files are already included at the bottom of List.h. Thus, only the List.h header file is needed to link with the client file

## FUNCTIONS AND OPERATIONS FOR LIST CLASS

### OVERLOADED OPERATORS
> The comparision operators are based on **_lexicographical_** comparison.
> * operator=
> * operator==
> * operator!=
> * operator>
> * operator>=
> * operator<
> * operator<=

### OPERATION FUNCTIONS

> INSERTION / ASSIGNMENT OPERATIONS
> * push_front
> * push_back
> * insert // single insertion
> * insert // multiple insertion
> * assign // single assignment
> * assign // multiple assignment
> * merge

> DELETION / REMOVAL OPERATIONS
> * pop_front
> * pop_back
> * splice // whole list
> * splice // from specfied beginning upto the last node
> * splice // from specfied beginning upto specified end
> * erase // single deletion
> * erase // multiple deletion
> * clear

> ARRANGEMENT OPERATIONS
> * reverse
> * sort

> UTILITY FUNCTIONS
> * size
> * front
> * back
> * begin
> * end
