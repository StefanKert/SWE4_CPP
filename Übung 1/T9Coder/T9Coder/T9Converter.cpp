#include <vector>
#include <string>
#include <iostream>
#include <algorithm>  
#include <vector>
#include <iterator>
#include <map>
#include "T9Converter.h"
#include "T9MappingEntry.h"
#include "utility.h"

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
		for (auto value : mappingChars)
		{
			for (auto entry : alreadyInsertedEntries){
				entries.push_back(entry + value);
			}
		}
	}
	return entries;
}

vector<string> T9Converter::Number2strings(string digits){
	vector<string> entries;
	auto wordBook = this->_t9MappingEntries;
	for (auto digitChar : digits){
		auto foundEntry = find_if(wordBook.begin(), wordBook.end(), [&](T9MappingEntry &entry){
			return entry.GetMappingDigit()[0] == digitChar;
		});
		if (wordBook.end() == foundEntry){
			throw "No entry found for " + digits;
		}
		else{
			entries = this->TestMethod(entries, *foundEntry);
		}
	}
	return entries;
}

vector<string> T9Converter::Number2Words(string digits, map<string, string> & wordDictionary){
	vector<string> entries;
	auto allPossibleEntries = this->Number2strings(digits);
	for_each(allPossibleEntries.begin(), allPossibleEntries.end(), [&](const string entry){
		if (wordDictionary[StringToUpper(entry)] != ""){
			entries.push_back(wordDictionary[entry]);
		}
	});
	return entries;
}

vector<string> T9Converter::Number2WordsByLength(string digits, map<int, map<string, string>> & wordDictionary){
	return this->Number2Words(digits, wordDictionary[digits.size()]);
}

vector<string> T9Converter::NumberPrefix2Word(string digits, map<string, string> & wordDictionary){
	vector<string> entries;
	auto allPossibleEntries = this->Number2strings(digits);
	for_each(allPossibleEntries.begin(), allPossibleEntries.end(), [&](const string entry){
		for_each(wordDictionary.begin(), wordDictionary.end(), [&](const pair<string, string> pair){
			if (pair.first.substr(0, entry.size()) == StringToUpper(entry)){
				if (pair.second != ""){
					entries.push_back(pair.second);
				}
			}
		});
	});
 	return entries;
}

vector<string> T9Converter::NumberPrefix2WordTest(string digits, map<string, map<string, string>> & wordDictionary){
	vector<string> entries;
	auto allPossibleEntries = this->Number2strings(digits);
	for (auto entry : allPossibleEntries){
		auto test = lower_bound(wordDictionary.begin(), wordDictionary.end(), digits);
	}
	for_each(allPossibleEntries.begin(), allPossibleEntries.end(), [&](const string entry){
		for_each(wordDictionary.begin(), wordDictionary.end(), [&](const pair<string, string> pair){
			if (pair.first.substr(0, entry.size()) == StringToUpper(entry)){
				if (pair.second != ""){
					entries.push_back(pair.second);
				}
			}
		});
	});
	return entries;
}