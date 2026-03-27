#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std

class arr_extensible{
private:
    int* B;
    unsigned long n;
    unsigned long capacidad;

    unsigned long siguiente_potencia(unsigned long x){
        if(x == 0){
            return 0;
        }
        unsigned long p = 1;
        while(p < x){
            p *= 2;
        }
        return p;
    }   
}