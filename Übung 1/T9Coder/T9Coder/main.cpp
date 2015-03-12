#include <string>
#include <iostream>
#include <algorithm>  
#include <fstream>
#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <hash_map>
#include <sstream>

#include "T9MappingEntry.h"
#include "T9Converter.h"
#include "utility.h"

using namespace std;

static set<string> SetWordDictionary;
static map<string, string>  WordDictionary;
static hash_map<string, string>  HashWordDictionary;
static map<int, map<string, string>> WordWithLengthDictionary;
static map<string, map<string, string>> WordWithT9CodeDictionary;

void loadWordsSetDictionaryFile(){
	clock_t begin = clock();
	ReadAllLinesFromFile("de_neu.dic", [&](string line){
		if (line.find("%") != 0){
			SetWordDictionary.insert(line);
		}
	});
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time for loading File with second method " << elapsed_secs << endl;
}
void loadWordsFromDictionaryFile(){
	clock_t begin = clock();
	for (auto entry : SetWordDictionary){
		WordDictionary[StringToUpper(entry)] = entry;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time for loading File with second method " << elapsed_secs << endl;
}
void loadWordsForHashFromStaticDictionaryFile(){
	clock_t begin = clock();
	for (auto entry : SetWordDictionary){
		HashWordDictionary[StringToUpper(entry)] = entry;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time for loading File with second method " << elapsed_secs << endl;
}
void loadSetWithLengthForWords(){
	for (auto word : WordDictionary){
		WordWithLengthDictionary[word.second.size()].insert(make_pair(word.first, word.second));
	}
}

void InitializeDictionaries(){
	cout << "Load dictionary from disk.... " << endl;
	loadWordsSetDictionaryFile();
	loadWordsFromDictionaryFile();
	loadWordsForHashFromStaticDictionaryFile();
	loadSetWithLengthForWords();
	cout << "Dictionary succesfully loaded. (" << WordDictionary.size() << " Entries) " << endl;
}

int main(int argc, char *argv[]) {
	InitializeDictionaries();
	T9Converter converter;

	bool finished = false;
	int option = 0;
	while (!finished){
		cout << "Geben Sie an welche der untenstehenden Optionen Sie ausführen wollen:" << endl;
		cout << "<1> Wort zu Nummer konvertieren. " << endl;
		cout << "<2> Nummer zu Zeichenfolge konvertieren. " << endl;
		cout << "<3> Nummer zu Wörtern konvertieren. " << endl;
		cout << "<4> Nummer zu Wörtern konvertieren (Hashmap). " << endl;
		cout << "<5> Nummer zu Wörtern konvertieren (Länge). " << endl;
		cout << "<6> Nummernprefix zu Wörtern. " << endl;
		cout << "<7> Nummernprefix zu Wörtern nach Relevanz. " << endl;
		cout << "<8> Beenden. " << endl;
		cin >> option;
		if (option == 1){
			cout << "Bitte geben Sie das gewünschte Wort ein: " << endl;
			string wordToConvert;
			cin >> wordToConvert;
			auto result = converter.Word2number(wordToConvert);
			cout << "Word2Number: " << wordToConvert << " = " << result << endl;
		}
		else if (option == 2){
			cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
			string numberToConvert = "";
			cin >> numberToConvert;
			auto result = converter.Number2strings(numberToConvert);
			cout << "Number2strings: " << numberToConvert << " = " << result.size() << endl;
		}
		else if (option == 3){
			cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
			string numberToConvert = "";
			cin >> numberToConvert;
			auto result = converter.Number2Words(numberToConvert, WordDictionary);
			cout << "Number2Words: " << numberToConvert << " = " << result.size() << endl;
			for_each(result.begin(), result.end(), [&](const string entry){
				cout << entry << endl;
			});
		}
		else if (option == 4){
			cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
			string numberToConvert = "";
			cin >> numberToConvert;
			auto result = converter.Number2WordsWithHashMap(numberToConvert, HashWordDictionary);
			cout << "Number2WordsWithHashMap: " << numberToConvert << " = " << result.size() << endl;
			for_each(result.begin(), result.end(), [&](const string entry){
				cout << entry << endl;
			});
		}
		else if (option == 5){
			cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
			string numberToConvert = "";
			cin >> numberToConvert;
			auto result = converter.Number2WordsByLength(numberToConvert, WordWithLengthDictionary);
			cout << "Number2WordsByLength: " << numberToConvert << " = " << result.size() << endl;
			for_each(result.begin(), result.end(), [&](const string entry){
				cout << entry << endl;
			});
		}
		else if (option == 6){
			cout << "Bitte geben Sie die gewünschte Nummer an: " << endl;
			string numberToConvert = "";
			cin >> numberToConvert;
			auto result = converter.NumberPrefix2Word(numberToConvert, WordDictionary);
			cout << "NumberPrefix2Word: " << numberToConvert << " = " << result.size() << endl;
			for_each(result.begin(), result.end(), [&](const string entry){
				cout << entry << endl;
			});
		}
		else if (option == 7){
			cout << "Noch nicht implementiert." << endl;
		}
		else if (option == 8){
			finished = true;
		}
		else{
			cout << "Ungültige Nummer eingegeben." << endl;
		}
		system("pause");
		system("cls");
	}

	system("pause");
	return 0;
}