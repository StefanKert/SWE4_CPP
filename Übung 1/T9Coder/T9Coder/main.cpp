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

using namespace std;

static set<string> SetWordDictionary;
static map<string, string>  WordDictionary;
static map<int, map<string, string>> WordWithLengthDictionary;
static hash_map<string, set<string>> WordDictionaryWithT9;

void loadDictionaries(T9Converter & converter){
	clock_t begin = clock();
	ReadAllLinesFromFile("de_neu.dic", [&](string line){
		if (line.find("%") != 0){
			SetWordDictionary.insert(line);
			WordDictionary[StringToUpper(line)] = line;
			WordWithLengthDictionary[line.size()].insert(make_pair(StringToUpper(line), line));
			//WordDictionaryWithT9[converter.Word2Number(line)].insert(line);
		}
	});
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time for loading File with second method " << elapsed_secs << endl;
}

void InitializeDictionaries(T9Converter & converter){
	cout << "Load dictionary from disk.... " << endl;
	loadDictionaries(converter);
	cout << "Dictionary succesfully loaded. (" << WordDictionary.size() << " Entries) " << endl;
}

int main(int argc, char *argv[]) {
	T9Converter converter;
	InitializeDictionaries(converter);

	bool finished = false;
	int option = 0;
	while (!finished){
		try{
			cout << "Geben Sie an welche der untenstehenden Optionen Sie ausführen wollen:" << endl;
			cout << "<1> Wort zu Nummer konvertieren. " << endl;
			cout << "<2> Nummer zu Zeichenfolge konvertieren. " << endl;
			cout << "<3> Nummer zu Wörtern konvertieren. " << endl;
			cout << "<4> Nummer zu Wörtern konvertieren (Länge). " << endl;
			cout << "<5> Nummernprefix zu Wörtern. " << endl;
			cout << "<6> Nummernprefix zu Wörtern nach Relevanz. " << endl;
			cout << "<7> Beenden. " << endl;
			cin >> option;
			if (option == 1){
				cout << "Bitte geben Sie das gewünschte Wort ein: " << endl;
				string wordToConvert;
				cin >> wordToConvert;
				clock_t begin = clock();
				auto result = converter.Word2Number(wordToConvert);
				clock_t end = clock();
				double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
				cout << "Word2Number: " << wordToConvert << " = " << result << endl;
				cout << "Time for Word2Number " << elapsed_secs << endl;
			}
			else if (option == 2){
				cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
				string numberToConvert = "";
				cin >> numberToConvert;
				if (!converter.IsNumberValid(numberToConvert)){
					cout << "Die angegebene Nummer war ungültig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
				}
				else{
					clock_t begin = clock();
					auto result = converter.Number2Strings(numberToConvert);
					clock_t end = clock();
					double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
					cout << "Number2strings: " << numberToConvert << " = " << result.size() << endl;
					cout << "Time for Number2Strings " << elapsed_secs << endl;
				}
			}
			else if (option == 3){
				cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
				string numberToConvert = "";
				cin >> numberToConvert;
				if (!converter.IsNumberValid(numberToConvert)){
					cout << "Die angegebene Nummer war ungültig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
				}
				else{
					clock_t begin = clock();
					auto result = converter.Number2Words(numberToConvert, WordDictionary);
					clock_t end = clock();
					double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
					cout << "Number2Words: " << numberToConvert << " = " << result.size() << endl;
					cout << "Time for Number2Words " << elapsed_secs << endl;
					for_each(result.begin(), result.end(), [&](const string entry){
						cout << entry << endl;
					});
				}
			}
			else if (option == 4){
				cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
				string numberToConvert = "";
				cin >> numberToConvert;
				if (!converter.IsNumberValid(numberToConvert)){
					cout << "Die angegebene Nummer war ungültig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
				}
				else{
					clock_t begin = clock();
					auto result = converter.Number2WordsByLength(numberToConvert, WordWithLengthDictionary);
					clock_t end = clock();
					double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
					cout << "Number2WordsByLength: " << numberToConvert << " = " << result.size() << endl;
					cout << "Time for Number2WordsByLength " << elapsed_secs << endl;
					for_each(result.begin(), result.end(), [&](const string entry){
						cout << entry << endl;
					});
				}
			}
			else if (option == 5){
				cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
				string numberToConvert = "";
				cin >> numberToConvert;
				if (!converter.IsNumberValid(numberToConvert)){
					cout << "Die angegebene Nummer war ungültig. Die Nummer darf nur Zahlen von 2 - 9 enthalten." << endl;
				}
				else{
					clock_t begin = clock();
					auto result = converter.NumberPrefix2Word(numberToConvert, WordDictionary);
					clock_t end = clock();
					double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
					cout << "NumberPrefix2Word: " << numberToConvert << " = " << result.size() << endl;
					cout << "Time for NumberPrefix2Word " << elapsed_secs << endl;
					for_each(result.begin(), result.end(), [&](const string entry){
						cout << entry << endl;
					});
				}

			}
			else if (option == 6){
				cout << "Noch nicht implementiert." << endl;
			}
			else if (option == 7){
				finished = true;
			}
			else{
				cout << "Ungültige Nummer eingegeben." << endl;
			}
			system("pause");
			system("cls");
		}
		catch (bad_alloc &e){
			cout << e.what() << endl;
		}
		catch (...){
			cout << "Ein schwerer Fehler ist aufgetreten der nicht erkannt werden konnte bitte starten Sie das Programm neu. " << endl;
		}
	}

	system("pause");
	return 0;
}