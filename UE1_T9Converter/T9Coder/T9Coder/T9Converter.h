#ifndef T9Converter_H
#define T9Converter_H


#include "T9MappingEntry.h"
#include "utility.h"
#include <iomanip>
#include <ostream>
#include <iterator>
#include <iostream>
#include <map>

using namespace std;

class T9Converter {
private:
	vector<T9MappingEntry> _t9MappingEntries;
    set<string> GetPossibleStringsForDigit(const char& digit);
public:
	T9Converter();
	~T9Converter();

	void InitializeT9Wordbook();
	string Word2Number(const string& word);
	bool IsNumberValid(const string& number);
	bool IsWordValid(const string& word);
	set<string> Number2Strings(const string& number);
	vector<string> Number2Words(const string& number, map<string, string> & wordDictionary);
	vector<string> Number2WordsByLength(const string& number, map<int, map<string, string>> & wordDictionary);
	vector<string> NumberPrefix2Word(const string& number, set<string> & wordDictionary);
	vector<string> NumberPrefix2SortedWords(const string& number, set<string> & wordDictionary, map<string,int, IgnoreCaseCmp> & wordDictionaryWithCount);
};

#endif

