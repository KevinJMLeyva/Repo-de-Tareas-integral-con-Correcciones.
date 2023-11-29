#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <exception>
#include <string>
#include <sstream>
#include <cstdio>

//Kevin Josué Martínez Leyva A01067611
//Excepciones
class Exception : public std::exception {
protected:
	std::string text;

public:
	Exception() throw();
	~Exception() throw();
	virtual const char* what() const throw();
};

Exception::Exception() throw ()
	: text("Basic exception") {
}

Exception::~Exception() throw () {}

const char* Exception::what() const throw() {
	return text.c_str();
}

/*********** RangeError ***********/
class RangeError : public Exception {
public:
	RangeError() throw();
};

RangeError::RangeError() throw () {
		text = std::string("RangeError");
}

/*********** OutOfMemory ***********/
class OutOfMemory : public Exception {
public:
	OutOfMemory() throw();
};

OutOfMemory::OutOfMemory() throw () {
		text = std::string("OutOfMemory");
}

/*********** IndexOutOfBounds ***********/
class IndexOutOfBounds : public Exception {
public:
	IndexOutOfBounds() throw();
};

IndexOutOfBounds::IndexOutOfBounds() throw () {
	text = std::string("IndexOutOfBounds");
}

/*********** NoSuchElement ***********/
class NoSuchElement : public Exception {
public:
	NoSuchElement() throw();
};

NoSuchElement::NoSuchElement() throw () {
		text = std::string("NoSuchElement");
}

/*********** IllegalAction ***********/
class IllegalAction : public Exception {
public:
	IllegalAction() throw();
};

IllegalAction::IllegalAction() throw () {
		text = std::string("IllegalAction");
}

/*********** Overflow ***********/
class Overflow : public Exception {
public:
	Overflow() throw();
};

Overflow::Overflow() throw () {
		text = std::string("Overflow");
}


//Elemtno de las listas que contiene un apuntador al valor y un valor la siguiente elemento
template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val):value(val),next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt):value(val),next(nxt)  {}

template <class T>
Link<T>::Link(const Link<T> &source):value(source.value),next(source.next){}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();

	void insertionFirst(T) ;
	void insertion(T) ;
	T    getFirst() const ;
	T    deleteFirst() ;
	int  length() const;
	T    get(int) const  ;
	int search(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
	void operator= (const List&) ;

	void insertionBefore(ListIterator<T>&, T)  ;
	void insertionAfter(ListIterator<T>&, T)  ;
	T    deleteCurrent(ListIterator<T>&)  ;

	void update(int, T) ;
	int  indexOf(T) const;
	int  lastIndexOf(T) const;
	T    deleteAt(int) ;
	bool deleteFirstOcurrence(T);
	bool deleteLastOcurrence(T);

private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List(){ 
	head=0;
	size=0;
}

template <class T>
List<T>::~List() {
	clear();//Tal vez no borrarlo por completo
}

template <class T>
bool List<T>::empty() const {
	return (size==0);
}

template <class T>
int List<T>::length() const {
	return size;
}

template <class T>
int List<T>::search(T val) const {
	Link<T> *p;
	int pos;
	p=head;
	pos=0;
	while(p!=0){
		if (p->value==val)
		{
			return pos;
		}
		p = p->next;
		pos++;
	}
	return -1;
}

template <class T>
T List<T>::getFirst() const  {
	if (empty()){
		throw NoSuchElement();
	}
	return head->value;
}

template <class T>
void List<T>::insertionFirst(T val)  {
	Link<T> *newlink;
	newlink=new Link<T> (val);
	if (newlink==0){
		throw OutOfMemory();
	}
	newlink->next=head;
	head=newlink;
	size++;
}

template <class T>
void List<T>::insertion(T val)  {
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}

	if (empty()) {
		insertionFirst(val);
		return;
	}
	p = head;
	while (p ->next!= 0) {
		p = p->next;
	}

	newLink->next=0;
	p->next=newLink;
	size++;
}

template <class T>
T List<T>::deleteFirst()  {
	T val;
	Link<T> *p;
	if (empty()){
		throw NoSuchElement();
	}
	p = head;

	head=p->next;
	val=p->value;

	delete p;
	size--;
	return val;
}

