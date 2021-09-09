#ifndef STACK_H
#define STACK_H

#include "Node.h"
//
template <typename T>
class Stack
{
private:
	Node<T>* top;
	int size;

public:
	Stack();
	~Stack();
	bool Isempty() const;
	bool Push(const T& newItem);
	bool Pop(T& TopItem);
	bool Peek(T& TopItem) const;
	const T* toArray(int& count);
	int getSize() const;
	void copyStack(Stack<T>& s);
};

template <typename T>
Stack<T>::Stack()
{
	top = nullptr;
	size = 0;
}

template <typename T>
bool  Stack<T>::Isempty() const
{
	if (top == nullptr)
		return true;
	else
		return false;
}


template <typename T>
bool  Stack<T>::Push(const T& newItem)
{
	Node<T>* NewNodeptr = new Node<T>(newItem);

	if (Isempty())
	{
		top = NewNodeptr; //case: this is the first node in the stack
		size++;
	}
	else
	{
		NewNodeptr->setNext(top);
		top = NewNodeptr;
		size++;
	}


	return true;


}


template <typename T>
bool  Stack<T>::Pop(T& TopItem)
{
	if (Isempty())
		return false;

	Node<T>* DeletedNodeptr = top;
	TopItem = top->getItem();

	if (top->getNext() != nullptr)
		top = top->getNext();
	else
		top = nullptr;


	if (DeletedNodeptr)
		delete DeletedNodeptr;

	size--;
	return true;


}

template <typename T>
bool  Stack<T>::Peek(T& TopItem) const
{
	if (Isempty())
		return false;

	else
		TopItem = top->getItem();
	return true;
}
template <typename T>

const T* Stack<T>::toArray(int& count)
{
	count = 0;

	if (!top)
		return nullptr;

	Node<T>* pointer = top;
	while (pointer)
	{
		count++;
		pointer = pointer->getNext();
	}

	T* Array = new T[count];
	pointer = top;

	for (int i = 0; i < count; i++)
	{
		Array[i] = pointer->getItem();
		pointer = pointer->getNext();
	}

	return Array;

}
template <typename T>
int Stack<T>::getSize() const
{
	return size;
}

template <typename T>
void Stack<T>::copyStack(Stack<T>& s) {

	Stack<T>* temp = new  Stack<T>();
	T item;

	while (Isempty() != true) {
		Pop(item);
		temp->Push(item);
	}
	while (temp->Isempty() != true) {
		temp->Pop(item);
		s.Push(item);
		Push(item);
	}
	delete temp;
}
template <typename T>
Stack<T>::~Stack()
{

}


#endif // !STACK_H