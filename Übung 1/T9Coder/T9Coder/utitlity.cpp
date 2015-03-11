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

