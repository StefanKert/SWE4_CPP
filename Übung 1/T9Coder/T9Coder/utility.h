#ifndef Utility_H
#define Utility_H

#include <string.h>
#include <vector>
#include <functional>

using namespace std;

string StringToUpper(const string & value);
void ReadAllLinesFromFile(const string fileName, function<void(const string&)> continueWith);
void ReadAllWordsFromFile(const string fileName, function<void(const string&)> continueWith);
string IncrementString(const string& str);

struct IgnoreCaseCmp{
    bool operator() (const string& x, const string& y) const{
        return strcasecmp(x.c_str(), y.c_str()) < 0;
    }
};

#endif
