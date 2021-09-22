template<typename T>
class ArrayList {
// Types
	T* elem;
	unsigned int elemCt;
	unsigned int sz;
    void newArr(){
        T* tmp = new T[sz * 2];
        for(int i = 0; i < sz; ++i){
            tmp[i] = elem[i];
        }
        delete[] elem;
        elem = tmp;
        sz *= 2;
    }

	public:
// value_type
// iterator
 	class iterator {
		T* loc;
		public:
		iterator(T *l) : loc{l} {}
		iterator() {}
		iterator(const iterator &i): loc{i.loc} {loc = i.loc;}
		T &operator*() { return *loc; }
		bool operator==(const iterator &i) const { return loc == i.loc; }
		bool operator!=(const iterator &i) const { return !(*this == i); }
		iterator &operator=(const iterator &i) {loc = i.loc; return *this;}
		iterator &operator++() {++loc; return *this;}
		iterator &operator--() {--loc; return *this;}
		iterator operator++() {
            auto ret = loc;
            loc++;
            return ret;
        }
		iterator operator--() {
            auto ret = loc;
            loc--;
            return ret;
        }
	};
// const_iterator
	class const_iterator {
        T* loc;
		public:
		const_iterator(T *l) {}
		const_iterator() {}
		const_iterator(const const_iterator &i) {}
		T &operator*() {}
		bool operator==(const const_iterator &i) const {return *this == i;}
		bool operator!=(const const_iterator &i) const {return !(*this == i);}
		const_iterator &operator=(const const_iterator &i) {loc = i.loc; return *this;}
		const_iterator &operator++() {++loc; return *this;}
		const_iterator &operator--() {--loc; return *this;}
		const_iterator operator++() {
            auto ret = loc;
            loc++;
            return ret;
        }
		const_iterator operator--() {
            auto ret = loc;
            loc--;
            return ret;
        }
	};

// General Methods
ArrayList() : elem{new T[10]}, elemCt{0}, sz{10} {}
ArrayList(const ArrayList &that) {}
ArrayList<T> &operator=(const ArrayList<T> &al) {}

~ArrayList() {}
void push_back(const T &t); // add to the end.
void pop_back(); // remove last element.
int size();
void clear();
void insert(const T &t,int index); // insert this element before the given index.
const T &operator[](int index) const; // get the element at index.
T &operator[](int index); // get the element at index.
void remove(int index); // remove the item at the given index.

iterator begin();
const_iterator begin() const;
iterator end();
const_iterator end() const;
const_iterator cbegin() const;
const_iterator cend() const;
};

template <typename T>
const T &ArrayList<T>::operator[](int index) const{
	return elem[index];
}

template <typename T>
T &ArrayList<T>::operator[](int index){
	return elem[index];
}

template <typename T>
typename ArrayList<T>::iterator ArrayList<T>::begin() {
	return iterator(elem);
}
template <typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::begin() const {
	return const_iterator(elem);
}
template <typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::cbegin() const {
	return const_iterator(elem);
}
template <typename T>
typename ArrayList<T>::iterator ArrayList<T>::end() {
	return iterator(elem+elemCt);
}
template <typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::end() const {
	return const_iterator(elem+elemCt);
}
template <typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::cend() const {
	return const_iterator(elem+elemCt);
}

template<typename T>
void ArrayList<T>::push_back(const T &t) {
    if(sz == elemCt) newArr();
	elem[elemCt++] = t;
}

template<typename T>
void ArrayList<T>::pop_back() {
    elem[elemCt--];
}

template<typename T>
int ArrayList<T>::size(){
	return elemCt;
}

template<typename T>
void ArrayList<T>::clear() {
	delete[] elem;
    elemCt = 0;
}

template<typename T>
void ArrayList<T>::remove(int index) {
	for(int i = index; i < elemCt - 1; ++i){
        elem[i] = elem[i + 1];
    }
}

template<typename T>
void ArrayList<T>::insert(const T &t, int index) {
    if(sz == elemCt) newArr();
	for(int i = elemCt; i > index; --i){
        elem[i] = elem[i - 1];
    }
    elem[index] = t;
    elemCt++;
}

