#include "utility.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>

using namespace std;

string StringToUpper(const string &value){
	auto result = value;
	transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}

void openStream(const string &fileName, ifstream &fin) {
  fin.open(fileName);
  if (fin.fail()) {
    cerr << "file " << fileName << " not found" << endl;
    exit(-2);
  }
  // fin returned as reference argument
}

void ReadAllLinesFromFile(const string &fileName, function<void(const string&)> continueWith){
    ifstream input;
	openStream(fileName, input);
	string line;
	while (getline(input, line)){
		continueWith(line);
	}
}

void ReadAllWordsFromFile(const string &fileName, function<void(const string&)> continueWith){
    ifstream input;
	openStream(fileName, input);
	string word;
	while (input >> word){
		continueWith(word);
	}
}

string IncrementString(const string &str) {
    int lastElement = str.length() - 1;
    char lastChar = str[lastElement];
    if (lastChar == 'z')
        return IncrementString(str.substr(0, lastElement)); // If last character is 'z' increase the second last character
    return str.substr(0, lastElement) + ++lastChar; // If the last character is differnt than 'z' increase it and append it to the string
}

// This function checks if there are other chars than z in the string
bool HasGivenStringDifferentCharsThanZ(const string &str) {
    for(auto c : str){
        if(c != 'z'){
            return true;
        }
    }
    return false;
}

void PrintResultsForT9ConverterResult(set<string> &resultToPrint){
    for(auto entry : resultToPrint){
        cout << entry << endl;
    }
}

void PrintResultsForT9ConverterResult(vector<string> &resultToPrint){
    for(auto entry : resultToPrint){
        cout << entry << endl;
    }
}
