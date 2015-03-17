#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <sstream>

#include "tests.h"
#include "utility.h"

Tests::Tests(T9Converter &converter, set<string> &setWordDictionary, map<string, string>  &wordDictionary, map<int, map<string, string>> &wordWithLengthDictionary, map<string, int, IgnoreCaseCmp> &wordWithCountDictionary) :
                _converter(converter), _setWordDictionary(setWordDictionary), _wordDictionary(wordDictionary), _wordWithLengthDictionary(wordWithLengthDictionary), _wordWithCountDictionary(wordWithCountDictionary) {}

Tests::~Tests(){}

void Tests::TestWord2Number(string test){
    if(strcmp(test.c_str(), "NoInput") == 0){
        try {
            cout << "Test: Word2Number-NoInput" << endl;
            cout << _converter.Word2Number("") << endl;
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "InvalidWord") == 0){
        try {
            cout << "Test: Word2Number-InvalidWord" << endl;
            cout << _converter.Word2Number("&hae34djfl4@") << endl;
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "PrintResult") == 0){
        cout << "Test: Word2Number-PrintResult" << endl;
        cout << "Bier = " << _converter.Word2Number("Bier") << endl;
        cout << "Superman = " << _converter.Word2Number("Superman") << endl;
        cout << "Hausfrauenbingo = " << _converter.Word2Number("Hausfrauenbingo") << endl;
    }
    else if(strcmp(test.c_str(), "Kiss") == 0){
        cout << "Test: Word2Number-Kiss" << endl;
        cout << "kiss = " << _converter.Word2Number("kiss") << endl;
    }
}

void Tests::TestNumber2Strings(string test){
    if(strcmp(test.c_str(), "NoInput") == 0){
        try {
            cout << "Test: Number2Strings-NoInput" << endl;
            cout << _converter.Number2Strings("").size() << endl;
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "InvalidNumber") == 0){
        try {
            cout << "Test: Number2Strings-InvalidNumber" << endl;
            _converter.Number2Strings("10234");
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "ResultCount") == 0){
        cout << "Test: Number2Strings-ResultCount" << endl;
        cout << "Amount of Results for  '2345'= " << _converter.Number2Strings("2345").size()  << endl;
        cout << "Amount of Results for  '45374'= " << _converter.Number2Strings("45374").size()  << endl;
        cout << "Amount of Results for  '59483727'= " << _converter.Number2Strings("59483727").size()  << endl;
    }
    else if(strcmp(test.c_str(), "PrintResult") == 0){
        cout << "Test: Number2Strings-ResultCount" << endl;
        cout << "Results for '23':" << endl;
        auto result = _converter.Number2Strings("23");
        PrintResultsForT9ConverterResult(result);
    }
    else if(strcmp(test.c_str(), "5477") == 0){
        cout << "Test: Word2Number-5477" << endl;
        cout << "Results for '5477':" << endl;
        auto result = _converter.Number2Strings("5477");
        PrintResultsForT9ConverterResult(result);
    }
}

void Tests::TestNumber2Words(string test){
    if(strcmp(test.c_str(), "NoInput") == 0){
        try {
            cout << "Test: Number2Words-NoInput" << endl;
            cout << _converter.Number2Words("", _wordDictionary).size() << endl;
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "InvalidNumber") == 0){
        try {
            cout << "Test: Number2Words-InvalidNumber" << endl;
            _converter.Number2Words("10234", _wordDictionary);
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "ResultCount") == 0){
        cout << "Test: Number2Words-ResultCount" << endl;
        cout << "Amount of Results for  '2345'= " << _converter.Number2Words("2345", _wordDictionary).size()  << endl;
        cout << "Amount of Results for  '45374'= " << _converter.Number2Words("45374", _wordDictionary).size()  << endl;
        cout << "Amount of Results for  '59483727'= " << _converter.Number2Words("59483727", _wordDictionary).size()  << endl;
    }
    else if(strcmp(test.c_str(), "PrintResult") == 0){
        cout << "Test: Number2Words-PrintResult" << endl;
        cout << "Results for '23':" << endl;
        auto result = _converter.Number2Words("23", _wordDictionary);
        PrintResultsForT9ConverterResult(result);
    }
}

void Tests::TestNumber2WordsByLength(string test){
    if(strcmp(test.c_str(), "NoInput") == 0){
        try {
            cout << "Test: Number2WordsByLength-NoInput" << endl;
            cout << _converter.Number2WordsByLength("", _wordWithLengthDictionary).size() << endl;
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "InvalidNumber") == 0){
        try {
            cout << "Test: Number2WordsByLength-InvalidNumber" << endl;
            _converter.Number2WordsByLength("10234", _wordWithLengthDictionary);
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "ResultCount") == 0){
        cout << "Test: Number2WordsByLength-ResultCount" << endl;
        cout << "Amount of Results for  '2345'= " << _converter.Number2WordsByLength("2345", _wordWithLengthDictionary).size()  << endl;
        cout << "Amount of Results for  '45374'= " << _converter.Number2WordsByLength("45374", _wordWithLengthDictionary).size()  << endl;
        cout << "Amount of Results for  '59483727'= " << _converter.Number2WordsByLength("59483727", _wordWithLengthDictionary).size()  << endl;
    }
    else if(strcmp(test.c_str(), "PrintResult") == 0){
        cout << "Test: Number2WordsByLength-PrintResult" << endl;
        cout << "Results for '23':" << endl;
        auto result = _converter.Number2WordsByLength("23", _wordWithLengthDictionary);
        PrintResultsForT9ConverterResult(result);
    }
}

