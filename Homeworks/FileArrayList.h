#ifndef FILE_ARRAY_LIST
#define FILE_ARRAY_LIST

#include<string>
#include<cstdio>

template<typename T>
class FileArrayList {
    FileArrayList(const FileArrayList<T> &that) = delete;
    FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;

    FILE * f;
    int ct;
    void writeElem(int index, const T &elem) const {
        fseek(f, sizeof(int) + (index * sizeof(T)), SEEK_SET);
        fwrite(&elem, sizeof(T), 1, f);
    }
    void readElem(int index, T &elem) const {
        fseek(f, sizeof(int) + (index * sizeof(T)), SEEK_SET);
        fread(&elem, sizeof(T), 1, f);
    }
    void writeSize() const {
        fseek(f, 0, SEEK_SET);
        fwrite(&ct, sizeof(int), 1, f);
    }
    void readSize(int &sz) const {
        fseek(f, 0, SEEK_SET);
        fread(&sz, sizeof(int), 1, f);
    }

    public:
        typedef T value_type;

        class const_iterator {
            int elem;
            FILE * file;
            public:
                const_iterator(int i,FILE *f) : elem{i}, file{f} {
                    fseek(file, sizeof(int) + (i * sizeof(T)), SEEK_SET);
                }
                const_iterator(const const_iterator &i) : elem{i.elem}, file{i.file} {}
                T operator*() {
                    T tmp;
                    fseek(file, sizeof(int) + (elem * sizeof(T)), SEEK_SET);
                    fread(&tmp, sizeof(T), 1, file);
                    return tmp;
                }
                bool operator==(const const_iterator &i) const { return elem == i.elem; }
                bool operator!=(const const_iterator &i) const { return !(*this == i); }
                const_iterator &operator=(const const_iterator &i) {
                    elem = i.elem;
                    file = i.file;
                    return *this;
                }
                const_iterator &operator++() { elem++; return *this; }
                const_iterator &operator--() { elem--; return *this; }
                const_iterator operator++(int) {
                    int ret = elem;
                    this->elem = ret;
                    ++elem;
                    return *this;
                }
                const_iterator operator--(int) {
                    int ret = elem;
                    this->elem = ret;
                    --elem;
                    return *this;
                }

                friend class FileArrayList;
        };

        // General Methods
        FileArrayList(const std::string &fname) {
            f = fopen(fname.c_str(), "r+");
            if (f == nullptr) f = fopen(fname.c_str(), "w+");
            fseek(f, 0, SEEK_END);
            if (ftell(f) > 0) {
                fseek(f, 0, SEEK_SET);
                fread(&ct, sizeof(int), 1, f);
            } else {
                ct = 0;
                writeSize();
            }
        }

        template<typename I> // The type I will be an iterator.
        FileArrayList(I begin,I end,const std::string &fname) {
            f = fopen(fname.c_str(), "r+");
            if (f == nullptr) f = fopen(fname.c_str(), "w+");
            fseek(f, 0, SEEK_END);
            if (ftell(f) > 0) {
                fread(&ct, sizeof(int), 1, f);
                const_iterator itr = begin;
                while (itr != end) {
                    writeElem(itr.elem++, *itr);
                    ++ct;
                }
            } else {
                ct = 0;
                writeSize();
                const_iterator itr = begin;
                while(itr != end) {
                    writeElem(itr.elem++, *itr);
                    ++ct;
                }
            }
        }
        ~FileArrayList() {
            fflush(f);
            fclose(f);
        }
        void push_back(const T &t) { writeElem(ct++, t); writeSize(); }
        void pop_back() { --ct; writeSize(); }
        int size() const {
            int tmp;
            readSize(tmp);
            return tmp;
        }
        void clear() { ct = 0; writeSize(); }
        const_iterator insert(const_iterator position, const T &t) {
            const_iterator itr = --end();
            while(itr != position) {
                writeElem(itr.elem + 1, *itr);
                --itr;
            }
            writeElem(itr.elem + 1, *itr);
            writeElem(itr.elem, t);
            ++ct;
            writeSize();
            return itr;
        }
        T operator[](int index) const {
            T tmp;
            readElem(index, tmp);
            return tmp;
        }
        const_iterator erase(const_iterator position) {
            const_iterator itr = ++position;
            while(itr != end()) {
                writeElem(itr.elem - 1, *itr);
                ++itr;
            }
            --ct;
            writeSize();
            return itr;
        }
        void set(const T &value,int index) {
            writeElem(index, value);
        }

        const_iterator begin() { return const_iterator(0, f); }
        const_iterator begin() const { return const_iterator(0, f); }
        const_iterator end() { return const_iterator(ct, f); }
        const_iterator end() const { return const_iterator(ct, f); }
        const_iterator cbegin() const { return const_iterator(ct, f); }
        const_iterator cend() const { return const_iterator(ct, f); }
};

#endif