template <class T>
T List<T>::get(int index) const   {
	Link<T> *p;
	int i;
	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		return getFirst();
	}

	p=head;
	i=0;
	while (i<=index) {
		p = p->next;
		i++;
	}
	return p->value;
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
List<T>::List(const List<T> &source)  {
Link<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
	} else {
		p = source.head;
		head = new Link<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new Link<T>(p->value);
			if (q->next == 0) {
				throw OutOfMemory();
			}
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
void List<T>::operator=(const List<T> &source)  {
	Link<T> *p, *q;

	clear();
	if (source.empty()) {
		size = 0;
		head = 0;
	} else {
		p = source.head;
		head = new Link<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new Link<T>(p->value);
			if (q->next == 0) {
				throw OutOfMemory();
			}
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
void List<T>::insertionBefore(ListIterator<T> &itr, T val)   {
Link<T> *newLink;

	if (this != itr.theList) {
		throw IllegalAction();
	}

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}

	// between
	if (itr.previous != 0) {
		newLink->next = itr.current;
		itr.previous->next = newLink;
		itr.previous = itr.previous->next;
		size++;
	// start
	} else {
		addFirst(val);
		itr.previous = head;
		itr.current = itr.previous->next;
	}
}

template <class T>
void List<T>::insertionAfter(ListIterator<T> &itr, T val)   {
Link<T> *newLink;

	if (this != itr.theList) {
		throw IllegalAction();
	}

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}


	// between
	if (itr.current != 0) {
		newLink->next = itr.current->next;
		itr.current->next = newLink;
		size++;
	// end
	} else if (itr.previous != 0) {
		itr.previous->next = newLink;
		itr.current = newLink;
		size++;
	// start
	} else {
		addFirst(val);
		itr.current = head;
		itr.previous = 0;
	}
}

template <class T>
T List<T>::deleteCurrent(ListIterator<T> &itr)   {
	T val;

	if (this != itr.theList) {
		throw IllegalAction();
	}

	if (itr.current == 0) {
		throw NoSuchElement();
	}

	if (itr.previous == 0) {
		head = itr.current->next;
	} else {
		itr.previous->next = itr.current->next;
	}

	val = itr.current->value;
	delete itr.current;
	itr.current = 0;

	//std::cout << "remove current = " << ((itr.current != 0)? itr.current->value : 0) << " previous: " << ((itr.previous != 0)? itr.previous->value : 0) << std::endl;
	return val;
}

template <class T>
void List<T>::update(int index, T val)  {
	Link<T> *p;
	int i;
	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		return insertionFirst(val);
	}

	p=head;
	i=0;
	while (i<index) {
		p = p->next;
		i++;
	}
	p->value=val;
}

template <class T>
int List<T>::indexOf(T val) const {
	Link<T> *p;
	int pos;
	p=head;
	pos=0;
	while(p!=0){
		if (p->value==val)
		{
			return pos;
		}
		p = p->next;
		pos++;
	}
	return -1;
}

template <class T>
int List<T>::lastIndexOf(T val) const {
	Link<T> *p;
	int pos,a;
	p=head;
	pos=0;
	a=-1;
	while(p!=0){
		if (p->value==val)
		{
			a=pos;
		}
		p = p->next;
		pos++;
	}
	return a;
}

template <class T>
T List<T>::deleteAt(int index)  {
	Link<T> *p,*anterior,*siguiente, *valor_index;
	int i;
	p=head;
	i=0;
	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		return deleteFirst();
	}
	
	while (i<=index-2) {
		p = p->next;
		i++;
	}
	anterior=p;
	p=p->next;
	valor_index=p->next;
	siguiente=valor_index;
	anterior->next=siguiente;

	size--;
	return -1;
}

template <class T>
bool List<T>::deleteFirstOcurrence(T val) {
	int posicion_val;
	posicion_val=indexOf(val);
	if(posicion_val!=-1){
		deleteAt(posicion_val);
		return true;
	}
	return false;
}

template <class T>
bool List<T>::deleteLastOcurrence(T val) {
	int posicion_val;
	posicion_val=lastIndexOf(val);
	if(posicion_val!=-1){
		deleteAt(posicion_val);
		return true;
	}
	return false;
}

template <class T>
class ListIterator {
public:
	ListIterator(List<T>*);
	ListIterator(const ListIterator<T>&);

	bool begin();
	bool end();
	T&   operator() ();
	bool operator++ ();
	void operator= (T);

private:
	Link<T> *current;
	Link<T> *previous;
	List<T> *theList;

	friend class List<T>;
};

template <class T>
ListIterator<T>::ListIterator(List<T> *aList) : theList(aList) {
	begin();
}

template <class T>
ListIterator<T>::ListIterator(const ListIterator<T> &source) : theList(source.theList) {
	begin();
}

template <class T>
bool ListIterator<T>::begin() {
	previous = 0;
	current = theList->head;
	return (current != 0);
}

template <class T>
T& ListIterator<T>::operator() () {
	if (current == 0) {
		throw NoSuchElement();
	}
	return current->value;
}

template <class T>
bool ListIterator<T>::end() {
	//std::cout << "1 end current = " << ((current != 0)? current->value : 0) << " previous: " << ((previous != 0)? previous->value : 0) << std::endl;
	if (current == 0) {
		if (previous != 0) {
			current = previous->next;
		}
	}
	return (current == 0);
}

template <class T>
bool ListIterator<T>::operator++ () {
	if (current == 0) {
		if (previous == 0) {
			current = theList->head;
		} else {
			current = previous->next;
		}
	} else {
		previous = current;
		current = current->next;
	}
	return (current != 0);
}

template <class T>
void ListIterator<T>::operator= (T val) {
	if (current == 0) {
		throw NoSuchElement();
	}
	current->value = val;
}

#endif /* LINKEDLIST_H_ */
