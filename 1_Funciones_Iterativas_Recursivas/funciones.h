/*
 * recursion.h
 *
 *  24/08/2023
 *      Author:  Kevin J. Martínez Leyva
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_
#include <iostream>

class Funciones {
public:
	int sumaIterativa(int n){
        if (n<=0)
        {
           return 0;
        }
        int resultado=0;
        for(int i=1;i<=n;i++){
            resultado=resultado+i;
        }
        return resultado;
     };
    int sumaRecursiva(int n){
        if (n <= 0) {
		return 0;
	    } 
        else if (n <= 1) {
		return 1;
	    }   
        else {
		    return n + sumaRecursiva(n - 1);
	    }
     };
    int sumaDirecta(int n){
        return n*(n+1)/2;
    };
};
#endif 

