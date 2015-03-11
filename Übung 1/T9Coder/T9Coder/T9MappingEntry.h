#ifndef T9MappingEntry_H
#define T9MappingEntry_H

#include <string>
#include <set>
#include <ostream>

using namespace std;

class T9MappingEntry {
private:
	int mappingDigit;
	string mappingChars;
public:
	T9MappingEntry(string word, int digitToMap);
	virtual ~T9MappingEntry();
	bool IsCharAvailableInMappingEntry(char charToCheck);
	string GetMappingDigit();
	string GetMappingChars();
	friend std::ostream & operator <<  (std::ostream &os, const T9MappingEntry &e);
};

#endif 
