#include "Queue.h"

template<typename T>
class ArrayQueue : public Queue<T>{
private:
	T* elem;
	int sz;
	int front;
	int back;
public:
    	explicit ArrayQueue(int s);
   	ArrayQueue();
    	ArrayQueue(const ArrayQueue &a);
    	ArrayQueue &operator=(const ArrayQueue<T> &a);
    	~ArrayQueue();
    	void enqueue(const T &t);
    	T dequeue();
    	T peek() const;
    	bool isEmpty() const;
};

template<typename T>
ArrayQueue<T>::ArrayQueue():elem{new T[10]},sz{10}, front{0}, back{0} {}

template<typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T> &a):elem{a.elem},sz{a.sz}, front{a.front}, back{a.back} {
    for (int i = 0; i != sz; ++i)
        elem[i] = a.elem[i];
}

template<typename T>
ArrayQueue<T> &ArrayQueue<T>::operator=(const ArrayQueue<T> &a) {
    	T *p = new T[a.sz];
    	for (int i = 0; i < a.sz; ++i)
        p[i] = a.elem[i];
    	delete[] elem;
    	elem = p;
    	sz = a.sz;
    	front = a.front;
    	back = a.back;   
}

template<typename T>
void ArrayQueue<T>::enqueue(const T &t) {
    if (back + 1 % sz == front) {
        T *tmp = new T[sz * 2];
        for (int i = 0; i <= sz; ++i) {
            tmp[i] = elem[i];
        }
        delete[] elem;
        elem = tmp;
        sz *= 2;
        back = (back + 1) % sz;
    } else {
        back = (back + 1) % sz;
    }
    elem[back] = t;
}

template<typename T>
T ArrayQueue<T>::dequeue() {
    T ret;
    if (isEmpty()) {
        return 0;
    } else {
        ret = elem[front - 1];
        front -= 1;
    }
    return ret;
}

template<typename T>
T ArrayQueue<T>::peek() const {
    return elem[front];
}

template<typename T>
bool ArrayQueue<T>::isEmpty() const {
    return (front == back);
}

template<typename T>
ArrayQueue<T>::~ArrayQueue(){
	delete[] elem;
}
