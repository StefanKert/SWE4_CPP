#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <sstream>

#include "T9MappingEntry.h"
#include "T9Converter.h"
#include "utility.h"
#include "tests.h"

using namespace std;

static set<string> SetWordDictionary;
static map<string, string>  WordDictionary;
static map<int, map<string, string>> WordWithLengthDictionary;
static map<string, int, IgnoreCaseCmp> WordWithCountDictionary;
static T9Converter Converter;

void loadDictionaries(){
	ReadAllLinesFromFile("de_neu.dic", [&](const string &line){
		if (line.find("%") != 0){ // In our dictionary file we have some comments we need to get rid of them
			SetWordDictionary.insert(line); // Init set with line
			WordDictionary[StringToUpper(line)] = line; // Saving the current line to the Dictionary with the line in upper cases as key
			WordWithLengthDictionary[line.size()].insert(make_pair(StringToUpper(line), line)); // Saving the current line with the upper case key to the dictionary with the line length as key
			WordWithCountDictionary[line] = 0; // Init Dictionary with line
		}
	});
}
void loadCountOfWords(){
	ReadAllWordsFromFile("dasParfum.txt", [&](string word){
        if (WordWithCountDictionary.find(word) == WordWithCountDictionary.end()) {
            WordWithCountDictionary[word] = 1; // If element is not existing in the Dictionary init it with 1
        }
        else {
            WordWithCountDictionary[word] += 1; // If the element already exists increase the count with 1
        }
	});
}

//This function shows the menu where the user can select the action which should be performed
void StartProgrammWithMenu(){
	bool finished = false;
	int option = 0;

	 while (!finished){
            try{
                cout << "Geben Sie an welche der untenstehenden Optionen Sie ausfuehren wollen:" << endl;
                cout << "<1> Wort zu Nummer konvertieren. " << endl;
                cout << "<2> Nummer zu Zeichenfolge konvertieren. " << endl;
                cout << "<3> Nummer zu Woertern konvertieren. " << endl;
                cout << "<4> Nummer zu Woertern konvertieren (Länge). " << endl;
                cout << "<5> Nummernprefix zu Woertern. " << endl;
                cout << "<6> Nummernprefix zu Woertern nach Relevanz. " << endl;
                cout << "<7> Beenden. " << endl;
                cin >> option;
                if (option == 1){
                    cout << "Bitte geben Sie das gewuenschte Wort ein: " << endl;
                    string wordToConvert;
                    cin >> wordToConvert;
                    auto result = Converter.Word2Number(wordToConvert);
                    cout << "Word2Number: " << wordToConvert << " = " << result << endl;
                }
                else if (option == 2){
                    cout << "Bitte geben Sie die gewuenschte Nummer an: " << endl;
                    string numberToConvert = "";
                    cin >> numberToConvert;
                    if (!Converter.IsNumberValid(numberToConvert)){
                        cout << "Die angegebene Nummer war ungueltig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
                    }
                    else{
                        auto result = Converter.Number2Strings(numberToConvert);
                        cout << "Number2strings: " << numberToConvert << " = " << result.size() << endl;
                        PrintResultsForT9ConverterResult(result);
                    }
                }
                else if (option == 3){
                    cout << "Bitte geben Sie die gewuenschte Nummer an: " << endl;
                    string numberToConvert = "";
                    cin >> numberToConvert;
                    if (!Converter.IsNumberValid(numberToConvert)){
                        cout << "Die angegebene Nummer war ungueltig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
                    }
                    else{
                        auto result = Converter.Number2Words(numberToConvert, WordDictionary);
                        cout << "Number2Words: " << numberToConvert << " = " << result.size() << endl;
                        PrintResultsForT9ConverterResult(result);
                    }
                }
                else if (option == 4){
                    cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
                    string numberToConvert = "";
                    cin >> numberToConvert;
                    if (!Converter.IsNumberValid(numberToConvert)){
                        cout << "Die angegebene Nummer war ungueltig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
                    }
                    else{
                        auto result = Converter.Number2WordsByLength(numberToConvert, WordWithLengthDictionary);
                        cout << "Number2WordsByLength: " << numberToConvert << " = " << result.size() << endl;
                        PrintResultsForT9ConverterResult(result);
                    }
                }
                else if (option == 5){
                    cout << "Bitte geben Sie die gewuenschte Nummer an: " << endl;
                    string numberToConvert = "";
                    cin >> numberToConvert;
                    if (!Converter.IsNumberValid(numberToConvert)){
                        cout << "Die angegebene Nummer war ungueltig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
                    }
                    else{
                        auto result = Converter.NumberPrefix2Word(numberToConvert, SetWordDictionary);
                        cout << "NumberPrefix2Word: " << numberToConvert << " = " << result.size() << endl;
                        PrintResultsForT9ConverterResult(result);
                    }

                }
                else if (option == 6){
                    cout << "Bitte geben Sie die gewuenschte Nummer an: " << endl;
                    string numberToConvert = "";
                    cin >> numberToConvert;
                    if (!Converter.IsNumberValid(numberToConvert)){
                        cout << "Die angegebene Nummer war ungueltig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
                    }
                    else{
                        auto result = Converter.NumberPrefix2SortedWords(numberToConvert, SetWordDictionary, WordWithCountDictionary);
                        cout << "NumberPrefix2SortedWords: " << numberToConvert << " = " << result.size() << endl;
                        PrintResultsForT9ConverterResult(result);
                    }
                }
                else if (option == 7){
                    finished = true;
                }
                else{
                    cout << "Ungültige Nummer eingegeben." << endl;
                }
            }
            catch (bad_alloc &e){
                cout << e.what() << endl;
            }
            catch (...){ // Catch every exception block
                cout << "Ein schwerer Fehler ist aufgetreten der nicht erkannt werden konnte bitte starten Sie das Programm neu. " << endl;
            }
        }
}


