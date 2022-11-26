// Title: Lab 1 - FileProcessing.cpp
//
// Purpose: Converts and transfers info from JSON files into new CSV files using only cstrings.
//
// Class: CSC 2430 Winter 2022
// Author: Karena Qian



#include "Formatting.h"
#include "FileProcessing.h"
#include <iostream>
#include <fstream>
#include <cstring>


using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::getline;

// Helper method for ProcessFiles.
// Takes in a cstring source and returns a new cstring comprised of characters
// after position start in source.
//
// Parameters:
//      source - cstring from which the new cstring will be derived
//      start - the starting position of the new cstring in source
// Returns:
//      new cstring derived from source
char* SubStr(const char* source, size_t start){
    char* neo = new char[100];
    int i;
    for(i = start; source[i] != '\0'; i++){
        neo[i - start] = source[i];
    }
    neo[i - start] = '\0';
    return neo;
}
// Helper method for ProcessFiles.
// Prints out the given cstring to the given ofstream, ending with an endline.
//
// Parameters:
//      str - given cstring to print
//      ofSS - given ofstream to write cstring to
// Returns:
//      nothing
void printCString(const char* str, ofstream& ofSS){
    for(int i = 0; str[i] != '\0'; i++){
        ofSS << str[i];
    }
    ofSS << endl;
}
// Operates in a loop so multiple files can be processed.
// On each iteration, reads name of input and output files from user and opens them
// Then calls ProcessFile to do the actual file processing
// - If user enters a blank line for the input file, loop ends
// - If either file cannot be opened, loop restarts
//
// Parameters:
//      none
// Returns:
//      nothing
void ProcessFiles() {
//for storing user input of output and input files
    char* inputFile = new char[50];
    char* outputFile = new char[50];

    //for storing max, min, and average of ages
    //(max initialized to -1 since age does not exist below 0)
    //(min initialized to 1 billion since human age does/has not exceeded the value)
    int maxAge = -1;
    int minAge = 1000000000;
    double sumAge = 0;
    double numPeople = 0;

    //first input for input file
    cout << "Input File Name: ";
    cin.getline(inputFile, 50);

    //while the user input is not an empty line
    while (strlen(inputFile) != 0){
        ifstream ifSS(inputFile);

        //(Note for error-checking code segments:
        // printing the error using cerr and then asking for input using cout gives an unsolvable bug)

        //checks if file is in correct format, if not, restart current loop
        char* partJSON = SubStr(inputFile, strlen(inputFile) - 5);
        if (strcmp(partJSON, ".json") != 0) {
            cout << "ERROR: Incorrect file format, please provide a JSON file" << endl;

            //get input for input file again before restarting loop
            cout << "Input File Name: ";
            cin.getline(inputFile, 50);
            continue;
        }

        //if input file cannot be opened, restart current loop
        if(!ifSS.is_open()){
            cout << "ERROR: " << inputFile << " not found" << endl;

            //get input for input file again before restarting loop
            cout << "Input File Name: ";
            cin.getline(inputFile, 50);
            continue;
        }
            //else if file is successfully opened
        else {
            //for output file loop
            bool isValid = false;

            //get output file input
            cout << "Output File Name: ";
            cin.getline(outputFile, 50);
            ofstream ofSS(outputFile);

            //runs until output file name is valid and successfully opened
            while (!isValid) {
                //checks for correct format, stays in loop if in incorrect format
                char* partCSV = SubStr(outputFile, strlen(outputFile) - 4);
                if (strcmp(partCSV, ".csv") != 0) {
                    cout << "ERROR: Incorrect file format, please provide a CSV file" << endl;
                    //get output file input before current loop restarts
                    cout << "Output File Name: ";
                    cin.getline(outputFile, 50);
                    ofSS.open(outputFile);
                    continue;
                }
                else{
                    isValid = true;
                }
                //checks if output file cannot be opened, stays in loop if true
                if (!ofSS.is_open()) {
                    cout << "ERROR: " << outputFile << " not found" << endl;

                    //get output file input before current loop restarts
                    cout << "Output File Name: ";
                    cin.getline(outputFile, 50);
                    ofSS.open(outputFile);
                    continue;
                }
                else{
                    isValid = true;
                }
            }

            //if output file is valid and successfully opened:
            //create CSV file from JSON file
            //and gather info about ages
            ofSS << CSVHeader() << endl;

            //get first line
            char* line = new char[150];
            char* formattedLine = new char[100];
            ifSS.getline(line, 150, '\n');
            //runs while the variable is not empty
            //(prevents an extra empty CSV line from being printed at the end of the output file)
            while (!ifSS.eof() || strlen(line) > 0) {
                //converts and prints each JSON line in CSV format
                FormatAsCSV(line, formattedLine);
                printCString(formattedLine, ofSS);

                //gathers age info if age exists
                char* age = new char[10];
                GetAge(line, age);
                if (strcmp(age, " \0") != 0) {
                    int intAge = atoi(age);
                    if (intAge > maxAge) {
                        maxAge = intAge;
                    }
                    if (intAge < minAge) {
                        minAge = intAge;
                    }
                    sumAge += intAge;
                    numPeople++;
                }

                delete[] line;
                line = new char[150];
                ifSS.getline(line, 150, '\n');
            }

            //close output file
            ofSS.close();
        }
        //close input file
        ifSS.close();

        //prints out age info
        cout << "Minimum age: " << minAge << endl;
        cout << "Maximum age: " << maxAge << endl;
        cout << "Average age: " << sumAge / numPeople << endl;

        //Resets variables for recording age info
        maxAge = -1;
        minAge = 1000000000;
        sumAge = 0;
        numPeople = 0;

        //get input for input file before loop begins again
        cout << "Input File Name: ";
        cin.getline(inputFile, 50);
    }
}

