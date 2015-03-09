#include <string>
#include <iostream>
#include <algorithm>  
#include <fstream>
#include <vector>
#include <iterator>
#include <list>
#include <map>

#include "T9MappingEntry.h"
#include "T9Converter.h"

using namespace std;

static map<string, string>  WordDictionary;


map<string, string> getWordsFromDictionaryFile(){
	ifstream fin;
	string fileName = "de_neu.dic";
	fin.open(fileName);
	if (fin.fail()) { // same as operator!() tests both failbit and badbit
		cerr << "file " << fileName << " not found" << endl;
		exit(-2);
	}
	map<string, string>  words;
	ifstream input("de_neu.dic");
	for (string line; getline(input, line);){
		if (line.find("%") != 0)
			words[line] = line;
	}

	cout << "Read " << words.size() << " values";
	return words;
}
map<int, map<string, string>> getSetWithLengthForWords(map<string, string> words){
	map<int, map<string, string>> lengthWorList;
	int length = 0;
	for_each(words.begin(), words.end(), [&](const pair<string, string> word){
		lengthWorList[word.second.size()].insert(make_pair(word.first, word.second));
	});
	return lengthWorList;
}


vector<T9MappingEntry> initializeT9Wordbook(){
	vector<T9MappingEntry> t9WorkBook;
	t9WorkBook.push_back(*new T9MappingEntry("abc", 2));
	t9WorkBook.push_back(*new T9MappingEntry("def", 3));
	t9WorkBook.push_back(*new T9MappingEntry("ghi", 4));
	t9WorkBook.push_back(*new T9MappingEntry("jkl", 5));
	t9WorkBook.push_back(*new T9MappingEntry("mno", 6));
	t9WorkBook.push_back(*new T9MappingEntry("pqrs", 7));
	t9WorkBook.push_back(*new T9MappingEntry("tuv", 8));
	t9WorkBook.push_back(*new T9MappingEntry("wxyz", 9));
	//ostream_iterator<T9MappingEntry> out_it(cout, "\n");
	//copy(t9WorkBook.begin(), t9WorkBook.end(), out_it);
	return t9WorkBook;
}

int main(int argc, char *argv[]) {
	WordDictionary = getWordsFromDictionaryFile();
	T9Converter converter(initializeT9Wordbook());
	string result = converter.Word2number("kiss");
	cout << "The Result for kiss is : " << result << endl;

	auto resultNumber2Strings = converter.Number2strings("5477");
	cout << "The Result for number2strings is : " << resultNumber2Strings.size() << endl;

	auto resultNumber2Strings2 = converter.Number2Words("5477", WordDictionary);
	cout << "The amount of Results for number2strings2 is : " << resultNumber2Strings2.size() << endl;
	for_each(resultNumber2Strings2.begin(), resultNumber2Strings2.end(), [&](const string entry){
		cout << entry << endl;
	});

	auto resultNumber2Strings3 = converter.Number2WordsByLength("5477", getSetWithLengthForWords(WordDictionary));
	cout << "The amount of Results for number2strings3 is : " << resultNumber2Strings3.size() << endl;
	for_each(resultNumber2Strings3.begin(), resultNumber2Strings3.end(), [&](const string entry){
		cout << entry << endl;
	});
	cin;
	return 0;
}