#ifndef T9MappingEntry_H
#define T9MappingEntry_H

#include <string>
#include <set>
#include <ostream>
#include <vector>

using namespace std;

class T9MappingEntry {
private:
	int mappingDigit;
	set<string> mappingChars;
public:
	T9MappingEntry(set<string> word, int digitToMap);
	virtual ~T9MappingEntry();
	bool IsCharAvailableInMappingEntry(char charToCheck);
	string GetMappingDigit();
	set<string> GetMappingChars();
};

#endif
