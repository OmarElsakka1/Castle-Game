template <typename T>
class P_Node
{
private:
	T item; // A data item
	double Priority;
	P_Node<T>* next; // Pointer to next node
public:
	P_Node();
	P_Node(const T& r_Item);	//passing by const ref.
	P_Node(const T& r_Item, double pri);
	P_Node(const T& r_Item, P_Node<T>* nextNodePtr, int pri);
	void setItem(const T& r_Item);
	void setNext(P_Node<T>* nextNodePtr);
	T getItem() const;
	P_Node<T>* getNext() const;
	void setPriority(double t);
	double getPriority();
};// end Node; 

template < typename T>
P_Node<T>::P_Node(const T& r_Item, P_Node<T>* nextNodePtr, int pri)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
P_Node<T>::P_Node()
{
	next = nullptr;
}
template < typename T>
P_Node<T>::P_Node(const T& r_Item) {

	item = r_Item;
	next = nullptr;
}

template < typename T>
void P_Node<T>::setItem(const T& r_Item) {
	item = r_Item;
}


template < typename T>
void P_Node<T>::setNext(P_Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T P_Node<T>::getItem() const {
	return item;
}

template < typename T>

void P_Node<T>::setPriority(double t) {
	Priority = t;
}

template < typename T>


double P_Node<T>::getPriority() {
	return Priority;
}
template < typename T>

P_Node<T>* P_Node<T>::getNext() const {
	return next;
}
template < typename T>

P_Node<T>::P_Node(const T& r_Item, double pri) {
	item = r_Item;
	Priority = pri;
}
