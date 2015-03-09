#include <vector>
#include <string>
#include <iostream>
#include <algorithm>  
#include <fstream>
#include <vector>
#include <iterator>
#include <list>
#include <map>
#include "T9Converter.h"
#include "T9MappingEntry.h"

T9Converter::T9Converter(vector<T9MappingEntry> t9MappingEntries) : _t9MappingEntries(t9MappingEntries) {}

T9Converter::~T9Converter(){}

string T9Converter::Word2number(string word){
	string retValue = "";
	auto wordBook = this->_t9MappingEntries;
	for_each(word.begin(), word.end(), [&](const char c) {
		for_each(wordBook.begin(), wordBook.end(), [&](T9MappingEntry entry){
			if (entry.IsCharAvailableInMappingEntry(c)){
				retValue += entry.GetMappingDigit();
			}
		});
	});
	return retValue;
}

vector<string> T9Converter::TestMethod(vector<string> alreadyInsertedEntries, T9MappingEntry entry){
	vector<string> entries;
	string mappingChars = entry.GetMappingChars();
	if (alreadyInsertedEntries.empty()){
		for_each(mappingChars.begin(), mappingChars.end(), [&](const char character){
			entries.push_back(string(&character));
		});
	}
	else{
		for (auto iterator = mappingChars.begin(); iterator != mappingChars.end(); iterator++){
			for (auto listIterator = alreadyInsertedEntries.begin(); listIterator != alreadyInsertedEntries.end(); listIterator++){
				entries.push_back(*listIterator + *iterator);
			}
		}
	}
	return entries;
}

vector<string> T9Converter::Number2strings(string digits){
	vector<string> entries;
	auto wordBook = this->_t9MappingEntries;
	for_each(digits.begin(), digits.end(), [&](const char character){
		auto foundEntry = find_if(wordBook.begin(), wordBook.end(), [&](T9MappingEntry &entry){
			return entry.GetMappingDigit()[0] == character;
		});
		if (wordBook.end() == foundEntry){
			throw "No entry found for " + digits;
		}
		else{
			entries = this->TestMethod(entries, *foundEntry);
		}
	});
	return entries;
}

vector<string> T9Converter::Number2Words(string digits, map<string, string> & wordDictionary){
	vector<string> entries;
	vector<string> allPossibleEntries;
	int loops = 0;
	allPossibleEntries = this->Number2strings(digits);
	for_each(allPossibleEntries.begin(), allPossibleEntries.end(), [&](const string entry){
		if (wordDictionary[entry] != ""){
			entries.push_back(wordDictionary[entry]);
		}
	});
	return entries;
}

vector<string> T9Converter::Number2WordsByLength(string digits, map<int, map<string, string>> & wordDictionary){
	auto dict = wordDictionary[digits.size()];
	auto result = this->Number2Words(digits, dict);
	return result;
}