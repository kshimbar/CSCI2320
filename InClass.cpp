#include <iostream>
//g++ -std=c++11 -Wall InClass.cpp -o inclass
void swapval(int* x, int* y);
void swapref(int &x, int &y);
template<typename T>
void myswap(T*x,T*y);

int main(){
    //Aug 25th
    std::cout << "Hello world!\n";
}

//Aug 27th
void swapval(int*x, int*y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void swapref(int &x, int &y){
    int a = x;
    x = y;
    y = a;
}

template<typename T>
void myswap(T* x, T* y);
    T tmp = *x;
    *x = *y;
    *y = tmp;
}