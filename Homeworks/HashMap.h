#ifndef HASH_MAP
#define HASH_MAP

#include<vector>

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    // Data to store the hash table and the number of elements.
    std::vector<std::vector<std::pair<K,V>>> table;
    unsigned int ct;


public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;


    class const_iterator;

    class iterator {
        // NOTE: These might be different depending on how you store your table.
        decltype(table.begin()) mainIter;
        decltype(table.begin()) mainEnd;
        decltype(table[0].begin()) subIter;
    public:
        friend class const_iterator;

     // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
     // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

        bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator {
     // NOTE: These might be different depending on how you store your table.
        decltype(table.cbegin()) mainIter;
        decltype(table.cbegin()) mainEnd;
        decltype(table[0].cbegin()) subIter;
    public:
     // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
     // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.begin()) mi,
            const decltype(table.begin()) me,
            const decltype(table[0].begin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
     // NOTE: These might be different depending on how you store your table.
        const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {

        }

        bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf) : hashFunction(hf), table(11), ct(0) {};
    HashMap(const HashMap<K,V,Hash> &that){}; // Only if needed.
    HashMap &operator=(const HashMap<K,V,Hash> &that){}; // Only if needed.
    bool empty() const {return ct == 0;};
    unsigned int size() const { return ct; };
    iterator find(const key_type& k) {};
    const_iterator find(const key_type& k) const {};
    int count(const key_type& k) const {
        int hc = hashFunction(k);
        int bin = hc % table.size();
        for(auto &iter:table[bin]){
            if(k == iter.first){
                return 1;
            }
        }
        return 0;
    };
    std::pair<iterator,bool> insert(const value_type& val) {};

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        // TODO: Put this one here to simplify the templates
        
    }

    iterator erase(const_iterator position) {};
    int erase(const key_type& k) {};
    void clear() {
        for(auto &bin : table){
            bin.clear();
        }
        ct = 0;
    };
    mapped_type &operator[](const K &key) {
		int hc = hashFunction(key);
		int bin = hc % table.size();
		auto iter = find_if(table[bin].begin(),table[bin].end(),
			[&key](const std::pair<K,V> &tmp){return tmp.first == key; });
		if(iter == table[bin].end()) {
			++ct;
			table[bin].push_back(make_pair(key,V()));
			return table[bin].back().second;
		} else {
			return iter->second;
		}
    };
    bool operator==(const HashMap<K,V,Hash>& rhs) const {
        if(rhs.size() == ct){
            for(auto &bin:table){
                for(auto &iter : bin){
                    int hold = rhs.count(iter.first);
                    if(hold == 0){
                        return false;
                    }
                }
            }
            return true;
        }else return false;
    };
    bool operator!=(const HashMap<K,V,Hash>& rhs) const {
        if(rhs.size() != ct){
            for(auto &bin:table){
                for(auto &iter : bin){
                    int hold = rhs.count(iter.first);
                    if(hold == 1){
                        return false;
                    }
                }
            }
            return true;
        }else return false;
    };
    iterator begin() {};
    const_iterator begin() const {};
    iterator end() {};
    const_iterator end() const {};
    const_iterator cbegin() const {};
    const_iterator cend() const {};

private:
    void growTableAndRehash(){};
};

#endif