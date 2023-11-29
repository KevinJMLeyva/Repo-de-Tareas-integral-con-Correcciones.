#ifndef HEAP_H_
#define HEAP_H_
#include <string>
#include <sstream>
#include <iostream>


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

template <class T>
class Heap {
private:
  T *data;
  unsigned int tamano;
  unsigned int count;
  unsigned int parent(unsigned int) const;
  unsigned int left(unsigned int) const;
  unsigned int right(unsigned int) const;
  void heapify(unsigned int);
  void swap(unsigned int, unsigned int);

public:
  Heap(unsigned int) ;
  ~Heap();
  int size();
  bool empty() const;
  bool full() const;
  void push(T) ;
  T pop() ;
  T top();
  void clear();
  std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int sze)  {
  tamano = sze;
  data = new T[tamano];
  if (data == 0) {
    throw OutOfMemory();
  }
  count = 0;
}

template <class T>
Heap<T>::~Heap() {
  delete [] data;
  data = 0;
  tamano = 0;
  count = 0;
}


template <class T>
bool Heap<T>::empty() const {
  return (count == 0);
}
template <class T>
bool Heap<T>::full() const {
  return (count == tamano);
}
template <class T>
int Heap<T>::size() {
  int a=0;
  for (unsigned int i = 0; i < count; i++) {
    if (i != 0) {
    } a++;
  } 
  return a;
}
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
  return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
  return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
  return ((2 * pos) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
  T aux = data[i];
  data[i] = data[j];
  data[j] = aux;
}
template <class T>
void Heap<T>::heapify(unsigned int pos) {
  unsigned int le = left(pos);
  unsigned int ri = right(pos);
  unsigned int min = pos;
  if (le <= count && data[le] < data[min]) {
    min = le;
  }
  if (ri <= count && data[ri] < data[min]) {
    min = ri;
  }
  if (min != pos) {
    swap(pos, min);
    heapify(min);
  }
}

template <class T>
void Heap<T>::push(T val)  {
  unsigned int pos;
  if (full()) {
    throw Overflow();
  }

  pos = count;
  count++;
  while (pos > 0 && val < data[parent(pos)]) {
    data[pos] = data[parent(pos)];
    pos = parent(pos);
  }
  data[pos] = val;
}

template <class T>
T Heap<T>::pop()  {
  if (empty()) {
    throw NoSuchElement();
  }
  T aux = data[0];

  data[0] = data[--count];
  heapify(0);
  return aux;
}
template <class T>
void Heap<T>::clear() {
  count = 0;
}

template <class T>
std::string Heap<T>::toString() const {
  std::stringstream aux;
  aux << "[";	for (unsigned int i = 0; i < count; i++) {
    if (i != 0) {
      aux << " ";
    } aux << data[i];
  } aux << "]";
  return aux.str();
}

template <class T>
T Heap<T>::top()  {
  if (!empty()) {
    return data[0];
  }
  return 0;

}

#endif /* HASH_H_ */