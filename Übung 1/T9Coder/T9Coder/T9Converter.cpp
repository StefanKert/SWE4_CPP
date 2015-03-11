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
	for (auto character : word){
		for (auto entry : wordBook){
			if (entry.IsCharAvailableInMappingEntry(character)){
				retValue += entry.GetMappingDigit();
			}
		}
	}
	return retValue;
}

vector<string> T9Converter::TestMethod(vector<string> alreadyInsertedEntries, T9MappingEntry entry) {
	vector<string> entries;
	string mappingChars = entry.GetMappingChars();
	if (alreadyInsertedEntries.empty()) {
		for (auto character : mappingChars) {
			// Workaround because casting from single char to string is not that easy
			string s;
			s.push_back(character);
			entries.push_back(s);
		}
	}
	else{
		for (auto value : mappingChars) {
			for (auto entry : alreadyInsertedEntries) {
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
	for (auto entry : allPossibleEntries){
		if (wordDictionary[StringToUpper(entry)] != ""){
			entries.push_back(wordDictionary[StringToUpper(entry)]);
		}
	}
	return entries;
}

vector<string> T9Converter::Number2WordsByLength(string digits, map<int, map<string, string>> & wordDictionary){
	return this->Number2Words(digits, wordDictionary[digits.size()]);
}

vector<string> T9Converter::NumberPrefix2Word(string digits, map<string, string> & wordDictionary){
	vector<string> entries;
	auto allPossibleEntries = this->Number2strings(digits);
	for (auto entry : allPossibleEntries){
		for (auto pair : wordDictionary){
			if (pair.first.substr(0, entry.size()) == StringToUpper(entry)){
				if (pair.second != ""){
					entries.push_back(pair.second);
				}
			}
		}
	}
 	return entries;
}