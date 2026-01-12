#ifndef CLASS_LINKEDLIST_H
#define CLASS_LINKEDLIST_H
#include "class_rectangle.h"
#include <iostream>

//declaring a template node to help us to declare the linkedlist
template <typename T>
struct Node{
    T data;               // data will be our rectangles in TwoDimTreeNode
    Node<T> * next;       // Node pointer to next object in LinkedList

    explicit Node(const T& _data) : data(_data), next(nullptr) {} //only constructor of this struct
};

template <typename T>
class LinkedList {
public:
    LinkedList();                       //constructor
    LinkedList(const LinkedList& rhs);  //copy constructor
    ~LinkedList();                      //destructor
    void insert( const T& _obj);        //insert method to add Rectangles in LinkedList
    void printList();                   //method to print all the data in the LinkedList
    Node<T>* getHeader();               //method to return head pointer in main
    int getSize();                      //method that returns the length of the LinkedList
private:
    Node<T>* header;                    //head pointer of the list
};

template <typename T>
LinkedList<T>::LinkedList(): header(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs) {
    header = nullptr;
    Node<T>* rhs_temp = rhs.header;
    Node<T>* lhs_temp = nullptr;
    while (rhs_temp != nullptr) {
        Node<T>* new_node = new Node<T>(rhs_temp->data);
        if(header == nullptr) {
            header = new_node;
            lhs_temp = new_node;
        }
        else {
            lhs_temp->next = new_node;
            lhs_temp = new_node;
        }
        rhs_temp = rhs_temp->next;
    }
}

template <typename T>
void LinkedList<T>::insert( const T& _obj) {
    Node<T>* new_node = new Node<T>(_obj);
    if(header == nullptr) {
        header = new_node;
    }
    else {
        Node<T>* temp = header;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

template <typename T>
void LinkedList<T>::printList() {
    Node<T>* temp = header;
    while(temp != nullptr) {
        cout << temp->data;   //we can print data(rectangle) since we overloaded the << operator in Rectangles class
        temp = temp->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* temp = header;
    Node<T>* _next = nullptr;
    while(temp != nullptr) {
        _next = temp->next;
        delete temp;
        temp = _next;
    }
}

template <typename T>
Node<T>* LinkedList<T>::getHeader() {
    return header;
}

template<typename T>
int LinkedList<T>::getSize() {
    int size = 0;
    Node<T>* temp = header;
    while(temp != nullptr) {
        size++;
        temp = temp->next;
    }
    return size;
}


#endif