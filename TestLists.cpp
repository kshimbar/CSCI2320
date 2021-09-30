#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<cstdlib>
#include "LinkedList.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::list;
using std::rand;

template<typename T>
bool passByValue(T lst) {
	auto tmp = lst.size();
	lst.push_back(5);
	return lst.size()==tmp+1 && lst[tmp]==5;
}

LinkedList<int> returnLittleLL() {
	LinkedList<int> ret;
	ret.push_back(1);
	ret.push_back(2);
	ret.push_back(3);
	return ret;
}

LinkedList<int> add3AndReturn(LinkedList<int> ll) {
	ll.push_back(9);
	ll.push_back(8);
	ll.push_back(7);
	return ll;
}

template<typename T>
bool simpleTest(T &lst1) {
	lst1.push_back(5);
	lst1.push_back(6);
	lst1.push_back(7);
	lst1.push_back(8);
	lst1.push_back(9);
	if(lst1[0]!=5) { cout << "[0] error." << endl; return false; }
	if(lst1[1]!=6) { cout << "[1] error." << endl; return false; }
	if(lst1[2]!=7) { cout << "[2] error." << endl; return false; }
	if(lst1[3]!=8) { cout << "[3] error." << endl; return false; }
	if(lst1[4]!=9) { cout << "[4] error." << endl; return false; }

	int cnt = 5;
	for(auto iter = lst1.begin(); iter!=lst1.end(); ++iter) {
		if(*iter!=cnt) {
			cout << "iter error " << cnt << endl;
			return false;
		}
		--(*iter);
		++cnt;
	}
	cnt = 4;
	for(auto iter = lst1.cbegin(); iter!=lst1.cend(); ++iter) {
		if(*iter!=cnt) {
			cout << "const_iter error " << cnt << endl;
			return false;
		}
		++cnt;
	}
	cnt = 8;
	for(auto iter = --lst1.end(); iter!=lst1.begin(); --iter) {
		if(*iter!=cnt) {
			cout << "--iter error " << cnt << endl;
			return false;
		}
		--cnt;
	}
	lst1[2] = 99;
	if(lst1[2]!=99) {
		cout << "[] error." << endl;
		return false;
	}
	T lst2(lst1);
	lst1.erase(++++lst1.begin());
	if(lst1[0]!=4) { cout << "After erase lst1[0]." << endl; return false; }
	if(lst1[1]!=5) { cout << "After erase lst1[1]." << endl; return false; }
	if(lst1[2]!=7) { cout << "After erase lst1[2]." << endl; return false; }
	if(lst1[3]!=8) { cout << "After erase lst1[3]." << endl; return false; }
	if(lst2[0]!=4) { cout << "After erase lst2[0]." << endl; return false; }
	if(lst2[1]!=5) { cout << "After erase lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After erase lst2[2]." << endl; return false; }
	if(lst2[3]!=7) { cout << "After erase lst2[3]." << endl; return false; }
	if(lst2[4]!=8) { cout << "After erase lst2[4]." << endl; return false; }
	lst2.insert(++++++lst2.begin(),98);
	if(lst2[0]!=4) { cout << "After insert lst2[0]." << endl; return false; }
	if(lst2[1]!=5) { cout << "After insert lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After insert lst2[2]." << endl; return false; }
	if(lst2[3]!=98) { cout << "After insert lst2[3]." << endl; return false; }
	if(lst2[4]!=7) { cout << "After insert lst2[4]." << endl; return false; }
	if(lst2[5]!=8) { cout << "After insert lst2[5]." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=5) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=4) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=3) { cout << "bad size after pop_back." << endl; return false; }
	if(lst2[0]!=4) { cout << "After pop_back lst2[0]." << endl; return false; }
	if(lst2[1]!=5) { cout << "After pop_back lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After pop_back lst2[2]." << endl; return false; }
	return true;
}

