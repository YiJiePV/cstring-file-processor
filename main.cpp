// Title: Lab 1 - main.cpp
//
// Purpose: Convert files with lines in JSON format to a CSV file
//
// Class: CSC 2430 Winter 2022
// Author: Max Benson

#include <iostream>
#include <cstring>
#include <cassert>
using std::cout;
using std::endl;
using std::string;

#include "FileProcessing.h"
#include "Formatting.h"

// Forward declaration
bool TestFormatting();

int main() {
    // Validate the string re-formatting function
    if (!TestFormatting()) {
        return 1;
    }
    cout << "VALIDATION SUCCEEDS" << endl;

    // Process one set of files
    ProcessFiles();
    return 0;
}

// Unit Test function for validating the formatting functions
//
// Parameters:
//      none
// Returns:
//      true if validation passes, false otherwise
bool TestFormatting() {
    char temp[100];

    string inputJSON[] = {
            R"({ "FirstName":"Hulk" })",
            R"({ "FirstName":"Peter", "LastName":"Parker" })",
            R"({ "LastName":"Stark", "FirstName":"Tony" })",
            R"({ "FirstName":"Flash", "LastName":"Thompson", "Age":16  })"
    };
    string outputCSV[] = { //changed per request of Professor Arias
            "Hulk,,,,",
            "Peter,Parker,,,",
            "Tony,Stark,,,",
            "Flash,Thompson,16,,"
    };
    string outputNumber[] = {
            "",
            "",
            "",
            "16"
    };

    // Test ParseNumberValue
    assert( sizeof(inputJSON)/sizeof(inputJSON[0]) == sizeof(outputNumber)/sizeof(outputNumber[0]) );
    for (int i = 0; i < sizeof(inputJSON)/sizeof(inputJSON[0]); i ++ ) {
        GetAge(inputJSON[i].c_str(), temp);
        if (outputNumber[i] != temp) {
            cout << "VALIDATION FAILURE: GetAge( '" << inputJSON[i] << "' ) returns"  << temp << endl;
            return false;
        }
    }

    // Test FormatAsCSV
    assert( sizeof(inputJSON)/sizeof(inputJSON[0]) == sizeof(outputCSV)/sizeof(outputCSV[0]) );
    for (int i = 0; i < sizeof(inputJSON)/sizeof(inputJSON[0]); i ++ ) {
        FormatAsCSV(inputJSON[i].c_str(), temp);
        if (outputCSV[i] != temp) {
            cout << "VALIDATION FAILURE: FormatAsCSV( '" << inputJSON[i] << "' ) returns " << temp << endl;
            return false;
        }
    }

    return true;
}
