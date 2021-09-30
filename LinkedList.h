template<typename T>
class LinkedList {
struct Node{
    Node(){}
    Node(const T &d, Node *p, Node *n) :  data(d), prev(p), next(n){}
    T data;
    Node* prev, *next;
};
int ct;
Node sent;

public:
typedef T value_type;

class iterator {
Node * loc;
public:
iterator() {}
iterator(Node *l) : loc{l}{}
T &operator*() { return loc -> data;}
bool operator==(const iterator &i) const { return loc == i.loc; }
bool operator!=(const iterator &i) const { return !(*this == i); }
iterator &operator=(const iterator &i) { loc = i.loc; return *this; }
iterator &operator++() { loc = loc->next; return *this; }
iterator &operator--() { loc = loc->prev; return *this; }
iterator operator++(int) {
    iterator res{loc};
    loc = loc->next;
    return res;
}
iterator operator--(int) {
    iterator res{loc};
    loc = loc->prev;
    return res;
}
friend class const_iterator;
friend class LinkedList;
};
class const_iterator {
const Node * loc;
public:
const_iterator() {}
const_iterator(const Node *l){loc = l;}
// TODO - Include a constructor that converts from a regular iterator.
const T &operator*() { return loc -> data; }
bool operator==(const const_iterator &i) const { return loc == i.loc; }
bool operator!=(const const_iterator &i) const { return !(*this == i); }
const_iterator &operator=(const const_iterator &i) { loc = i.loc; return *this; }
const_iterator &operator++() { loc = loc -> next; return *this; }
const_iterator &operator--() { loc = loc -> prev; return *this; }
const_iterator operator++(int) {
    const_iterator res{loc};
    res = res -> next;
    return res;
}
const_iterator operator--(int) {
    const_iterator res{loc};
    res = res -> prev;
    return res;
}
};

// General Methods

LinkedList(){
    sent.next = &sent;
    sent.prev = &sent;
    ct = 0;
}

LinkedList(const LinkedList &l){
    ct = 0;
    sent.prev = &sent;
    sent.next = &sent;
    for(auto &v : l) push_back(v);
}

LinkedList &operator=(const LinkedList &l) {
    ct = 0;
    clear();
    for(auto &n : l) push_back(n);
    return *this;
}
~LinkedList() {
    for(iterator rover = begin(); rover != end();++rover){
        delete rover.loc;
    }
    ct = 0;
}
void push_back(const T &t){
    Node *a = new Node(t,sent.prev,&sent);
    sent.prev = a;
    a->prev->next = a;
    ++ct;
} // add to the end.
void pop_back(){
    Node* eras = sent.prev;
    sent.prev = eras->prev;
    eras->prev->next = &sent;
    delete eras;
    --ct;
} // remove last element.
int size() const {return ct;}
void clear(){
    for(iterator tmp = begin(); tmp != end(); ++tmp){
        erase(tmp);
    }
    ct = 0;
}
iterator insert(iterator position,const T &t){
    Node *n = new Node(t,position.loc->prev,position.loc);
    position.loc->prev->next = n;
    position.loc->prev = n;
    ct++;
    return --position;
} // insert this element before the given index.
const T &operator[](int index) const{
    Node *tmp = sent.next;
    while(tmp != &sent && index-- > 0){
        tmp = tmp->next;
    }
    return tmp->data;
} // get the element at index.
T &operator[](int index){
    Node *tmp = sent.next;
    while(tmp != &sent && index-- > 0)
        tmp = tmp->next; 
    return tmp->data;
} // get the element at index.
iterator erase(iterator position){
	iterator tmp{position.loc->next};
    position.loc->prev->next = position.loc->next;
    position.loc->next->prev = position.loc->prev;
    ct -= 1;
	delete position.loc;
    return tmp;
} // remove the item at the given index.

iterator begin(){return iterator(sent.next);}
const_iterator begin() const {return const_iterator(sent.next);}
iterator end(){return iterator(&sent);}
const_iterator end() const {return const_iterator(&sent);}
const_iterator cbegin() const {return const_iterator(sent.next);};
const_iterator cend() const{return const_iterator(&sent);}

};
