#pragma once
#include"P_Node.h"

template <typename T>
class Priority_queue
{
	P_Node<T>* front;
	int size;
public:
	Priority_queue();
	bool isEmpty() const;
	int getSize() const;
	void push(T& elemnt, double priority);
	void pop(T& elemnt);
	const T* toArray(int& count);

};


template < typename T>
Priority_queue<T>::Priority_queue() {
	size = 0;
	front = nullptr;
}




template < typename T>
bool Priority_queue<T>::isEmpty() const {
	if (front == nullptr)
		return true;
	else
		return false;
}
template < typename T>
int Priority_queue<T>::getSize() const {
	return size;
}

template < typename T>

void Priority_queue<T>::push(T& elemnt, double pri) {
	P_Node<T>* newNode = new P_Node<T>(elemnt, pri);

	if (front == nullptr) {

		front = newNode;
		newNode->setNext(nullptr);
	}
	else {
		if (pri >= front->getPriority()) {
			P_Node<T>* save = front;
			front = newNode;
			newNode->setNext(save);
		}
		else {
			P_Node<T>* current = front;
			while (current != nullptr && current->getNext() != nullptr && pri < current->getNext()->getPriority()) {
				current = current->getNext();
			}

			P_Node<T>* saveNext = current->getNext();
			current->setNext(newNode);
			newNode->setNext(saveNext);
		}
	}
	++size;
}

template < typename T>
void Priority_queue<T>::pop(T& elemnt) {
	if (isEmpty())
		return;
	else {
		elemnt = front->getItem();
		P_Node<T>* savefront = front;
		P_Node<T>* ptr = front->getNext();

		front = ptr;
		delete savefront;
		--size;
	}
}
template < typename T>

const T* Priority_queue<T>::toArray(int& count)
{
	count = 0;

	if (!front)
		return nullptr;

	P_Node<T>* p = front;
	while (p)
	{
		count++;
		p = p->getNext();
	}

	T* Arr = new T[count];
	p = front;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;

}