template<typename T>
bool stringTest(T &lst1) {
	lst1.push_back("5");
	lst1.push_back("6");
	lst1.push_back("7");
	lst1.push_back("8");
	lst1.push_back("9");
	if(lst1[0]!="5") { cout << "string [0] error." << endl; return false; }
	if(lst1[1]!="6") { cout << "string [1] error." << endl; return false; }
	if(lst1[2]!="7") { cout << "string [2] error." << endl; return false; }
	if(lst1[3]!="8") { cout << "string [3] error." << endl; return false; }
	if(lst1[4]!="9") { cout << "string [4] error." << endl; return false; }

	lst1[2] = "99";
	if(lst1[2]!="99") {
		cout << "[] error." << endl;
		return false;
	}
	T lst2(lst1);
	lst1.erase(lst1.begin()++++);
	if(lst1[0]!="5") { cout << "string After erase lst1[0]." << endl; return false; }
	if(lst1[1]!="6") { cout << "string After erase lst1[1]." << endl; return false; }
	if(lst1[2]!="8") { cout << "string After erase lst1[2]." << endl; return false; }
	if(lst1[3]!="9") { cout << "string After erase lst1[3]." << endl; return false; }
	if(lst2[0]!="5") { cout << "string After erase lst2[0]." << endl; return false; }
	if(lst2[1]!="6") { cout << "string After erase lst2[1]." << endl; return false; }
	if(lst2[2]!="99") { cout << "string After erase lst2[2]." << endl; return false; }
	if(lst2[3]!="8") { cout << "string After erase lst2[3]." << endl; return false; }
	if(lst2[4]!="9") { cout << "string After erase lst2[4]." << endl; return false; }
	lst2.insert(lst1.begin()++++++,"98");
	if(lst2[0]!="5") { cout << "string After insert lst2[0]." << endl; return false; }
	if(lst2[1]!="6") { cout << "string After insert lst2[1]." << endl; return false; }
	if(lst2[2]!="99") { cout << "string After insert lst2[2]." << endl; return false; }
	if(lst2[3]!="98") { cout << "string After insert lst2[3]." << endl; return false; }
	if(lst2[4]!="8") { cout << "string After insert lst2[4]." << endl; return false; }
	if(lst2[5]!="9") { cout << "string After insert lst2[5]." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=5) { cout << "string bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=4) { cout << "string bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=3) { cout << "string bad size after pop_back." << endl; return false; }
	if(lst2[0]!="5") { cout << "string After pop_back lst2[0]." << endl; return false; }
	if(lst2[1]!="6") { cout << "string After pop_back lst2[1]." << endl; return false; }
	if(lst2[2]!="99") { cout << "string After pop_back lst2[2]." << endl; return false; }
	return true;
}

int main(int argc,char **argv) {
	ofstream out("time.txt");
	std::srand(42);

	LinkedList<int> ll1;
	if(!simpleTest(ll1)) return 2;
	if(!passByValue(ll1)) {
		cout << "Failed LinkedList pass-by-value." << endl;
		return 2;
	}
	LinkedList<int> ll2 = returnLittleLL();
	if(ll2[0]!=1 || ll2[1]!=2 || ll2[2]!=3) {
		cout << "Failed return by value LinkedList." << endl;
		return 2;
	}
	ll1 = returnLittleLL();
	if(ll1[0]!=1 || ll1[1]!=2 || ll1[2]!=3) {
		cout << "Failed return by value-assign LinkedList." << endl;
		return 2;
	}

	LinkedList<string> llstr;
	stringTest(llstr);

	long long n = 50000;
	long long ans1 = n*(n-1)/2;

	cout << "Starting timing." << endl;
	double start = clock();

	LinkedList<int> ll3;
	list<int> v3;
	for(int i=0; i<n; ++i) {
		ll3.push_back(i);
		v3.push_back(i);
	}
	long long sum = 0;
	long long sum2 = 0;
	for(auto i:ll3) sum += i;
	for(auto i:v3) sum2 += i;
	if(sum!=ans1) {
		cout << "Failed LL big 1." << endl;
		return 2;
	}
	cout << "Passed big 1 set." << endl;
	auto vi = ++(v3.begin());
	for(auto i = ++(ll3.begin()); i!=ll3.end(); ) {
		i = ll3.erase(i);
		vi = v3.erase(vi);
		if(i!=ll3.end()) {
			++i;
			++vi;
		}
	}
	sum = 0;
	sum2 = 0;
	for(auto i:ll3) sum += i;
	for(auto i:v3) sum2 += i;
	if(sum!=sum2) {
		cout << "Failed LL big 2." << endl;
		return 2;
	}
	cout << "Passed big 2 set." << endl;

	for(int i=0; i<10000000; ++i) {
		int tmp = rand()%100;
		v3.push_back(tmp);
		ll3.push_back(tmp);
	}
	LinkedList<int> ll4 = add3AndReturn(ll3);
	long long sum1 = 0;
	sum2 = 0;
	for(auto i:v3) sum1 += i;
	for(auto i:ll4) sum2 += i;
	if(sum1+24!=sum2) {
		cout << sum1 << " " << sum2 << "\n";
		cout << "Failed big test 3." << endl;
		return 2;
	}

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;

	cout << "Tests passed." << endl;
	return 0;
}
