#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include "hashtable.hpp"

using namespace std;

void CheckEqualAssertion(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	hashtable<int, hash<int>, equal_to<int>> h2(100, hash<int>(), equal_to<int>());
	for (int i = 0; i < 10; i++){
		h.insert(i);
		h2.insert(i);
	}
	cout << "Lists are the same: " << (h == h2) << endl;
	cout << h << endl;
	auto it = h.end(); 
	do{
		--it;
		cout << (*it) << endl;
	} while (it != h.begin());
}

int main(int argc, char** argv) {
	cout << "Starte program " << endl;
	CheckEqualAssertion();

	return 0;
}