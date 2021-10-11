#ifndef FILE_LINKED_LIST
#define FILE_LINKED_LIST

#include <cstdio>
#include <string>
using std::fopen;
template<typename T>
class FileLinkedList {
	FILE * f;
	int ct;
	int firstFree;

	void writeElem(int index, const T &elem, int prev, int next) const;
	void readElem(int index, T &elem) const;
	int readNext(int index) const;
	int readPrev(int index) const;
	void writeNext(int index, int next) const;
	void writePrev(int index, int prev) const;
	void writeSize() const;
	void writeSizeAndFF() const;

	public:
		FileLinkedList(const std::string &fname);
		void push_back(const T &t);
		T operator[](int index) const;
		class const_iterator {
			FILE *f;
			int index;
			public:
				const_iterator(FILE * fi, int i) : f{fi},index{i} {}
				const_iterator(const const_iterator &i) : f{i.f},index{i.index} {}
				T operator*() {
					fseek(f,sizeof(int)+index*sizeof(T),SEEK_SET);
					T dat;
					fread(&dat,sizeof(T),1,f);
					return dat;
				}
				bool operator==(const const_iterator &i) {return index==i.index && f==i.f;}
				bool operator!=(const const_iterator &i) {return !(*this == i);}
				const_iterator& operator=(const const_iterator &i) {index=i.index;f=i.f;return *this;}
				const_iterator& operator++() {++index; return *this;}
				const_iterator& operator--() {--index; return *this;}
				const_iterator operator++(int) {
					const_iterator tmp(f, index);
					++index;
					return tmp;
				}
				const_iterator operator--(int) {
					const_iterator tmp(f, index);
					--index;
					return tmp;
				}
				friend class FileLinkedList;
		};

		const_iterator begin() { return const_iterator(f, 0); };
		const_iterator begin() const { return const_iterator(f, 0); };
		const_iterator cbegin() const{ return const_iterator(f, 0); };
		const_iterator end() { return const_iterator(f,ct);};
		const_iterator end() const {return const_iterator(f,ct);};
		const_iterator cend() const {return const_iterator(f,ct);};
};

template<typename T>
FileLinkedList<T>::FileLinkedList(const std::string &fname) {
	f = fopen(fname.c_str(),"r+"); // if successful, file exists
	if(f==nullptr) f = fopen(fname.c_str(),"w+");
	std::fseek(f,0,SEEK_END);
	if(std::ftell(f) > 0) { // data exists in file
		std::fseek(f,0,SEEK_SET);
		std::fread(&ct, sizeof(int), 1, f);
	} else {
		ct = 0;
		firstFree = -1;
		writeSize();
	}
}

template<typename T>
void FileLinkedList<T>::push_back(const T &t) {
	writeElem(ct,t);
	++ct;
	writeSize();
}

template<typename T>
T FileLinkedList<T>::operator[](int index) const{
	T tmp;
	readElem(index,tmp);
	return tmp;
}

template<typename T>
void FileLinkedList<T>::writeElem(int index, const T &elem) const {
	std::fseek(f,sizeof(int)+(index*sizeof(T)),SEEK_SET);
	std::fwrite(&elem,sizeof(T),1,f);
}

template<typename T>
void FileLinkedList<T>::readElem(int index, T &elem) const {
	std::fseek(f,sizeof(int)+(index*sizeof(T)),SEEK_SET);
	std::fread(&elem,sizeof(T),1,f);	
}

template<typename T>
void FileLinkedList<T>::writeSize() const {
	std::fseek(f,0,SEEK_SET);
	std::fwrite(&ct,sizeof(int),1,f);
}

template<typename T>
void FileLinkedList<T>::writeSizeAndFF() const {
	std::fseek(f,0,SEEK_SET);
	std::fwrite(&ct,sizeof(int),1,f);
	std::fwrite(&firstFree,sizeof(int),1,f);
}
#endif
