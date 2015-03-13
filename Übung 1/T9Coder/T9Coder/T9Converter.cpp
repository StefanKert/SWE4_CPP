#include <vector>
#include <string>
#include <iostream>
#include <algorithm>  
#include <vector>
#include <iterator>
#include <map>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include "T9Converter.h"
#include "T9MappingEntry.h"
#include "utility.h"

T9Converter::T9Converter() {
	this->InitializeT9Wordbook();
}
T9Converter::~T9Converter(){}

void T9Converter::InitializeT9Wordbook(){
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "a", "b", "c" }, 2));
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "d", "e", "f" }, 3));
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "g", "h", "i" }, 4));
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "j", "k", "l" }, 5));
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "m", "n", "o" }, 6));
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "p", "q", "r", "s" }, 7));
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "t", "u", "v" }, 8));
	this->_t9MappingEntries.push_back(*new T9MappingEntry({ "w", "x", "y", "z" }, 9));
}

set<string> T9Converter::GetPossibleStringsForDigit(char digit){
	auto foundEntry = find_if(this->_t9MappingEntries.begin(), this->_t9MappingEntries.end(), [&](T9MappingEntry &entry){
		return entry.GetMappingDigit()[0] == digit;
	});
	if (this->_t9MappingEntries.end() == foundEntry){
		throw "No entry found for " + digit;
	}
	else{
		return (*foundEntry).GetMappingChars();
	}
}

bool T9Converter::IsNumberValid(const string& number){
	auto wordBook = this->_t9MappingEntries;
	for (auto digitChar : number){
		auto foundEntry = find_if(wordBook.begin(), wordBook.end(), [&](T9MappingEntry &entry){
			return entry.GetMappingDigit()[0] == digitChar;
		});
		if (wordBook.end() == foundEntry){
			return false;
		}
	}
	return true;
}

string T9Converter::Word2Number(string word){
	string retValue = "";
	for (auto character : word){
		for (auto entry : this->_t9MappingEntries){
			if (entry.IsCharAvailableInMappingEntry(character)){
				retValue += entry.GetMappingDigit();
			}
		}
	}
	return retValue;
}

set<string> T9Converter::Number2Strings(const string& number){
	if (number.length() == 1){
		return GetPossibleStringsForDigit(number[0]);
	}
	set<string> entries;
	set<string> possibleEntries = GetPossibleStringsForDigit(number[0]);
	set<string> allChars = Number2Strings(number.substr(1));

	for (auto d : allChars){
		for (auto entry : possibleEntries){
			entries.insert(entry + d);
		}
	}
	return entries;
}

vector<string> T9Converter::Number2Words(const string& number, map<string, string> & wordDictionary){
	vector<string> entries;
	auto allPossibleEntries = this->Number2Strings(number);
	for (auto entry : allPossibleEntries){
		if (wordDictionary[StringToUpper(entry)] != ""){
			entries.push_back(wordDictionary[StringToUpper(entry)]);
		}
	}
	return entries;
}

vector<string> T9Converter::Number2WordsByLength(const string& number, map<int, map<string, string>> & wordDictionary){
	return this->Number2Words(number, wordDictionary[number.length()]);
}

vector<string> T9Converter::NumberPrefix2Word(const string& number, map<string, string> & wordDictionary){
	vector<string> entries;
	auto allPossibleEntries = this->Number2Strings(number);
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