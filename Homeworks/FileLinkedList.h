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
		void pop_back();
		T operator[](int index) const;
		class const_iterator {
			FILE *f;
			int index;
			public:
				const_iterator(FILE * fi, int i) : f{fi},index{i} {}
				const_iterator(const const_iterator &i) : f{i.f},index{i.index} {}
				T operator*() {
					std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
					T dat;
					fread(&dat,sizeof(T),1,f);
					return dat;
				}
				bool operator==(const const_iterator &i) {return index==i.index && f==i.f;}
				bool operator!=(const const_iterator &i) {return !(*this == i);}
				const_iterator& operator=(const const_iterator &i) {index=i.index;f=i.f;return *this;}
				const_iterator& operator++() {
					std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
					std::fread(&index,sizeof(int),1,f);
					return *this;
				}
				const_iterator& operator--() {
					std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
					std::fread(&index,sizeof(int),1,f);
					return *this;
				}
				const_iterator operator++(int) {
					const_iterator tmp(f, index);
					std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
					std::fread(&index,sizeof(int),1,f);
					return tmp;
				}
				const_iterator operator--(int) {
					const_iterator tmp(f, index);
					std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
					std::fread(&index,sizeof(int),1,f);
					return tmp;
				}
				friend class FileLinkedList;
		};

		const_iterator begin() { return const_iterator(f, readNext(0)); };
		const_iterator begin() const { return const_iterator(f, readNext(0)); };
		const_iterator cbegin() const{ return const_iterator(f, readNext(0)); };
		const_iterator end() { return const_iterator(f,0);};
		const_iterator end() const {return const_iterator(f,0);};
		const_iterator cend() const {return const_iterator(f,0);};
};

template<typename T>
FileLinkedList<T>::FileLinkedList(const std::string &fname) {
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

template<typename T>
void FileLinkedList<T>::push_back(const T &t) {
	int n;
	if (firstFree < 0) {
		n = ct;
	} else {
		n = firstFree;
		firstFree = readNext(firstFree);
	}
	int tail = readPrev(0);
	writeElem(n,t,tail,0);
	writePrev(0,n);
	writeNext(tail,n);
	++ct;
	writeSizeAndFF();
}

template<typename T>
void FileLinkedList<T>::pop_back() {
	int tail = readPrev(0);
	int tailPrev = readPrev(tail);
	writeNext(tailPrev,0);
	writePrev(0,tailPrev);
	writeNext(tail,firstFree);
	firstFree = tail;
	--ct;
	writeSizeAndFF();
}

template<typename T>
T FileLinkedList<T>::operator[](int index) const{
	T tmp;
	readElem(index,tmp);
	return tmp;
}

template<typename T>
void FileLinkedList<T>::writeElem(int index, const T &elem, int prev, int next) const {
	std::fseek(f,2*sizeof(int)+(index*(sizeof(T)+2*sizeof(int))),SEEK_SET);
	std::fwrite(&elem,sizeof(T),1,f);
	std::fwrite(&prev,sizeof(int),1,f);
	std::fwrite(&next,sizeof(int),1,f);
}

template<typename T>
void FileLinkedList<T>::readElem(int index, T &elem) const {
	std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
	std::fread(&elem,sizeof(T),1,f);	
}

template<typename T>
int FileLinkedList<T>::readNext(int index) const {
	std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
	int ret;
	std::fread(&ret,sizeof(int),1,f);
	return ret;
}
template<typename T>
void FileLinkedList<T>::writeNext(int index, int next) const {
	std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T)+sizeof(int), SEEK_SET);
	std::fwrite(&next,sizeof(int),1,f);
}
 
template<typename T>
int FileLinkedList<T>::readPrev(int index) const {
	std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
	int ret;
	std::fread(&ret,sizeof(int),1,f);
	return ret;
} 
template<typename T>
void FileLinkedList<T>::writePrev(int index, int prev) const {
	std::fseek(f,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int))+sizeof(T), SEEK_SET);
	std::fwrite(&prev, sizeof(int),1,f);
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
