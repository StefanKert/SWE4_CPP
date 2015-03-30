#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>
#include "hashtable.hpp"

using namespace std;

int main(int argc, char** argv) {
	cout << "Starte program " << endl;
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	for (int i = 0; i < 1000; i++){
		h.insert(i);
	}
	h.insert(-5);
	cout << h.contains(2) << endl;
	cout << h.empty() << endl;
	cout << h.size() << endl;
	cout << h;
	return 0;
}