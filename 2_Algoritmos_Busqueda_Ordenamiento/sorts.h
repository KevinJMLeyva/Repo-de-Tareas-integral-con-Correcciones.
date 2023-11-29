#ifndef SORTS_H_
#define SORTS_H_
#include <vector>
#include <list>

template <class T>// T se rellena por un tipo de dato
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
public:
	std::vector<T> ordenaBurbuja(std::vector<T>&);//& se la paso por referencia para no hacer copias en ram por accidente, const solo puedes ver no tocar 
	std::vector<T> ordenaSeleccion(std::vector<T>&);
	std::vector<T> insertionSort(std::vector<T>&);
	std::vector<T> ordenaMerge(std::vector<T>&);
	int busqSecuencial(std::vector<T>&,int);
	int busqBinaria(std::vector<T>&,int);
	int busqBinaria_aux(std::vector<T>&, int, int, int);
}; 

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}
template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}
template <class T>	
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid &&j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) { //termina de poner los ultimos valores
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) { //termina de poner los ultimos valores
			B[k++] = A[i];
		}
	}
}
template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}
template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja( std::vector<T> &source) {
	std::vector<T> v(source);

	for (int i = source.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (source[j] > source[j + 1]) {
				swap(source, j, j + 1);
			}
		}
	}
	return source;
}
template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T> &source) {
	int pos;

	for (int i = source.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (source[j] > source[pos]) {
				pos = j;
			}
		}

		if (pos != i) {
			swap(source, i, pos);
		}
	}
	return source;
}
template <class T>
std::vector<T> Sorts<T>::insertionSort(std::vector<T> &source) {
	for (int i = 1; i < source.size(); i++) {
		for (int j = i; j > 0 && source[j] < source[j - 1]; j--) {
			swap(source, j, j - 1);
		}
	}
	return source;
}
template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T> &source) {
	std::vector<T> v(source);
	std::vector<T> tmp(v.size());

	mergeSplit(source, tmp, 0, source.size() - 1);
	return source;
}
template <class T>
int Sorts<T>::busqSecuencial (std::vector<T> &source, int val){
	int longitud=source.size();
    for (int i = 0; i < longitud; i++) {
		if (val == source[i]) {
			return i;
		}
	}
	return -1;
}
template <class T>
int Sorts<T>::busqBinaria_aux (std::vector<T>&source, int low, int high, int valor){
    int mid;
	if(low <= high) {
		mid=(low+high)/2;
		if(valor==source[mid]){
			return mid;
		}
		else if(valor<source[mid]){
			return busqBinaria_aux(source,low,mid-1,valor);
		}
		else{
			return busqBinaria_aux(source,mid+1,high,valor);
		}
	}
	return -1;
}
template <class T>
int Sorts<T>::busqBinaria (std::vector<T> &source, int valor){
	int low=0;
	int longitud=source.size(); 
	int high=longitud-1;
	int mid;
	mid=(low+high)/2;
	if(valor==source[mid]){
		return mid;
	}
	else {
		mid = (low+high) / 2;
		if(valor<source[mid]){
			return busqBinaria_aux(source,low,mid-1,valor);
		}
		else{
			return busqBinaria_aux(source,mid+1,high,valor);
		}
	}
	return busqBinaria_aux(source, 0, longitud - 1, valor);
}
#endif /* SORTS_H_ */