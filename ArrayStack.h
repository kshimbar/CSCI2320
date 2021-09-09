#include "Stack.h"
template<typename T>
class ArrayStack : public Stack<T>{
    private:
        T* elem;
        int sz;
        int top;
        void print() const;
    public:
    ArrayStack() : elem{new T[10]},sz{10},top{0} {};;
	ArrayStack(int s);//length for the array
	ArrayStack(const ArrayStack &a);
    ArrayStack& operator=(const ArrayStack& a){
        T* p = new T[a.sz];
        for(int i = 0; i != a.sz; i++){
            p[i] = a.elem[i];
        }
        delete[] elem;
        elem = p;
        sz = a.sz;
        top = a.top;
    }
	~ArrayStack() {}
	void push(const T &t);
	T pop();
	T peek() const { return elem[top]; }
	bool isEmpty() const { return top == 0; }
};

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack &a)
:elem{new T[sz]},sz{a.sz},top{a.top} {
    for(int i = 0; i != sz; i++)
        elem[i] = a.elem[i];
}

template<typename T>
void ArrayStack<T>::push(const T &t){
    if(top == sz){
       T* tmp = new T[sz*2];
       for(int i = 0; i != sz; ++i){
            tmp[i] = elem[i];
        }
        delete[] elem;
        elem = tmp;
        sz *= 2;
    }
    elem[top] = t;
    top += 1;
}

template <typename T>
T ArrayStack<T>::pop(){
    if(top == 0){
        return NULL;
    }else{
        return elem[--top];
    }
}
