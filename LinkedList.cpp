#pragma once

#ifndef LINKED_LIST_CPP

#define LINKED_LIST_HPP

#include "LinkedList.hpp"

template <class T>
Node<T>::Node(int id, T message) : clientId(id), data(message),next(NULL){
}

template <class T>
T Node<T>::getData() const{
	return data;
}

template <class T>
void Node<T>::setData(T data){
	this->data = data;
}

template <class T>
void Node<T>::setId(int id){
	this->clientId = id;
}

template <class T>
int Node<T>::getId() const{
	return this->clientId;
}

template <class T>
Node<T>* Node<T>::getNext() const{
	return this->next;
}

template <class T>
void Node<T>::setNext(Node<T> *next){
	this->next = next;
}

template <class T>
LinkedList<T>::LinkedList() : start(NULL), end(NULL), length(0){

}

template <class T>
LinkedList<T>::LinkedList(Node<T>* node) : start(node), end(node), length(1){
}

template <class T>
LinkedList<T>::~LinkedList(){
	Node<T>* node = start, *next;
	while (node != NULL) {
		next = node->getNext();
		delete node;
		node = next;
	}
}

template <class T>
void LinkedList<T>::addNode(Node<T>* node){
	if (start == NULL) {
		start = node;
		end = node;
	}
	else {
		end->setNext(node);
		end = end->getNext();
	}
	length++;
}

template <class T>
void LinkedList<T>::addNode(int id, T data){
	Node<T> *node = new Node<T>(id, data);
	addNode(node);
}

template <class T>
Node<T>* LinkedList<T>::getNode(int id) const{
	Node<T> *node = start;
	while (node != NULL && node->getId() != id) {
		node = node->getNext();
	}
	return node;
}

template <class T>
size_t LinkedList<T>::getLength() const{
	return length;
}

template <class T>
Node<T>* LinkedList<T>::removeNode(int id){
	Node<T> *node = start, *result;
	if (start == NULL || (start->getId() != id && start->getNext() == NULL)) {
		return NULL;
	}
	else if (start->getId() == id) {
		result = start;
		start = result->getNext();
		if(start == NULL){
			end = NULL;
			length = 0;
		}
		return result;
	}
	while(node->getNext() != NULL && node->getNext()->getId() != id){
		node = node->getNext();
	}
	if (node->getNext() == NULL) {
		return NULL;
	}
	else{
		result = node->getNext();
		node->setNext(result->getNext());
		length--;
		if (end == result) {
			end = node;
		}
		return result;
	}
}

template <class T>
void LinkedList<T>::deleteNode(int id){
	Node<T>* node = removeNode(id);
	if (node != NULL) {
		delete node;
	}
}

#endif
