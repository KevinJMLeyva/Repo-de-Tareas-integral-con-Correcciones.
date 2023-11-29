/*
 * hash.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

#include <iostream>
using namespace std;

template <class Key, class Value>
class  Quadratic {
public:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

	Key *keys;
	Key initialValue;
	Value *values;

	long indexOf(const Key) const;
	 Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	~ Quadratic();
	bool full() const;
	bool put(Key, Value);
	bool contains(const Key) const;
	Value get(const Key) ;
	void clear();
	std::string toString() const;
};

template <class Key, class Value>
 Quadratic<Key, Value>:: Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
   size = sze;
    func = f;
    count = 0;

    // Inicialización de 'keys' con un array dinámico
    keys = new Key[size];
    initialValue = init;

    // Inicialización de 'values' con un array dinámico
    values = new Value[size];

    // Resto del código de inicialización
    for (unsigned int i = 0; i < size; ++i) {
        keys[i] = init; // Asignar el valor inicial a todas las keys
        values[i] = Value{}; // Inicializar los valores
    }
}
//long k [4] = {35,34524,543594,354};
//long* pk = k;
//int a;
//Primer modo -------------------------------------
//for {a=0;a<4;a++) {
//printf("%ld",*pk);
//pk++;
//}
//Segundo modo--------------------------------------
//for (a=0;a<4;a++){
//printf("%ld, *(pk+a));
//}

template <class Key, class Value>
 Quadratic<Key, Value>::~ Quadratic() {
  delete[] keys;
   delete[] values;

}

template <class Key, class Value>
bool  Quadratic<Key, Value>::full() const {
	return (count>=size);
}

template <class Key, class Value>
long  Quadratic<Key, Value>::indexOf(const Key k) const {
	return -1;
}

template <class Key, class Value>
bool  Quadratic<Key, Value>::put(Key k, Value v) {
  unsigned int s=func(k);
  int asig=s%size;
  int a=asig;
  if(keys[asig]=="empty"){
    keys[asig]=k;
    values[asig]=v;
    count++;
  }
  else{
    int i = 1;
    while (i <= size) {
        asig = (a + i * i) % size;
        if (keys[asig] == "empty") {
            keys[asig] = k;
            values[asig] = v;
            count++;
            return true;
        }
        i++;
  }
    }
    return false;
}

template <class Key, class Value>
bool  Quadratic<Key, Value>::contains(const Key k) const {
  unsigned int s=func(k);
  int asig=s%size;
  int a=asig;
  if(keys[asig]==k){
    return true;
  }
  else{
    int i = 1;
    while (i <= size) {
        asig = (a + i * i) % size;
        if (keys[asig] ==k) {
          return true;
        }
        i++;
  }
	return false;
}
  }
template <class Key, class Value>
Value  Quadratic<Key, Value>::get(const Key k)  {
  unsigned int s=func(k);
  int asig=s%size;
  int a=asig;
  if(keys[asig]==k){
    return values[asig];
  }
  else{
    int i = 1;
    while (i <= size) {
        asig = (a + i * i) % size;
        if (keys[asig] ==k) {
          return values[asig];
        }
        i++;
  }
    }
	return -1;
}

template <class Key, class Value>
void  Quadratic<Key, Value>::clear() {
   delete[] keys;
   delete[] values;
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
  std::stringstream aux;
  for (int i = 0; i < size; i++){
      if (keys[i] != initialValue){
        aux << "(" << i << " ";
        aux << keys[i] << " : " << values[i] << ") ";
      }
  }
  return aux.str();
}
#endif /* HASH_H_ */
