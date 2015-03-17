#ifndef Tests_H
#define Tests_H

#include <iomanip>
#include <ostream>
#include <iterator>
#include <iostream>
#include <map>
#include <set>

#include "utility.h"
#include "T9Converter.h"

using namespace std;

class Tests {
private:
	set<string> _setWordDictionary;
    map<string, string>  _wordDictionary;
    map<int, map<string, string>> _wordWithLengthDictionary;
    map<string, int, IgnoreCaseCmp> _wordWithCountDictionary;
    T9Converter _converter;
public:
	Tests(T9Converter &converter, set<string> &setWordDictionary, map<string, string>  &wordDictionary, map<int, map<string, string>> &wordWithLengthDictionary, map<string, int, IgnoreCaseCmp> &wordWithCountDictionary);
	~Tests();

	void TestWord2Number(string test);
    void TestNumber2Strings(string test);
    void TestNumber2Words(string test);
    void TestNumber2WordsByLength(string test);
    void TestNumberPrefix2Word(string test);
    void TestNumberPrefix2SortedWords(string test);
    void TestAll();
};

#endif