/**
The Program can be started with the following Command Line Args
-- No Params
The startmenu is executed


-- This Command performs all available tests, but not the Print Result tests for Number2Words, NumberPrefix2Word and NumberPrefix2SortedWords
Test

-- This Commands Perform the tests for the function Word2Number
Test Word2Number NoInput
Test Word2Number InvalidNumber
Test Word2Number PrintResult

-- This Commands Perform the tests for the function Number2Strings
Test Number2Strings NoInput
Test Number2Strings InvalidNumber
Test Number2Strings ResultCount
Test Number2Strings PrintResult

-- This Commands Perform the tests for the function Number2Words
Test Number2Words NoInput
Test Number2Words InvalidNumber
Test Number2Words ResultCount
Test Number2Words PrintResult

-- This Commands Perform the tests for the function Number2WordsByLength
Test Number2WordsByLength NoInput
Test Number2WordsByLength InvalidNumber
Test Number2WordsByLength ResultCount
Test Number2WordsByLength PrintResult

-- This Commands Perform the tests for the function NumberPrefix2Word
Test NumberPrefix2Word NoInput
Test NumberPrefix2Word InvalidNumber
Test NumberPrefix2Word ResultCount
Test NumberPrefix2Word PrintResult

-- This Commands Perform the tests for the function NumberPrefix2SortedWords
Test NumberPrefix2SortedWords NoInput
Test NumberPrefix2SortedWords InvalidNumber
Test NumberPrefix2SortedWords ResultCount
Test NumberPrefix2SortedWords PrintResult
**/
int main(int argc, char *argv[]) {
	T9Converter converter;
	Converter = converter;
	loadDictionaries();
	loadCountOfWords();
    Tests tests(Converter, SetWordDictionary, WordDictionary, WordWithLengthDictionary, WordWithCountDictionary);
	if(argc > 1 && strcmp(argv[1], "Test") == 0){ // If tests should be executed the command line arg 'Test' should be passed
        if(argc > 2 && strcmp(argv[2], "Word2Number") == 0){
            tests.TestWord2Number(argv[3]);
        }
        else if(argc > 2 && strcmp(argv[2], "Number2Strings") == 0){
            tests.TestNumber2Strings(argv[3]);
        }
        else if(argc > 2 && strcmp(argv[2], "Number2Words") == 0){
            tests.TestNumber2Words(argv[3]);
        }
        else if(argc > 2 && strcmp(argv[2], "Number2WordsByLength") == 0){
            tests.TestNumber2WordsByLength(argv[3]);
        }
        else if(argc > 2 && strcmp(argv[2], "NumberPrefix2Word") == 0){
            tests.TestNumberPrefix2Word(argv[3]);
        }
        else if(argc > 2 && strcmp(argv[2], "NumberPrefix2SortedWords") == 0){
            tests.TestNumberPrefix2SortedWords(argv[3]);
        }
        else{
            tests.TestAll();
        }
	}
	else{ // If no command line args are available we show the programm menu
        StartProgrammWithMenu();
	}

	return 0;
}
