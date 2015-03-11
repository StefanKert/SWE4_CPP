#ifndef Utility_H
#define Utility_H

#include <string>
#include <vector>
#include <functional>

using namespace std;

string StringToUpper(const string & value);
void ReadAllLinesFromFile(const string fileName, function<void(const string&)> continueWith);

#endif 
