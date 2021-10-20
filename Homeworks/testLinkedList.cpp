#include <iostream>
#include "FileLinkedList.h"

int main() {
	FileLinkedList<int> lst1("data.bin");
	lst1.push_back(2);
	lst1.push_back(4);
	lst1.push_back(6);
	lst1.push_back(8);
	lst1.pop_back();
	lst1.push_back(10);
	//std::cout << lst1[0] << std::endl;
	//std::cout << lst1[1] << std::endl;
	for(auto e : lst1) { // 2,4,6,10
		std::cout << e << std::endl;
	}
	return 0;
}
