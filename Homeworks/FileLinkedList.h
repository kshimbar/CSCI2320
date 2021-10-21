#ifndef FILE_LINKED_LIST
#define FILE_LINKED_LIST

#include<string>
#include<cstdio>

template<typename T>
class FileLinkedList {
FileLinkedList(const FileLinkedList<T> &that) = delete;
FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

    FILE * f;
    int ct;
	int firstFree;
    void writeElem(int index, const T &elem, int prev, int next) const {
        std::fseek(f,2*sizeof(int)+(index*(sizeof(T)+2*sizeof(int))),SEEK_SET);
        std::fwrite(&elem,sizeof(T),1,f);
        std::fwrite(&prev,sizeof(int),1,f);
        std::fwrite(&next,sizeof(int),1,f);
    }
    void readElem(int index, T &elem) const {
        std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        std::fread(&elem,sizeof(T),1,f);
    }
    int readNext(int index) const {
        std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
        int ret;
        std::fread(&ret,sizeof(int),1,f);
        return ret;
    }
    int readPrev(int index) const {
        std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
        int ret;
        std::fread(&ret,sizeof(int),1,f);
        return ret;
    }
    void writeNext(int index, int next) const {
        std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
        std::fwrite(&next,sizeof(int),1,f);
    }
    void writePrev(int index, int prev) const {
        std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
        std::fwrite(&prev, sizeof(int),1,f);
    }
    void writeSizeAndFF() const {
        std::fseek(f, 0, SEEK_SET);
        std::fwrite(&ct, sizeof(int), 1, f);
        std::fwrite(&firstFree, sizeof(int), 1, f);
    }
    void readSizeAndFF(int &sz, int &ff) const {
        std::fseek(f, 0, SEEK_SET);
        std::fread(&sz, sizeof(int), 1, f);
        std::fread(&ff, sizeof(int), 1, f);
    }
public:
typedef T value_type;

class const_iterator {
int loc;
FILE * file;
public:
const_iterator(int i,FILE *f) : loc{i}, file{f} {
    std::fseek(file, (2 * sizeof(int)) + (i * ((2 * sizeof(int)) + sizeof(T))), SEEK_SET);
}
const_iterator(const const_iterator &i) : loc{i.loc}, file{i.file} {}
T operator*(){
    std::fseek(f,2*sizeof(int)+loc*(sizeof(T)+2*sizeof(int)),SEEK_SET);
    T dat;
    fread(&dat,sizeof(T),1,f);
    return dat;
}
bool operator==(const const_iterator &i) const { return loc == i.loc && file == i.file; }
bool operator!=(const const_iterator &i) const { return !(*this == i); }
const_iterator &operator=(const const_iterator &i){
    loc = i.loc;
    file = i.file;
    return *this;
}
const_iterator &operator++(){
    std::fseek(f,2*sizeof(int)+loc*(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
    std::fread(&loc,sizeof(int),1,f);
    return *this;

}
const_iterator &operator--(){
    std::fseek(f,2*sizeof(int)+loc*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
    std::fread(&loc,sizeof(int),1,f);
    return *this;
}
const_iterator operator++(int){
    const_iterator tmp(f, index);
    std::fseek(f,2*sizeof(int)+ index *(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
    std::fread(&loc,sizeof(int),1,f);
    return tmp;
}
const_iterator operator--(int){
    const_iterator tmp(f, index);
    std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
    std::fread(&loc,sizeof(int),1,f);
    return tmp;
}

friend class FileLinkedList;
};

FileLinkedList(const std::string &fname) {
	f = fopen(fname.c_str(),"r+"); // if successful, file exists
	if(f==nullptr) f = fopen(fname.c_str(),"w+");
	std::fseek(f,0,SEEK_END);
	if(std::ftell(f) > 0) { // data exists in file
		std::fseek(f,0,SEEK_SET);
		std::fread(&ct, sizeof(int), 1, f);
		std::fread(&firstFree, sizeof(int), 1, f);
	} else {
		ct = 1;
		firstFree = -1;
		writeSizeAndFF();
		T sent;
		writeElem(0,sent,0,0);
	}
}

template<typename I> 
FileLinkedList(I begin,I end,const std::string &fname) {
    f = fopen(fname.c_str(), "r+");
    if (f == nullptr) f = fopen(fname.c_str(), "w+");
    fseek(f, 0, SEEK_END);
    if (ftell(f) > 0) {
        fseek(f, 0, SEEK_SET);
        fread(&ct, sizeof(int), 1, f);
        fread(&firstFree, sizeof(int), 1, f);
        const_iterator itr = begin;
        while (itr != end) {
            const_iterator tmp = itr;
            writeElem(itr.loc, *itr, 0, 0);
            ++ct;
            --itr;
            writePrev(tmp.loc, itr.loc);
            ++++itr;
            writeNext(tmp.loc, itr.loc);
        }
        const_iterator endprev = --itr;
        writeElem(end.loc, *end, endprev.loc, begin.loc);
        writeSizeAndFF();
    } else {
        ct = 1;
        firstFree = -1;
        const_iterator itr = begin;
        while (itr != end) {
            const_iterator tmp = itr;
            writeElem(itr.loc, *itr, 0, 0);
            ++ct;
            --itr;
            writePrev(tmp.loc, itr.loc);
            ++++itr;
            writeNext(tmp.loc, itr.loc);
        }
        const_iterator endprev = --itr;
        writeElem(end.loc, *end, endprev.loc, begin.loc);
        writeSizeAndFF();
    }
}
~FileLinkedList(){
    fflush(f);
    fclose(f);
}
void push_back(const T &t){
    int n;
    if(firstFree < 0) {
        n = ct;
    } else {
        n = firstFree;
        firstFree = readNext(firstFree);
    }
    int tail = readPrev(0);
    writeElem(n, t, tail, 0);
    writePrev(0, n);
    writeNext(tail, n);
    ++ct;
    writeSizeAndFF();
}
void pop_back(){
	int tail = readPrev(0);
	int tailPrev = readPrev(tail);
	writeNext(tailPrev,0);
	writePrev(0,tailPrev);
	writeNext(tail,firstFree);
	firstFree = tail;
	--ct;
	writeSizeAndFF();
}
int size() const{
    int tmp;
    int ff;
    readSizeAndFF(tmp, ff);
    return tmp - 1;
}
void clear(){
    ct = 1;
    firstFree = -1;
    writeSizeAndFF();
    T garbage;
    writeElem(0, garbage, 0, 0);
}
const_iterator insert(const_iterator position, const T &t){
    int n;
    int pos = position.loc;
    int prev = readPrev(pos);
    if(firstFree < 0) {
        n = ct;
    } else {
        n = firstFree;
        firstFree = readNext(firstFree);
    }
    writeElem(n, t, prev, pos);
    writeNext(prev, n);
    writePrev(pos, n);
    ++ct;
    writeSizeAndFF();
    return position;    
}
T operator[](int index) const{
    const_iterator tmp = begin();
    for(int i = 0; i < index; ++i) ++tmp;
    return *tmp;
}
const_iterator erase(const_iterator position){
    int pos = position.loc;
    int prev = readPrev(pos);
    int next = readNext(pos);
    writeNext(prev, next);
    writePrev(next, prev);
    writeNext(pos, firstFree);
    firstFree = pos;
    --ct;
    writeSizeAndFF();
    return ++--position;
}
void set(const T &value,int index){
    writeElem(index + 1, value, readPrev(index + 1), readNext(index + 1));
}
void set(const T &value,const_iterator position){
    writeElem(position.loc, value, readPrev(position.loc), readNext(position.loc));
}

const_iterator begin() { return const_iterator(readNext(0), f); }
const_iterator begin() const{ return const_iterator(readNext(0), f); }
const_iterator end() { return const_iterator(0, f); }
const_iterator end() const { return const_iterator(0, f); }
const_iterator cbegin() const{ return const_iterator(readNext(0), f); }
const_iterator cend() const { return const_iterator(0, f); }
};

#endif

