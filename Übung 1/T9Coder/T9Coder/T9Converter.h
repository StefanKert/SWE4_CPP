#ifndef T9Converter_H
#define T9Converter_H


#include "T9MappingEntry.h"
#include <iomanip>
#include <ostream>
#include <iterator>
#include <iostream>
#include <map>
#include <hash_map>

using namespace std;

class T9Converter {
private: 
	vector<T9MappingEntry> _t9MappingEntries;
public:
	T9Converter();
	~T9Converter();

	void InitializeT9Wordbook();
	string Word2number(string word);
	bool IsNumberValid(string digits);
	vector<string> TestMethod(vector<string> alreadyInsertedEntries, T9MappingEntry entry);
	vector<string> Number2strings(string digits);
	vector<string> Number2Words(string digits, map<string, string> & wordDictionary);
	vector<string> Number2WordsByLength(string digits, map<int, map<string, string>> & wordDictionary);
	vector<string> T9Converter::NumberPrefix2Word(string digits, map<string, string> & wordDictionary);
	vector<string> T9Converter::Number2WordsWithHashMap(string digits, hash_map<string, string> & wordDictionary);
};

#endif

