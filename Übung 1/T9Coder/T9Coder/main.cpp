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
#include "utility.h"

using namespace std;

static map<string, string>  WordDictionary;
static map<int, map<string, string>> WordWithLengthDictionary;
static map<string, map<string, string>> WordWithT9CodeDictionary;


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
	return t9WorkBook;
}

void loadWordsFromDictionaryFile(){
	ReadAllLinesFromFile("de_neu.dic", [&](string line){
		if (line.find("%") != 0){
			WordDictionary[StringToUpper(line)] = line;
		}
	});
}
void loadSetWithLengthForWords(map<string, string> & words){
	int length = 0;
	for_each(words.begin(), words.end(), [&](const pair<string, string> word){
		WordWithLengthDictionary[word.second.size()].insert(make_pair(word.first, word.second));
	});
}
void loadMapWithT9CodeForWords(map<string, string> & words){
	int length = 0;
	T9Converter converter(initializeT9Wordbook());
	for_each(words.begin(), words.end(), [&](const pair<string, string> word){
		WordWithT9CodeDictionary[converter.Word2number(word.first)].insert(make_pair(word.first, word.second));
	});
}

void InitializeDictionaries(){
	cout << "Load dictionary from disk.... " << endl;
	loadWordsFromDictionaryFile();
	loadSetWithLengthForWords(WordDictionary);
	//loadMapWithT9CodeForWords(WordDictionary);
	cout << "Dictionary succesfully loaded. (" << WordDictionary.size() << " Entries) " << endl;
}

int main(int argc, char *argv[]) {
	InitializeDictionaries();
	T9Converter converter(initializeT9Wordbook());

	auto result = converter.Word2number("kiss");
	cout << "The Result for Word2number is : " << result << endl;

	auto resultNumber2Strings = converter.Number2strings("4355");
	cout << "The Result for Number2strings is : " << resultNumber2Strings.size() << endl;

	auto resultNumber2Words = converter.Number2Words("4355", WordDictionary);
	cout << "The amount of Results for Number2Words is : " << resultNumber2Words.size() << endl;
	for_each(resultNumber2Words.begin(), resultNumber2Words.end(), [&](const string entry){
		cout << entry << endl;
	});

	auto resultNumber2WordsByLength = converter.Number2WordsByLength("4355", WordWithLengthDictionary);
	cout << "The amount of Results for Number2WordsByLength is : " << resultNumber2WordsByLength.size() << endl;
	for_each(resultNumber2WordsByLength.begin(), resultNumber2WordsByLength.end(), [&](const string entry){
		cout << entry << endl;
	});

	auto resultNumberPrefix2Word = converter.NumberPrefix2Word("43", WordDictionary);
	cout << "The amount of Results for NumberPrefix2Word is : " << resultNumberPrefix2Word.size() << endl;
	for_each(resultNumberPrefix2Word.begin(), resultNumberPrefix2Word.end(), [&](const string entry){
		cout << entry << endl;
	});
	system("pause");
	return 0;
}