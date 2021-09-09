#pragma once

/*This code is an updated version from "Data Abstraction & Problem Solving with C++,WALLS AND MIRRORS ,SIXTH EDITION"*/

/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers, 
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					------------- 
					| item| next | --->
					-------------
General Queue case:

                 frontPtr																backPtr
					\											   						/		
					 \											  					   /		
					------------- 	  ------------- 	  ------------- 	  ------------- 	  	  
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------	  
		
Empty Case:

                 frontptr	 backptr
						\	 /				
						 \	/				
					---- NULL ------


Single Node Case:
                 frontPtr	 backPtr
					\		/	
					 \	   /			
					-------- 	
					|	|nxt -->NULL
					--------	

*/

#include "Node.h"

template <typename T>
class Queue
{
private :
	
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int size;
public :
	Queue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;
	int getSize() const;
	void copyQueue(Queue<T>& p);
	
	//toArray function to be used ONLY when drawing the queue items
	const T* toArray(int& count);	//returns array of T (array of items)


	~Queue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
Queue<T>::Queue()
{
	backPtr=nullptr;
	frontPtr=nullptr;
	size = 0;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool Queue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>

bool Queue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	size++;
	return true;
} // end enqueue



/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Queue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	size--;

	return true;

}
template <typename T>
int Queue<T>::getSize() const
{
	return size;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool Queue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
Queue<T>::~Queue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T" 
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/

//IMPORTANT:
//toArray function to be used ONLY when drawing the queue items

template <typename T>
const T* Queue<T>::toArray(int& count)
{

	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

	count=0;

	if(!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while(p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr= new T[count];
	p = frontPtr;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

}

template <typename T>
void Queue<T>::copyQueue(Queue<T>& p) {
	Queue<T>* temp = new  Queue<T>();
	T x;
	while (isEmpty() != true)
	{
		dequeue(x);
		temp->enqueue(x);
	}
	while (temp->isEmpty() != true) {
		temp->dequeue(x);
		p.enqueue(x);
		enqueue(x);
	}
	delete temp;
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/*template < typename T>
class Priority_queue
{
	Node<T>* front;
	int size;
public:
	Priority_queue();
	bool isEmpty() const;
	int getSize() const;
	Node<T>* top();
	void push(T elemnt);
	void pop();
};




template < typename T>
Priority_queue<T>::Priority_queue() {
	size = 0;
	front = nullptr;
}




template < typename T>
bool Priority_queue<T>::isEmpty() const {
	if (size == 0)
		return true;
	else
		return false;
}
template < typename T>
int Priority_queue<T>::getSize() const {
	return size;
}
template < typename T>
Node<T>* Priority_queue<T>::top() {
	return front;
}
template < typename T>
void Priority_queue<T>::push(T elemnt) {
	Node<T>* newNode = new Node<T>(elemnt);
	if (front == nullptr) {

		front = newNode;
		newNode->setNext(nullptr);
	}
	else {
		if (elemnt > front->getItem()) {
			Node<T>* save = front;
			front = newNode;
			newNode->setNext(save);
		}
		else {
			Node<T>* current = front->getNext();
			while (current != nullptr && current->getNext() != nullptr && elemnt < current->getItem()) {
				current = current->getNext();
			}
			Node<T>* saveNext = current->getNext();
			current->setNext(newNode);
			newNode->setNext(saveNext);
		}
	}
	++size;
}

template < typename T>
void Priority_queue<T>::pop() {
	if (isEmpty() != true) {
		Node<T>* savefront = front;
		Node<T>* ptr = front->getNext();
		front = ptr;
		delete savefront;
		--size;
	}
}*/

