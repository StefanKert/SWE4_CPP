#ifndef T9Converter_H
#define T9Converter_H


#include "T9MappingEntry.h"
#include <iomanip>
#include <ostream>
#include <iterator>
#include <iostream>
#include <map>

using namespace std;

class T9Converter {
private: 
	vector<T9MappingEntry> _t9MappingEntries;
public:
	T9Converter();
	~T9Converter();

	void InitializeT9Wordbook();
	string Word2Number(string word);
	set<string> GetPossibleStringsForDigit(char digit);
	bool IsNumberValid(const string& number);
	vector<string> TestMethod(vector<string> alreadyInsertedEntries, T9MappingEntry entry);
	set<string> Number2Strings(const string& number);
	vector<string> Number2Words(const string& number, map<string, string> & wordDictionary);
	vector<string> Number2WordsByLength(const string& number, map<int, map<string, string>> & wordDictionary);
	vector<string> T9Converter::NumberPrefix2Word(const string& number, map<string, string> & wordDictionary);
};

#endif

