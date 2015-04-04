#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "hashtable.hpp"

using namespace std;

void CheckIntInsert(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	for (int i = 0; i < 5; i++){
		h.insert(i);
		cout << "Int List contains element " << i << ": " << (h.contains(i) ? "true" : "false") << endl;
	}
	cout << "Expected Size 5 || Actual Size " << h.size() << endl;
	cout << "Expected Capacity 10 || Actual Capacity " << h.capacity() << endl;
}
void CheckStringInsert(){
	hashtable<string, hash<string>, equal_to<string>> h(5, hash<string>(), equal_to<string>());
	for (int i = 0; i < 5; i++){
		h.insert(to_string(i));
		cout << "String List contains element '" << i << "': " << (h.contains(to_string(i)) ? "true" : "false") << endl;
	}
	cout << "Expected Size 5 || Actual Size " << h.size() << endl;
	cout << "Expected Capacity 10 || Actual Capacity " << h.capacity() << endl;
}

void CheckEraseInt(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	for (int i = 0; i < 10; i++){
		h.insert(i);
	}
	cout << "Int List contains Value 5 before erase: " << (h.contains(5) ? "true" : "false") << endl;
	h.erase(5);
	cout << "Int List contains Value 5 after erase: " << (h.contains(5) ? "true" : "false") << endl;
}
void CheckEraseString(){
	hashtable<string, hash<string>, equal_to<string>> h(5, hash<string>(), equal_to<string>());
	for (int i = 0; i < 10; i++){
		h.insert(to_string(i));
	}
	cout << "String List contains Value '5' before erase: " << (h.contains(to_string(5)) ? "true" : "false") << endl;
	h.erase(to_string(5));
	cout << "String List contains Value '5' after erase: " << (h.contains(to_string(5)) ? "true" : "false") << endl;
}

void CheckIntOperatorEquals(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	hashtable<int, hash<int>, equal_to<int>> h2(100, hash<int>(), equal_to<int>());
	for (int i = 0; i < 10; i++){
		h.insert(i);
		h2.insert(i);
	}
	cout << "Int Lists are the same: " << (h == h2 ? "true" : "false") << endl;
}
void CheckStringOperatorEquals(){
	hashtable<string, hash<string>, equal_to<string>> h(5, hash<string>(), equal_to<string>());
	hashtable<string, hash<string>, equal_to<string>> h2(100, hash<string>(), equal_to<string>());
	for (int i = 0; i < 10; i++){
		h.insert(to_string(i));
		h2.insert(to_string(i));
	}
	cout << "String Lists are the same: " << (h == h2 ? "true" : "false") << endl;
}

void CheckPrintIntListWithOverloadedOperator(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	for (int i = 0; i < 10; i++){
		h.insert(i);
	}
	cout << h << endl;
}
void CheckPrintStringListWithOverloadedOperator(){
	hashtable<string, hash<string>, equal_to<string>> h(5, hash<string>(), equal_to<string>());
	for (int i = 0; i < 10; i++){
		h.insert(to_string(i));
	}
	cout << h << endl;
}

void PrintListNormalAndReverseOrder(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	for (int i = 0; i < 10; i++){
		h.insert(i);
	}
	auto it = h.begin();
	cout << "Normal order: " << endl;
	while (it != h.end()){
		cout << (*it) << endl;
		it++;
	}

	cout << "Reverse order: " << endl;
	auto reverseIt = h.end();
	do{
		--reverseIt;
		cout << (*reverseIt) << endl;
	} while (reverseIt != h.begin());
}

void PrintListWithForeachWithSTL(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	for (int i = 0; i < 10; i++){
		h.insert(i);
	}
	for_each(h.begin(), h.end(), [](const int& element){
		cout << element << endl;
	});
}
void FindElementWithSTL(){
	hashtable<int, hash<int>, equal_to<int>> h(5, hash<int>(), equal_to<int>());
	for (int i = 0; i < 10; i++){
		h.insert(i);
	}
	auto foundIt = find(h.begin(), h.end(), 5);
	cout << "Should find element '5': Found " << (foundIt != h.end() ? "true" : "false") << endl;
	auto foundItNot = find(h.begin(), h.end(), 15);
	cout << "Should not find element '15': Found " << (foundItNot != h.end() ? "true" : "false") << endl;
}

int main(int argc, char** argv) {
	cout << "CheckIntInsert" << endl;
	CheckIntInsert();
	cout << endl;
	cout << "CheckStringInsert" << endl;
	CheckStringInsert();
	cout << endl;
	cout << "CheckIntOperatorEquals" << endl;
	CheckIntOperatorEquals();
	cout << endl;
	cout << "CheckStringOperatorEquals" << endl;
	CheckStringOperatorEquals();
	cout << endl;
	cout << "CheckEraseInt" << endl;
	CheckEraseInt();
	cout << endl;
	cout << "CheckEraseString" << endl;
	CheckEraseString();
	cout << endl;
	cout << "CheckPrintIntListWithOverloadedOperator" << endl;
	CheckPrintIntListWithOverloadedOperator();
	cout << endl;
	cout << "CheckPrintStringListWithOverloadedOperator" << endl;
	CheckPrintStringListWithOverloadedOperator();
	cout << "PrintListNormalAndReverseOrder" << endl;
	cout << endl;
	PrintListNormalAndReverseOrder();
	cout << endl;
	cout << "PrintListWithForeachWithSTL" << endl;
	PrintListWithForeachWithSTL();
	cout << endl;
	cout << "FindElementWithSTL" << endl;
	FindElementWithSTL();
	cout << endl;
	return 0;
}
