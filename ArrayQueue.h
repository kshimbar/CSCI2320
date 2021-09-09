#include "Queue.h"

template<typename T>
class ArrayQueue : public Queue<T> {
public:
    explicit ArrayQueue(int s);
    ArrayQueue();
    ArrayQueue(const ArrayQueue &a) : elem{new T[sz]}, sz{a.sz},front{a.front},back{a.back}{
        for(int i = 0; i != sz; ++i){
            elem[i] = a.elem[i];
        }
    }
    ArrayQueue &operator=(const ArrayQueue<T> &a){
        T* p = new T[a.sz];
        for(int i = 0; i != a.sz; i++){
            p[i] = a.elem[i];
        }
        delete[] elem;
        elem = p;
        sz = a.sz;
        front = a.front;
        back = a.back;
    }
    ~ArrayQueue(){delete[] elem;}
    void enqueue(const T &t);
    T dequeue();
    T peek() const;
    bool isEmpty() const;

private:
    T *elem;
    int sz;
    int front;
    int back;
};

template<typename T>
ArrayQueue<T>::ArrayQueue(int s):elem{new T[s]},sz{s},front{0},back{0}{}

template<typename T>
T ArrayQueue<T>::peek() const {
    return elem[front];
}

template<typename T>
bool ArrayQueue<T>::isEmpty() const {
    return (front == back);
}

template<typename T>
void ArrayQueue<T>::enqueue(const T &t) {
    if ((back + 1) % sz == front) {
        T *tmp = new T[sz * 2];
        for (int ind = 0; ind <= sz; ++ind) {
            tmp[ind] = elem[ind];
        }
        delete[] elem;
        elem = tmp;
        sz *= 2;
        back = (back + 1) % sz;
    } else if (isEmpty()) {
        front = 0;
        back = 0;
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
    } else if (front == back) {
        ret = elem[front];
    } else {
        ret = elem[front];
        front = (front + 1) % sz;
    }
    return ret;
}
