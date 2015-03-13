#include "T9MappingEntry.h"

#include <iomanip>
#include <ostream>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

T9MappingEntry::T9MappingEntry(set<string> charsToMap, int digitToMap) : mappingChars(charsToMap), mappingDigit(digitToMap){}

T9MappingEntry::~T9MappingEntry() {}

bool T9MappingEntry::IsCharAvailableInMappingEntry(char charToCheck){
	return find_if(this->mappingChars.begin(), this->mappingChars.end(), [&](string mappingChar){
		return mappingChar[0] == tolower(charToCheck);
	}) != this->mappingChars.end();
}
string T9MappingEntry::GetMappingDigit(){
	return to_string(this->mappingDigit);
}
set<string> T9MappingEntry::GetMappingChars(){
	return this->mappingChars;
}