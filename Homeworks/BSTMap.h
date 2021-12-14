#ifndef BSTMAP
#define BSTMAP

#include <vector>
#include <utility>
#include <algorithm>

template<typename K,typename V>
class BSTMap {
    // TODO: Define your Node
    struct Node {
        Node *left, *right, *parent;
        std::pair<K,V> data;
        // may need more
    };
    // TODO: specify whatever member data you need.
    Node * root;
    unsigned int ct;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. I keep a Node* and a bool that tells me if it is at end.
        Node *n;
        bool end;
    public:
        friend class const_iterator;
        iterator(/*TODO*/)/*:...*/ { /*TODO*/ }
        iterator(Node *node) : n(node), end(false) {}
        iterator(Node *node, bool isEnd) : n(node), end(isEnd) {}
        // TODO: Other constructors as needed.
        bool operator==(const iterator &i) const { return n == i.n && end == i.end; }
        bool operator!=(const iterator &i) const { return !(*this == i); }
        std::pair<K,V> &operator*() { return n->data; }
        iterator &operator++() {
            if (!n) return *this; 
            if (n->right != nullptr) {
                n = n->right;
                while(n->left) n = n->left;
            } else {
                Node *tmp = n;
                Node *start = n;
                n = n->parent;
                while (n && tmp == n->right) {
                    tmp = n;
                    n = n->parent;
                }
                if (!n) {
                    n = start;
                    end = true;
                }
            }
            return *this;
        }
        iterator &operator--() {
            if (!n) return *this; 
            if (end) {
                end = false;
                return *this;
            }
            if (n->left != nullptr) {
                n = n->left;
                while(n->right) n = n->right;
            } else {
                Node *tmp = n;
                Node *start = n;
                n = n->parent;
                while (n && tmp == n->left) {
                    tmp = n;
                    n = n->parent;
                }
                if (!n) {
                    n = start;
                }
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
        // TODO: iterator data
        Node *n;
        bool end;
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(/*TODO*/)/*:...*/ { /*TODO*/ }
        const_iterator(Node *node) : n(node), end(false) {}
        const_iterator(Node *node, bool isEnd) : n(node), end(isEnd) {}
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter) : n(iter.n), end(iter.end) {}

        bool operator==(const const_iterator &i) const { return n == i.n && end == i.end; }
        bool operator!=(const const_iterator &i) const { return !(*this == i); }
        const std::pair<K,V> &operator*() { return n->data; }
        const_iterator &operator++() {
            if (!n) return *this; 
            if (n->right != nullptr) {
                n = n->right;
                while(n->left != nullptr) n = n->left;
            } else {
                Node *tmp = n;
                Node *start = n;
                n = n->parent;
                while (n && tmp == n->right) {
                    tmp = n;
                    n = n->parent;
                }
                if (!n) {
                    n = start;
                    end = true;
                }
            }
            return *this;
        }
        const_iterator &operator--() {
            if (!n) return *this; 
            if (end) {
                end = false;
                return *this;
            }
            if (n->left != nullptr) {
                n = n->left;
                while(n->right != nullptr) n = n->right;
            } else {
                Node *tmp = n;
                Node *start = n;
                n = n->parent;
                while (n && tmp == n->left) {
                    tmp = n;
                    n = n->parent;
                }
                if (!n) {
                    n = start;
                }
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    BSTMap() : root(nullptr), ct(0) {}
    
    ~BSTMap() {
        recursiveDelete(root);
    }
    
    BSTMap(const BSTMap<K,V> &that) {
        root = recursiveCopy(that.root, nullptr);
        ct = that.ct;
    }
    
    BSTMap &operator=(const BSTMap<K,V> &that) {
        // TODO
    }
    
    bool empty() const { return ct == 0; }
    
    unsigned size() const { return ct; }
    
    iterator find(const key_type& k) {
        Node *n = root;
        while(n) {
            if (n->data.first == k) break;
            if (n->data.first > k) n = n->left;
            else n = n->right;
        }
        if(!n) return end();
        return iterator(n);
    }
    
    const_iterator find(const key_type& k) const {
        Node *n = root;
        while(n) {
            if (n->data.first == k) break;
            if (n->data.first > k) n = n->left;
            else n = n->right;
        }
        if(!n) return end();
        return const_iterator(n);
    }
    
    unsigned int count(const key_type& k) {
        Node *n = root;
        while(n) {
            if (n->data.first == k) break;
            if (n->data.first > k) n = n->left;
            else n = n->right;
        }
        return n != nullptr;
    }
    
    std::pair<iterator,bool> insert(const value_type& val) {
        Node *n = root;
        Node *trail = nullptr;
        while(n) {
            if (n->data.first == val.first) return make_pair(iterator(n), false);
            trail = n;
            if (n->data.first > val.first) n = n->left;
            else n = n->right;
        }
        ++ct;
        Node *newNode = new Node();
        newNode->parent = trail;
        newNode->data = val;
        if(val.first < trail->data.first) {
            trail->left = newNode;
        } else {
            trail->right = newNode;
        }
        return make_pair(iterator(newNode), true);
    }
    
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter != last; ++iter) insert(*iter);
    }
    
    iterator erase(const_iterator position) {
        auto iter = begin();
        while((*iter).first != (*position).first) ++iter;
        erase((*iter).first); 
        return ++iter;
    }
    
    unsigned int erase(const key_type& k) {
        Node *n = root;
        while(n) {
            if (n->data.first == k) break;
            if (n->data.first > k) n = n->left;
            else n = n->right;
        }
        if(!n) return 0;
        --ct;
        if(!n->parent) {
            if(!n->left && !n->right) {
                delete n;
                root = nullptr;
                return 1;
            }
            if(!n->left && n->right != nullptr) {
                n->right->parent = n->parent;
                root = n->right;
                delete n;
                return 1;
            }
            if(n->left != nullptr && !n->right) {
                n->left->parent = n->parent;
                root = n->left;
                delete n;
                return 1;
            }
            if(n->left != nullptr && n->right != nullptr) {
                if(!n->left->right) {
                    n->data = n->left->data;
                    n->left = n->left->left;
                    if(n->left != nullptr) n->left->parent = n;
                } else {
                    Node *s = n->left->right;
                    while(s->right != nullptr) s = s->right;
                    s->parent->right = s->left;
                    if(s->left != nullptr) s->left->parent = s->parent;
                    n->data = s->data;
                    delete s;
                }
                return 1;
            }
        }
        if(!n->left && !n->right) {
            if(n->parent->left == n) n->parent->left = nullptr;
            else n->parent->right = nullptr;
            delete n;
            return 1;
        }
        if(!n->left && n->right != nullptr) {
            n->right->parent = n->parent;
            if(n->parent->left == n) n->parent->left = n->right;
            else n->parent->right = n->right;
            delete n;
            return 1;
        }
        if(n->left != nullptr && !n->right) {
            n->left->parent = n->parent;
            if(n->parent->right == n) n->parent->right = n->left;
            else n->parent->left = n->left;
            delete n;
            return 1;
        }
        if(n->left != nullptr && n->right != nullptr) {
            if(!n->left->right) {
                n->data = n->left->data;
                n->left = n->left->left;
                if(n->left != nullptr) n->left->parent = n;
            } else {
                Node *s = n->left->right;
                while(s->right != nullptr) s = s->right;
                s->parent->right = s->left;
                if(s->left != nullptr) s->left->parent = s->parent;
                n->data = s->data;
                delete s;
            }
            return 1;
        }
        return 0;
    }
    
    void clear() {
        ct = 0;
        recursiveDelete(root);
        root = nullptr;
    }
    
    mapped_type &operator[](const K &key) {
        Node *n = root;
        Node *trail = nullptr;
        while(n) {
            if (n->data.first == key) return n->data.second;
            trail = n;
            if (n->data.first > key) n = n->left;
            else n = n->right;
        }
        ++ct;
        Node *newNode = new Node();
        newNode->parent = trail;
        newNode->data.first = key;
    
        if (!trail) {
            root = newNode;
        } else {
            if (trail->data.first > key) trail->left = newNode;
            else trail->right = newNode;
        }

        return newNode->data.second;
    }
    
    bool operator==(const BSTMap<K,V>& rhs) const {
        auto niter = begin();
        auto riter = rhs.begin();
        while(niter != end() || riter != rhs.end()) {
            //if(niter == end() || riter == rhs.end()) return false;
            if((*niter).second != (*riter).second) return false;
            ++niter; ++riter;
        }
        return true;
    }
    
    bool operator!=(const BSTMap<K,V>& rhs) const { return !(*this == rhs); }

    iterator begin() { 
        Node *n = root;
        while(n->left) n = n->left;
        return iterator(n);
    }
    const_iterator begin() const {
        Node *n = root;
        while(n->left) n = n->left;
        return const_iterator(n);
    }
    iterator end() { 
        Node *n = root;
        while(n->right) n = n->right;
        return iterator(n, true); 
    }
    const_iterator end() const {
        Node *n = root;
        while(n->right) n = n->right;
        return const_iterator(n, true);
    }
    const_iterator cbegin() const {
        Node *n = root;
        while(n->left) n = n->left;
        return const_iterator(n);
    }
    const_iterator cend() const {
        Node *n = root;
        while(n->right) n = n->right;
        return const_iterator(n, true);
    }
    private:
        void recursiveDelete(Node* n) {
            if(!n) return;
            recursiveDelete(n->left);
            recursiveDelete(n->right);
            delete n;
        }
        Node* recursiveCopy(Node* n, Node *p) {
            if (!n) return nullptr;
            Node *newNode = new Node();
            newNode->parent = p;
            newNode->data = n->data;
            newNode->left = recursiveCopy(n->left,newNode);
            newNode->right = recursiveCopy(n->right,newNode);
            return newNode;
        }
        Node* pred(Node* n) {
            n = n->left;
            while(n->right) n = n->right;
            return n;
        }
};

#endif