// Title: Lab 1 - Formatting.h
//
// Purpose: Declares the functions that understand the JSON format and can reformat a line of
// JSON to a line of CSV
//
// Class: CSC 2430 Winter 2022
// Author: Max Benson

#ifndef FORMATTING_H
#define FORMATTING_H



char* CSVHeader();
void FormatAsCSV(const char* json, char* csvLine);
void GetAge(const char* json, char* ageString);

#endif //FORMATTING_H
