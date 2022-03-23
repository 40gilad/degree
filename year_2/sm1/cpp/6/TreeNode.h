#pragma once
#include <iostream>
#include <string.h>
#include "Student.h"

using namespace std;

#define MAX_CHILDREN 4
template<class T>
class TreeNode {

private:
	int index, returned;
	T* t_data;
	TreeNode<T>* arrey[MAX_CHILDREN];
	TreeNode<T>* next;

public:

	TreeNode(TreeNode<T>* parent, T* data);

	TreeNode(T* data);
	

~TreeNode();
	
	

T* getData() const;

		
void setData(T* data);

		
void addChild(T* data);
	
void addChild(TreeNode<T>* newChild);

void removeChild();

	
TreeNode<T>* findChild(T* data) const;

	
int findChildIndx(T* data) const;

	
TreeNode<T>* getChild(int indx) const;

	
TreeNode<T>* getNextChild();

	
TreeNode<T>* getPrevChild();

	
TreeNode<T>* getParent() const;

	
void setParent(TreeNode<T>* parent);

int getNumChildren() const;

};

template<class T>
TreeNode<T>::TreeNode(TreeNode<T>* parent, T* data) 
	: next(parent), t_data(data)
{
	for (int i = 0; i < MAX_CHILDREN; i++)
		arrey[i] = nullptr;
}

template <class T>
TreeNode<T>::TreeNode(T* data) :
	next(nullptr), t_data(data),index(0),returned(0) {
	for (int i = 0; i < MAX_CHILDREN; i++)
		arrey[i] = nullptr;
}

template<class T>
TreeNode<T>::~TreeNode() {
	
}

template<class T>
T* TreeNode<T>:: getData() const { return t_data; }

template<class T>
void TreeNode<T>:: setData(T* data) { t_data=data; }

template<class T>
void TreeNode<T>:: addChild(T* data) {
	TreeNode<T> temp(data);
	if ((index == 0) && arrey[index] != nullptr) {
		cout << "\nNo more space for data" << endl;
		return;
	}
	arrey[index++] = &temp;
	if (index == MAX_CHILDREN)
		index = 0;

}

template<class T>
void TreeNode<T>:: addChild(TreeNode<T>* newChild) {
	if ((index == 0) && arrey[index] != nullptr) {
		cout << "\nNo more space for new child" << endl;
		return;
	}
	arrey[index++] = newChild;
	if (index == MAX_CHILDREN)
		index = 0;
}

template<class T>
void TreeNode<T>:: removeChild() {
	//removes the nodes last entered child or if no children - does nothing
	if ((arrey[index-1] != nullptr)&&index>=0) {
		delete arrey[index--];
	}
	if (index == -1)
		index = 0;
}

template<class T>
TreeNode<T>* TreeNode<T>::findChild(T* data) const // returns ptr or NULL
{
	for (int i = 0; i < MAX_CHILDREN; i++) {
		if (*arrey[i]->t_data==*data)
			return arrey[i];
	}
	return nullptr;
}

template<class T>
int TreeNode<T>:: findChildIndx(T* data) const // returns childs indx or -1
{
	for (int i = 0; i < MAX_CHILDREN; i++) {
		if (*arrey[i]->t_data== *data)
			return i;
	}
	return -1;
}

template<class T>
TreeNode<T>* TreeNode<T>:: getChild(int indx) const { return arrey[indx]; }


template<class T>
TreeNode<T>* TreeNode<T>:: getNextChild() {
	if (returned == MAX_CHILDREN)
		returned = 0;
	return arrey[returned++];
}

template<class T>
TreeNode<T>* TreeNode<T>:: getPrevChild() {
	if (returned == -1)
		returned = 3;
	return arrey[returned--];

}

template<class T>
TreeNode<T>* TreeNode<T>::getParent() const { return next; }

template<class T>
void TreeNode<T>::setParent(TreeNode<T>* parent) { next = parent; }

template<class T>
int TreeNode<T>::getNumChildren() const { return index + 1; }
