#include "Stack.h"

template<typename T>
class ArrayStack : public Stack<T> {
public:
	ArrayStack(): elem{new T[10]}, sz{10}, top{0} {};
	ArrayStack(const ArrayStack &a);
<<<<<<< HEAD
	ArrayStack &operator=(const ArrayStack &a);
	~ArrayStack() {delete[] elem;}
=======
    ArrayStack& operator=(const ArrayStack& a);
	~ArrayStack() {}
    ArrayStack& operator=(const ArrayStack& a){
        T* p = new T[a.sz];
        for(int i = 0; i != a.sz; ++i)
                p[i] = a.elem[i];
        delete[] elem;
        elem = p;
        sz = a.sz;
        top = a.top;
    }
	~ArrayStack() {delete[] elem;
>>>>>>> 708d2940a8262b62f6224f9857c2fcccdb3bfcd0
	void push(const T &t);
	T pop();
	T peek() const;
	bool isEmpty() const;
<<<<<<< HEAD
private:
	T *elem;
	int sz;
	int top;
=======
>>>>>>> 708d2940a8262b62f6224f9857c2fcccdb3bfcd0
};

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack &a):elem{new T[sz]},sz{a.sz}, top{a.top} {
	for (int i = 0; i != sz; i++)
		elem[i] = a.elem[i];
}

template<typename T>
ArrayStack<T> &ArrayStack<T>::operator=(const ArrayStack &a) {
	T *p = new T[a.sz];
	for (int i = 0; i != a.sz; ++i)
		p[i] = a.elem[i];
	delete[] elem;
	elem = p;
	sz = a.sz;
	top = a.top;
}

template<typename T>
<<<<<<< HEAD
void ArrayStack<T>::push(const T &i) {
	if (top == sz) {
		T *tmp = new T[sz * 2];
		for (int ind = 0; ind != sz; ind++)
			tmp[ind] = elem[ind];
		delete[] elem;
		elem = tmp;
		sz *= 2;
	}
	elem[top] = i;
	++top;
}

template<typename T>
T ArrayStack<T>::pop(){
	return elem[--top];	
}

template<typename T>
inline T ArrayStack<T>::peek() const{
	return elem[top - 1];
}

template<typename T>
inline bool ArrayStack<T>::isEmpty() const{
	return (top == 0);
=======
ArrayStack<T> &ArrayStack<T>::operator=(const ArrayStack &a){
    T* p = new T[a.sz];
    for(int i = 0; i != a.sz; i++){
        p[i] = a.elem[i];
    }
    delete[] elem;
    elem = p;
    sz = a.sz;
    top = a.top;
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

<<<<<<< HEAD
template<typename T>
T ArrayStack<T>::pop() {
	return elem[--top];
}

template<typename T>
inline T ArrayStack<T>::peek() const {
	return (elem[top - 1]);
}

template<typename T>
bool ArrayStack<T>::isEmpty() const {
    return (top == 0);
=======
template <typename T>
T ArrayStack<T>::pop(){
    return elem[--top];
>>>>>>> 52c9481b686df131d7f1f575b8a9e775bf610d00
>>>>>>> 708d2940a8262b62f6224f9857c2fcccdb3bfcd0
}
