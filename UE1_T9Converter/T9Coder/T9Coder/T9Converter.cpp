#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <strings.h>

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

set<string> T9Converter::GetPossibleStringsForDigit(const char& digit){
    for(auto entry : _t9MappingEntries){
        if(entry.GetMappingDigit()[0] == digit){
            return entry.GetMappingChars();
        }
    }
    // If no value was found an exception should indicate that a wrong digit was given.
    throw "No entry found for " + digit;
}

bool T9Converter::IsNumberValid(const string& number){
	if(number.empty()){
        return false;
    }
	auto wordBook = this->_t9MappingEntries;
	for (auto digitChar : number){
		auto foundEntry = find_if(wordBook.begin(), wordBook.end(), [&](T9MappingEntry &entry){
			return entry.GetMappingDigit()[0] == digitChar;
		});
		if (wordBook.end() == foundEntry){ // If this condition is true no entry was found so the number is invalid
			return false;
		}
	}
	return true;
}

bool T9Converter::IsWordValid(const string& word){
	if(word.empty()){
        return false;
    }
    for (auto character : word){
        auto foundEntry = find_if(this->_t9MappingEntries.begin(), this->_t9MappingEntries.end(), [&](T9MappingEntry &entry){
			return entry.IsCharAvailableInMappingEntry(character);
		});
		if (this->_t9MappingEntries.end() == foundEntry){ // If this condition is true no entry was found so the word is invalid
			return false;
		}
	}
	return true;
}

string T9Converter::Word2Number(const string& word){
	string retValue = "";
	if(!this->IsWordValid(word)){
        throw invalid_argument("The parameter word was empty or invalid char was given. Param: " + word);
	}
	for (auto character : word){
		for (auto entry : this->_t9MappingEntries){
			if (entry.IsCharAvailableInMappingEntry(character)){
				retValue += entry.GetMappingDigit(); // If character is available in mapping append to returnValue
			}
		}
	}
	return retValue;
}

set<string> T9Converter::Number2Strings(const string& number){
    if(!IsNumberValid(number)){
        throw invalid_argument("The parameter number is empty or contains a invalid digit. Only from 2-9 allowed.");
    }
	if (number.length() != 1){  // If the numbers length is >1 continue recursive call
        set<string> entries;
        set<string> allChars = Number2Strings(number.substr(1));
        set<string> possibleEntries = GetPossibleStringsForDigit(number[0]);

        for (auto subChar : allChars){
            for (auto entry : possibleEntries){
                entries.insert(entry + subChar); // Insert all values to the result
            }
        }
		return entries;
	}
	else { // If only one digit is left return values for this digit
        return GetPossibleStringsForDigit(number[0]);
	}
}

vector<string> T9Converter::Number2Words(const string& number, map<string, string> & wordDictionary){
    if(!IsNumberValid(number)){
        throw invalid_argument("The parameter number is empty or contains a invalid digit. Only from 2-9 allowed.");
    }
	vector<string> entries;
	auto allPossibleEntries = this->Number2Strings(number); //Load all possible combinations for given number
	for (auto entry : allPossibleEntries){
		if (wordDictionary[StringToUpper(entry)] != ""){
			entries.push_back(wordDictionary[StringToUpper(entry)]); //If value exists in dictionary append value to result vector
		}
	}
	return entries;
}

vector<string> T9Converter::Number2WordsByLength(const string& number, map<int, map<string, string>> & wordDictionary){
	return this->Number2Words(number, wordDictionary[number.length()]); // Just call Number2Words with de map entry that contains values with the same length
}

vector<string> T9Converter::NumberPrefix2Word(const string& number, set<string> & wordDictionary){
    if(!IsNumberValid(number)){
        throw invalid_argument("The parameter number is empty or contains a invalid digit. Only from 2-9 allowed.");
    }
	vector<string> entries;
	auto allPossibleEntries = this->Number2Strings(number); //Load all possible combinations for given number
	for (auto entry : allPossibleEntries){
        auto iteratorEntry = wordDictionary.lower_bound(entry); // Select first value where prefix occurs
        if(!HasGivenStringDifferentCharsThanZ(entry)){
            while(iteratorEntry != wordDictionary.end()){ // If the entry just consists of 'z' than we can iterate to the end because z is always the last leaf of the tree
                entries.push_back(*iteratorEntry);
                ++iteratorEntry;
            }
        }
        else{
            while(iteratorEntry != wordDictionary.lower_bound(IncrementString(entry))){ // If the entry doesn't only consist of 'z' we iterate to lower_bound entry of the incrementedstring
                 entries.push_back(*iteratorEntry);
                 ++iteratorEntry;
            }
        }
	}
 	return entries;
}

vector<string> T9Converter::NumberPrefix2SortedWords(const string& number, set<string> & wordDictionary, map<string,int, IgnoreCaseCmp> & wordDictionaryWithCount){
	vector<string> entries = this->NumberPrefix2Word(number, wordDictionary); // Get all entries for prefix
	sort(entries.begin(), entries.end(), [&wordDictionaryWithCount](const string& a, const string& b) -> bool {
        return wordDictionaryWithCount[a] > wordDictionaryWithCount[b]; // The sortfunction checks which count is higher
    });// The sort function orders the elements depending on there count of occurences
    return entries;
}
