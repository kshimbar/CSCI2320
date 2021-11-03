#include <vector>
#include <utility>
#include <algorithm>

template <typename K, typename V, typename Hash>
class HashMap
{
    Hash hashFunction;
    // Data to store the hash table and the number of elements.
    std::vector<std::vector<std::pair<K, V>>> table;
    unsigned int ct;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K, V> value_type;

    class const_iterator;

    class iterator
    {
        // NOTE: These might be different depending on how you store your table.
        decltype(table.begin()) mainIter;
        decltype(table.begin()) mainEnd;
        decltype(table[0].begin()) subIter;

    public:
        friend class const_iterator;

        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi, const decltype(mainEnd) me) : mainIter(mi), mainEnd(me)
        {
            if (mainIter != mainEnd)
                subIter = mainIter->begin();
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
        }

        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,
                 const decltype(mainEnd) me,
                 const decltype(subIter) si) : mainIter(mi), mainEnd(me), subIter(si) {}

        bool operator==(const iterator &i) const { return mainIter == i.mainIter && (mainIter == mainEnd || subIter == i.subIter); }

        bool operator!=(const iterator &i) const { return !(*this == i); }

        std::pair<K, V> &operator*() { return *subIter; }

        iterator &operator++()
        {
            ++subIter;
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator
    {
        // NOTE: These might be different depending on how you store your table.
        decltype(table.cbegin()) mainIter;
        decltype(table.cbegin()) mainEnd;
        decltype(table[0].cbegin()) subIter;

    public:
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi, const decltype(table.cbegin()) me) : mainIter(mi), mainEnd(me)
        {
            if (mainIter != mainEnd)
                subIter = mainIter->begin();
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
        }

        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.begin()) mi,
                       const decltype(table.begin()) me,
                       const decltype(table[0].begin()) si) : mainIter(mi), mainEnd(me), subIter(si) {}

        // NOTE: These might be different depending on how you store your table.
        const_iterator(const iterator &i) : mainIter(i.mainIter), mainEnd(i.mainEnd), subIter(i.subIter) {}

        bool operator==(const const_iterator &i) const { return mainIter == i.mainIter && (mainIter == mainEnd || subIter == i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this == i); }
        const std::pair<K, V> &operator*() const { return *subIter; }
        const_iterator &operator++()
        {
            ++subIter;
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    // constructor
    HashMap(const Hash &hf) : hashFunction(hf), table(11), ct(0){};

    // HashMap(const HashMap<K, V, Hash> &that){}; // Only if needed.

    // HashMap &operator=(const HashMap<K, V, Hash> &that){}; // Only if needed.

    bool empty() const { return ct == 0; };

    unsigned int size() const { return ct; };

    iterator find(const key_type &k)
    {
        int hc = hashFunction(k);
        int bin = hc % table.size();
        auto idx = find_if(table[bin].begin(), table[bin].end(), [&k](const std::pair<K, V> &tmp)
                           { return k == tmp.first; });
        if (idx != table[bin].end())
        {
            auto val = std::make_pair(k, (*idx).second);
            auto loc = find_if(table[bin].begin(), table[bin].end(), [&val](const std::pair<K, V> &tmp)
                               { return val == tmp; });
            return (iterator(table.begin(), table.end(), loc));
        }
    };

    const_iterator find(const key_type &k) const
    {
        int hc = hashFunction(k);
        int bin = hc % table.size();
        auto idx = find_if(table[bin].begin(), table[bin].end(), [&k](const std::pair<K, V> &tmp)
                           { return k == tmp.first; });
        if (idx != table[bin].end())
        {
            auto val = std::make_pair(k, (*idx).second);
            auto loc = find_if(table[bin].begin(), table[bin].end(), [&val](const std::pair<K, V> &tmp)
                               { return val == tmp; });
            return (iterator(table.begin(), table.end(), loc));
        }
    };

    int count(const key_type &k) const
    {
        int hc = hashFunction(k);
        int bin = hc % table.size();
        auto iter = find_if(table[bin].begin(), table[bin].end(), [&k](const std::pair<K, V> &tmp)
                            { return k == tmp.first; });

        if (iter == table[bin].end())
            return 0;
        else
            return 1;
    };

    std::pair<iterator, bool> insert(const value_type &val)
    {
        auto key = val.first;
        auto value = val.second;

        // get the hash
        int hashIndex = hashFunction(key);
        int bin = hashIndex % table.size();

        auto idx = find_if(table[bin].begin(), table[bin].end(), [&key](const std::pair<K, V> &tmp)
                           { return key == tmp.first; });

        if (idx == table[bin].end())
        {
            if ((double(ct) / table.size()) > 0.5)
            {
                growTableAndRehash();
                hashIndex = hashFunction(key);
                bin = hashIndex % table.size();
            }
            table[bin].push_back(std::make_pair(key, value));
            ++ct;
            auto loc = find_if(table[bin].begin(), table[bin].end(), [&val](const std::pair<K, V> &tmp)
                               { return val == tmp; });
            return std::make_pair(iterator(table.begin(), table.end(), loc), true);
        }

        return (std::make_pair(iterator(table.begin(), table.end(), idx), false));
    };

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        for (auto idx = first; idx != last; ++idx)
        {
            auto key = (*idx).first;
            auto value = (*idx).second;

            // get the hash
            int hashIndex = hashFunction(key);
            int bin = hashIndex % table.size();

            auto exists = find_if(table[bin].begin(), table[bin].end(), [&key](const std::pair<K, V> &tmp)
                                  { return key == tmp.first; });

            if (exists == table[bin].end())
            {
                if ((double(ct) / table.size()) > 0.5)
                {
                    growTableAndRehash();
                    hashIndex = hashFunction(key);
                    bin = hashIndex % table.size();
                }
                table[bin].push_back(std::make_pair(key, value));
                ct++;
            }
        }
    }

    iterator erase(const_iterator position)
    {
        auto key = (*position).first;
        auto value = (*position).second;

        // get the hash
        int hashIndex = hashFunction(key);
        int bin = hashIndex % table.size();

        auto exists = find_if(table[bin].begin(), table[bin].end(), [&key](const std::pair<K, V> &tmp)
                              { return key == tmp.first; });

        if (exists != table[bin].end())
        {
            table[bin].erase(exists);
            ct--;
        }
    };

    int erase(const key_type &k)
    {
        int hc = hashFunction(k);
        int bin = hc % table.size();
        int elemErased = 0;
        auto iter = find_if(table[bin].begin(), table[bin].end(), [&k](const std::pair<K, V> &tmp)
                            { return k == tmp.first; });

        if (iter != table[bin].end())
        {
            table[bin].erase(iter);
            ct--;
            return 1;
        }
        else
            return 0;
    };

    void clear()
    {
        for (unsigned int i = 0; i < table.size(); ++i)
            table[i].clear();
        ct = 0;
    }

    mapped_type &operator[](const K &key)
    {
        int hashIndex = hashFunction(key);
        int bin = hashIndex % table.size();

        auto iter = find_if(table[bin].begin(), table[bin].end(), [&key](const std::pair<K, V> &tmp)
                            { return key == tmp.first; });

        if (iter == table[bin].end())
        {
            if ((double(ct) / table.size()) > 0.5)
            {
                growTableAndRehash();
                hashIndex = hashFunction(key);
                bin = hashIndex % table.size();
            }
            table[bin].push_back(std::make_pair(key, V()));
            ct++;
            return table[bin].back().second;
        }
        else
            return iter->second;
    }

    bool operator==(const HashMap<K, V, Hash> &rhs) const
    {
        if (ct != rhs.size())
            return false;

        for (auto &c : table)
            for (auto &p : c)
            {
                if (rhs.count(p.first) == 0)
                {
                    return false;
                }
            }
        return true;
    };

    bool operator!=(const HashMap<K, V, Hash> &rhs) const
    {
        if (ct != rhs.size())
            return true;

        for (auto &c : table)
            for (auto &p : c)
            {
                if (rhs.count(p.first) == 0)
                {
                    return true;
                }
            }
        return false;
    };

    iterator begin()
    {
        return iterator(table.begin(), table.end());
    };

    const_iterator begin() const
    {
        return const_iterator(table.begin(), table.end());
    };

    iterator end()
    {
        return iterator(table.end(), table.end());
    };

    const_iterator end() const
    {
        return iterator(table.end(), table.end());
    };

    const_iterator cbegin() const
    {
        return const_iterator(table.begin(), table.end());
    };

    const_iterator cend() const
    {
        return const_iterator(table.end(), table.end());
    };

private:
    void growTableAndRehash()
    {
        int newSize = table.size() * 2;

        std::vector<std::vector<std::pair<K, V>>> newTable(newSize);

        for (auto &c : table)
            for (auto &p : c)
            {
                auto key = p.first;
                auto value = p.second;

                // get the hash
                int hashIndex = hashFunction(key);
                int bin = hashIndex % newTable.size();

                auto idx = find_if(newTable[bin].begin(), newTable[bin].end(), [&key](const std::pair<K, V> &tmp)
                                   { return key == tmp.first; });

                if (idx == newTable[bin].end())
                    newTable[bin].push_back(std::make_pair(key, value));
            }
        table = newTable;
    }
};
