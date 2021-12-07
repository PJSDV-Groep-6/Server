#pragma once

#ifndef LINKED_LIST

#define LINKED_LIST

#include <iostream>

template <class T>
class Node{
private:
	T data;
	int clientId;
	Node* next;
public:
	Node(int,T);
	T getData() const;
	void setData(T);
	void setId(int);
	int getId() const;
	Node<T>* getNext() const;
	void setNext(Node<T>*);
};

template <class T>
class LinkedList {
private:
	Node<T>* start, * end;
	size_t length;
public:
	LinkedList();
	LinkedList(Node<T>*);
	~LinkedList();

	void addNode(Node<T>*);
	void addNode(int, T);
	
	Node<T>* getNode(int) const;
	size_t getLength() const;

	Node<T>* removeNode(int);

	void deleteNode(int);
};

#endif
