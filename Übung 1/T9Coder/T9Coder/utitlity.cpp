#include "utility.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>

using namespace std;

string StringToUpper(const string & value){
	auto result = value;
	transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}

void ReadAllLinesFromFile(const string fileName, function<void(const string&)> continueWith){
	ifstream fin;
	fin.open(fileName);
	if (fin.fail()) { // same as operator!() tests both failbit and badbit
		cerr << "file " << fileName << " not found" << endl;
		exit(-2);
	}
	ifstream input(fileName);
	string line;
	while (getline(input, line)){
		continueWith(line);
	}
}

void ReadAllWordsFromFile(const string fileName, function<void(const string&)> continueWith){
	ifstream fin;
	fin.open(fileName);
	if (fin.fail()) { // same as operator!() tests both failbit and badbit
		cerr << "file " << fileName << " not found" << endl;
		exit(-2);
	}
	ifstream input(fileName);
	string word;
	while (input >> word){
		continueWith(word);
	}
}

string IncrementString(const string& str) {
    int length = str.length();
    char c = str[length - 1];
    if (c == 'z')
        return length > 1 ? IncrementString(str.substr(0, length - 1)) + 'a' : "aa";
    return str.substr(0, length - 1) + ++c;
}
