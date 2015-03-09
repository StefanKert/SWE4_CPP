#include "T9MappingEntry.h"

#include <iomanip>
#include <ostream>
#include <iterator>
#include <iostream>

using namespace std;

T9MappingEntry::T9MappingEntry(string charsToMap, int digitToMap) : mappingChars(charsToMap), mappingDigit(digitToMap){}

T9MappingEntry::~T9MappingEntry() {}

bool T9MappingEntry::IsCharAvailableInMappingEntry(char charToCheck){
	return this->mappingChars.find(charToCheck) != string::npos;
}
string T9MappingEntry::GetMappingDigit(){
	return to_string(this->mappingDigit);
}
string T9MappingEntry::GetMappingChars(){
	return this->mappingChars;
}
ostream & operator << (ostream &os, const T9MappingEntry &e) {
	os << setw(15) << "Digit: " << e.mappingDigit << " for Chars: " << e.mappingChars << endl;
	return os;
}
