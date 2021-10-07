#ifndef FILE_ARRAY_LIST
#define FILE_ARRAY_LIST

#include <iostream>
#include <string>
using std::fopen;

template<typename T>
class FileArrayList {
    // pribate data
    int ct;
    FILE * f;//means T* elem in ArrayList.h

    // pribate helper functions
    void writeElem(int index, const T &elem) const{
        std::fseek(f,sizeof(int) + index * sizeof(T), SEEK_SET);
        std::fwrite(&elem,sizeof(T),1,f);
    }

    void readElem(int index, T &elem){
        std::fseek(f,sizeof(int) + index * sizeof(T), SEEK_SET);
        std::fread(&elem,sizeof(T),1,f);
    }

    void writeSize() const {
        std::fseek(f,0,SEEK_SET);//start from the top
        std::fread(&ct,sizeof(T),1,f);
    }


    // copy construuctor
    FileArrayList(const FileArrayList<T> &that) = delete;
    FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;


    public:
    typedef T value_type;

    class const_iterator {
    // private data
    T* loc;


    public:
    const_iterator(int i,FILE *f);

    const_iterator(const const_iterator &i) : loc {i.loc}{}

    T operator*() {return *loc;}

    bool operator==(const const_iterator &i) const {return loc == i.loc;}

    bool operator!=(const const_iterator &i) const {return !(*this == i);}

    const_iterator &operator=(const const_iterator &i) {loc = i.loc; return *this;}

    const_iterator &operator++() {++loc; return *this;}

    const_iterator &operator--() {--loc; return *this;}

    const_iterator operator++(int){
        auto ret = loc;
        loc++;
        return ret;
    }

    const_iterator operator--(int){
        auto ret = loc;
        loc--;
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
            std::fread(&ct,sizeof(T),1,f);
        }else{
            ct = 0;
            writeSize();
        }
    }


    template<typename I> // The type I will be an iterator.
    FileArrayList(I begin,I end,const std::string &fname) {
    // TODO - Write this one here. It is easier than trying to fight with adding a template below.
}


~FileArrayList(){
    fflush(f);
    fclose(f);
    ct = 0;
}

//functions
void push_back(const T &t){
    writeElem(ct,t);
    ++ct;
    writeSize();
}

void pop_back(){ --ct; }

int size() const{ return ct; }

void clear(){ ct = 0;}

const_iterator insert(const_iterator position, const T &t){
    for(int i = ct; i > )
}

T operator[](int index) const;

const_iterator erase(const_iterator position);

void set(const T &value,int index);

const_iterator begin(){
    return SEEK_SET;
}

const_iterator begin() const{
    return const_iterator(f);
}

const_iterator end(){
    return const_iterator(f+ct);
}

const_iterator end() const{
    return const_iterator(f+ct);
}

const_iterator cbegin() const{
    return const_iterator(f);
}

const_iterator cend() const{
    return const_iterator(f+ct);
}
};

#endif