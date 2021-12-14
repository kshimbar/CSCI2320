#include "BSTMap.h"
#include <iostream>
#include <functional>
#include <utility>
#include <string>
#include <vector>

using std::cout;
using std::endl;

void doTests() {

	BSTMap<int,std::string> bst;
	if (!bst.empty()) cout << "Not empty!" << endl;

	bst[1] = "one";
	if (bst.empty()) cout << "Empty after []!" << endl;
	if (bst[1] != "one") cout << "incorrect data" << endl;
	bst[5] = "five";
	bst[3] = "three";
	bst[20] = "twenty";
	//cout << (*(bst.begin())).first << endl;
	//cout << (*(++bst.begin())).first << endl;
	BSTMap<int,std::string> bst2(bst);
	bst[5] = "FIVE";

	cout << "bst print" << endl;
	for (auto itr = bst.begin(); itr != bst.end(); ++itr) {
		cout << (*itr).second << endl;
	}
	cout << "bst2 print" << endl;
	for (auto itr = bst2.begin(); itr != bst2.end(); ++itr) {
		cout << (*itr).second << endl;
	}
}

int main() {
	doTests();
}