void Tests::TestNumberPrefix2Word(string test){
    if(strcmp(test.c_str(), "NoInput") == 0){
        try {
            cout << "Test: NumberPrefix2Word-NoInput" << endl;
            cout << _converter.NumberPrefix2Word("", _setWordDictionary).size() << endl;
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "InvalidNumber") == 0){
        try {
            cout << "Test: NumberPrefix2Word-InvalidNumber" << endl;
            _converter.NumberPrefix2Word("10234", _setWordDictionary);
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "ResultCount") == 0){
        cout << "Test: NumberPrefix2Word-ResultCount" << endl;
        cout << "Amount of Results for  '2345'= " << _converter.NumberPrefix2Word("2345", _setWordDictionary).size()  << endl;
        cout << "Amount of Results for  '45374'= " << _converter.NumberPrefix2Word("45374", _setWordDictionary).size()  << endl;
        cout << "Amount of Results for  '59483727'= " << _converter.NumberPrefix2Word("59483727", _setWordDictionary).size()  << endl;
    }
    else if(strcmp(test.c_str(), "PrintResult") == 0){
        cout << "Test: NumberPrefix2Word-PrintResult" << endl;
        cout << "Results for '4355':" << endl;
        auto result = _converter.NumberPrefix2Word("4355", _setWordDictionary);
        PrintResultsForT9ConverterResult(result);
    }
}

void Tests::TestNumberPrefix2SortedWords(string test){
    if(strcmp(test.c_str(), "NoInput") == 0){
        try {
            cout << "Test: NumberPrefix2SortedWords-NoInput" << endl;
            cout << _converter.NumberPrefix2SortedWords("", _setWordDictionary, _wordWithCountDictionary).size() << endl;
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "InvalidNumber") == 0){
        try {
            cout << "Test: NumberPrefix2SortedWords-InvalidNumber" << endl;
            _converter.NumberPrefix2SortedWords("10234", _setWordDictionary, _wordWithCountDictionary);
        } catch(const invalid_argument &ex){
            cerr << "Invalid Argument exception was caught. Exception text was: " << ex.what() << endl;
        }
    }
    else if(strcmp(test.c_str(), "ResultCount") == 0){
        cout << "Test: NumberPrefix2SortedWords-ResultCount" << endl;
        cout << "Amount of Results for  '2345'= " << _converter.NumberPrefix2SortedWords("2345", _setWordDictionary, _wordWithCountDictionary).size()  << endl;
        cout << "Amount of Results for  '45374'= " << _converter.NumberPrefix2SortedWords("45374", _setWordDictionary, _wordWithCountDictionary).size()  << endl;
        cout << "Amount of Results for  '59483727'= " << _converter.NumberPrefix2SortedWords("59483727", _setWordDictionary, _wordWithCountDictionary).size()  << endl;
    }
    else if(strcmp(test.c_str(), "PrintResult") == 0){
        cout << "Test: NumberPrefix2SortedWords-PrintResult" << endl;
        cout << "Results for '4355':" << endl;
        auto result = _converter.NumberPrefix2SortedWords("4355", _setWordDictionary, _wordWithCountDictionary);
        PrintResultsForT9ConverterResult(result);
    }
}

void Tests::TestAll(){
    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
    TestWord2Number("NoInput");
    cout << endl << endl;
    TestWord2Number("InvalidNumber");
    cout << endl << endl;
    TestWord2Number("PrintResult");
    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
    TestNumber2Strings("NoInput");
    cout << endl << endl;
    TestNumber2Strings("InvalidNumber");
    cout << endl << endl;
    TestNumber2Strings("ResultCount");
    cout << endl << endl;
    TestNumber2Strings("PrintResult");
    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
    TestNumber2Words("NoInput");
    cout << endl << endl;
    TestNumber2Words("InvalidNumber");
    cout << endl << endl;
    TestNumber2Words("ResultCount");
    cout << endl << endl;
    TestNumber2Words("PrintResult");
    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
    TestNumber2WordsByLength("NoInput");
    cout << endl << endl;
    TestNumber2WordsByLength("InvalidNumber");
    cout << endl << endl;
    TestNumber2WordsByLength("ResultCount");
    cout << endl << endl;
    TestNumber2WordsByLength("PrintResult");
    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
    TestNumberPrefix2Word("NoInput");
    cout << endl << endl;
    TestNumberPrefix2Word("InvalidNumber");
    cout << endl << endl;
    TestNumberPrefix2Word("ResultCount");
    cout << endl << endl;
    //TestNumberPrefix2Word("PrintResult");
    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
    TestNumberPrefix2SortedWords("NoInput");
    cout << endl << endl;
    TestNumberPrefix2SortedWords("InvalidNumber");
    cout << endl << endl;
    TestNumberPrefix2SortedWords("ResultCount");
    cout << endl << endl;
    //TestNumberPrefix2WordSortedWords("PrintResult");
    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
}
