// Title: Lab 1 - Formatting.cpp
//
// Purpose: Stores functions that create a CSV header, help convert a JSON line to a CSV line, and
// retrieve certain information from said JSON line
//
// Class: CSC 2430 Winter 2022
// Author: Karena Qian

#include <cstring>
#include <sstream>

#include "Formatting.h"

using std::stringstream;

// Returns CSV header as a cstring
//
// Parameters:
//      None
// Returns:
//      CSV header
char* CSVHeader() {
    char* header = new char[50];
    strcpy(header, "FirstName,LastName,Age,Height,Nationality\0");
    return header;
}

// Helper method for FindAfterCharType, FindWord, and ParseJson
// Returns index of first instance of type of char, indicated by type, in str,
// -1 if no sought chars are found.
//
// Parameters:
//      str - cstring from which char type is found
//      type - type of char to be found, can be integer (i, number) or alpha (a, word)
// Returns:
//      index of first instance of type of char, -1 otherwise
int FindFirstCharType(const char* str, const char type){
    for(int i = 0; str[i] != '\0'; i++){
        if(type == 'a' && isalpha(str[i])) {
            return i;
        }
        else if(type == 'i' && isdigit(str[i])){
            return i;
        }
    }
    return -1;
}
// Helper method for FindWord and ParseJson
// Returns char just after the first word or number, or returns an empty char
// if the whole str is a word or a number.
//
// Parameters:
//      str - cstring from which word or number is found
//      type - type of char to be found, can be integer (i, number) or alpha (a, word)
// Returns:
//      char just after first word or number
char FindAfterCharType(const char* str, const char type){
    for(int i = FindFirstCharType(str, type); str[i] != '\0'; i++){
        if(type == 'a' && !isalpha(str[i])) {
            return str[i];
        }
        else if(type == 'i' && !isdigit(str[i])){
            return str[i];
        }
    }
    return ' ';
}
// Helper method for FindWord and ParseJson
// Returns cstring consisting of char from position start to just before char end
// in cstring source.
//
// Parameters:
//      source - cstring from which sub cstring is derived
//      start - beginning of new cstring in source
//      end - just before new cstring ends in source, default set to \0
// Returns:
//      cstring derived from source
char* SubStr(const char* source, size_t start, char end = '\0'){
    char* neo = new char[100];
    int i;
    for(i = start; source[i] != end; i++){
        neo[i - start] = source[i];
    }
    neo[i - start] = '\0';
    return neo;
}
// Helper method for ParseJson
// Finds given cstring word in cstring str. If found, returns index just after the last char of the word.
// Otherwise, returns -1.
//
// Parameters:
//      str - cstring from which word is found
//      word - word to be found
// Returns:
//      index just after last char of word, or -1 if word is not found
int FindWord(const char* str, const char* word){
    size_t index = 0;
    char* strcopy = new char[100];
    char* substr;
    strcpy(strcopy, str); //copies str into strcpy to create a local copy of str
    //check if each word in str is word
    while(FindFirstCharType(strcopy, 'a') != -1){
        index += FindFirstCharType(strcopy, 'a'); //get index of first char of first word in strcopy
        //get first word
        substr = SubStr(strcopy, FindFirstCharType(strcopy, 'a'), FindAfterCharType(strcopy, 'a'));
        //return index after word if same as first word
        if(strcmp(substr, word) == 0){
            return static_cast<int>(index + strlen(substr));
        }
        //removes first word and all char before first word from strcopy
        strcopy = SubStr(strcopy, FindFirstCharType(strcopy, 'a') + strlen(substr));
        //update index to position just after first word
        index += strlen(substr);
    }
    //return -1 if word is not found
    return -1;
}
// Helper method for FormatAsCSV and GetAge
// Parses through the given JSON cstring and returns the requested information
// as a cstring. If not found, returns an empty cstring.
//
// Parameters:
//      json - JSON formatted line
//      word - desired info
// Returns:
//      info as a cstring, or empty if info is not found
char* ParseJson(const char* json, char* word) {
    char* newStr = new char[100];
    int wordIndex = FindWord(json, word);
    //If word is not found in json
    if (wordIndex == -1) {
        //return a space
        strcpy(newStr, "\0");
    }
    else {
        //trims out desired info (gives json up to the desired info plus everything after it)
        newStr = SubStr(json, wordIndex);
        //finishes trimming out extra string based on type and position of info
        if (strcmp(word, "Age\0") == 0 || strcmp(word, "Height\0") == 0) {
            newStr = SubStr(newStr, FindFirstCharType(newStr, 'i'), FindAfterCharType(newStr, 'i'));
        }
        else {
            newStr = SubStr(newStr, FindFirstCharType(newStr, 'a'), FindAfterCharType(newStr, 'a'));
        }
    }
    return newStr;
}

// Converts one JSON formatted line to CSV, returning the CSV
// representation as a string
//
// Parameters:
//      json - JSON formatted line
// Returns:
//      CSV formatted line
void FormatAsCSV(const char* json, char* csvLine) {
    char wordFirstname[] = {'F', 'i', 'r', 's', 't', 'N', 'a', 'm', 'e', '\0'};
    char wordLastname[] = {'L', 'a', 's', 't', 'N', 'a', 'm', 'e', '\0'};
    char wordAge[] = {'A', 'g', 'e', '\0'};
    char wordHeight[] = {'H', 'e', 'i', 'g', 'h', 't', '\0'};
    char wordNationality[] = {'N', 'a', 't', 'i', 'o', 'n', 'a', 'l', 'i', 't', 'y', '\0'};

    char* firstname = ParseJson(json, wordFirstname);
    char* lastname = ParseJson(json, wordLastname);
    char* age = ParseJson(json, wordAge);
    char* height = ParseJson(json, wordHeight);
    char* nationality = ParseJson(json, wordNationality);

    stringstream ss;
    ss << firstname << "," << lastname << "," << age << "," << height << "," << nationality;
    strcpy(csvLine, ss.str().c_str());
}

// Return the age value stored in a JSON
// formatted line.  The return value is a string
// If age doesn't appear, returns empty string
//
// Parameters:
//      json - JSON formatted line
// Returns:
//      age as string, or empty if age doesn't appear
void GetAge(const char* json, char* ageString) {
    char wordAge[] = {'A', 'g', 'e', '\0'};
    strcpy(ageString, ParseJson(json, wordAge));
}

