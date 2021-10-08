#ifndef FILE_ARRAY_LIST
#define FILE_ARRAY_LIST

#include <iostream>
#include<cstdio>
using std::fopen;

template<typename T>
class FileArrayList {
    // pribate data
    int ct;
    FILE * f;//means T* elem in ArrayList.h

    // pribate helper functions
    void writeElem(int index, const T &ele) const{
        std::fseek(f,sizeof(int) + index * sizeof(T), SEEK_SET);
        std::fwrite(&ele,sizeof(T),1,f);
    }

    void readElem(int index, T &ele) const{
        std::fseek(f,sizeof(int) + index * sizeof(T), SEEK_SET);
        std::fread(&ele,sizeof(T),1,f);
    }

    void writeSize() const {
        std::fseek(f,0,SEEK_SET);//start from the top
        std::fwrite(&ct,sizeof(int),1,f);
    }

    void readSize(int &sz) const {
        fseek(f, 0, SEEK_SET);
        fread(&sz, sizeof(int), 1, f);
    }


    // copy construuctor
    FileArrayList(const FileArrayList<T> &that) = delete;
    FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;


    public:
    typedef T value_type;

    class const_iterator {
    // private data
    int pos;
    FILE * fil;

    public:
    const_iterator(int i,FILE *f){
        pos = i; 
        fil = f;
        std::fseek(fil,sizeof(int) + (i * sizeof(T)),SEEK_SET);
    }

    const_iterator(const const_iterator &i){
        pos = i.pos; 
        fil = i.fil;
    }

    T operator*() {
        T tmp;
        std::fseek(fil,(pos * sizeof(T)),SEEK_SET);
        std::fseek(fil,(pos * sizeof(T)),SEEK_SET);
        fread(&tmp,sizeof(T),1,fil);
        return tmp;
    }

    bool operator==(const const_iterator &i) const {return pos == i.pos;}

    bool operator!=(const const_iterator &i) const {return !(*this == i);}

    const_iterator &operator=(const const_iterator &i) {pos = i.pos; fil = i.fil; return *this;}

    const_iterator &operator++() {pos++; return *this;}

    const_iterator &operator--() {pos--; return *this;}

    const_iterator operator++(int){
        int ret = pos;
        this->pos = ret;
        ++pos;
        return *this;
    }

    const_iterator operator--(int){
        int ret = pos;
        this->pos = ret;
        --pos;
        return ret;
    }

    friend class FileArrayList;
    };

    // General Methods
    FileArrayList(const std::string &fname){
        f = fopen(fname.c_str(), "r+");
        if(f == NULL){
            f = fopen(fname.c_str(),"w+");
        }
        std::fseek(f,0,SEEK_END);
        if(std::ftell(f) > 0){
            //ftell will tell the size of the file
            //data exists in the file
            std::fseek(f,0,SEEK_SET);//start from the top
            std::fread(&ct,sizeof(int),1,f);
        }else{
            ct = 0;
            writeSize();
        }
    }


    template<typename I> // The type I will be an iterator.
    FileArrayList(I begin,I end,const std::string &fname) {
    // TODO - Write this one here. It is easier than trying to fight with adding a template below.
    f = fopen(fname.c_str(), "r+");
    if(f == NULL){
        f = fopen(fname.c_str(),"w+");
    }
    std::fseek(f,0,SEEK_END);
    if(std::ftell(f) > 0){
        //ftell will tell the size of the file
        //data exists in the file
        fread(&ct, sizeof(int), 1, f);
        const_iterator itr = begin;
        while (itr != end) {
            writeElem(itr.pos++, *itr);
            ++ct;
        }
    }else{
        ct = 0;
        writeSize();
        const_iterator itr = begin;
        while(itr != end) {
            writeElem(itr.pos++, *itr);
            ++ct;
        }
    }
}


~FileArrayList(){
    fflush(f);
    fclose(f);
}

//functions
void push_back(const T &t){
    writeElem(ct++,t);
    writeSize();
}

void pop_back(){ --ct; writeSize();}

int size() const{
    int tmp;
    readSize(tmp);
    return tmp;
}

void clear(){ ct = 0; writeSize();}

const_iterator insert(const_iterator position, const T &t){
    const_iterator itr = --end();
    while(itr != position) {
        writeElem(itr.pos + 1, *itr);
        --itr;
    }
    writeElem(itr.pos + 1, *itr);
    writeElem(itr.pos, t);
    ++ct;
    writeSize();
    return itr;
}   

T operator[](int index) const{
    T tmp;
    readElem(index,tmp);
    return tmp;
}

const_iterator erase(const_iterator position){
    const_iterator po = ++position;
    while(po != end()) {
        writeElem(po.pos - 1, *po);
        ++po;
    }
    --ct;
    writeSize();
    return po;
}

void set(const T &value,int index){
    writeElem(index, value);
}

const_iterator begin(){
    return const_iterator(0,f);
}

const_iterator begin() const{
    return const_iterator(0,f);
}

const_iterator end(){
    return const_iterator(ct,f);
}

const_iterator end() const{
    return const_iterator(ct,f);
}

const_iterator cbegin() const{
    return const_iterator(0,f);
}

const_iterator cend() const{
    return const_iterator(ct,f);
}
};

#endif