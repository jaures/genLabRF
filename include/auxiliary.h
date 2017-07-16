/*

Contains Useful Auxiliary Functions

*/

// Include Guard
#ifndef _auxiliary_h
#define _auxiliary_h

// Includes
#include <iostream>
#include <string>
#include <fstream>



// Maximum Buffer Size
extern const int kMaxBuff;


// Perform a system call
//  @Return the exit code
int _checkCall(std::string);

// Takes a the first argument, and replaces all instances of
//  the second argument with the third argument.
//  @Return the new string
std::string _strReplace(std::string, std::string, std::string);

// Takes a the first argument, and replaces all instances of
//  the second argument with the third argument in place.
//  @Return if any swaps were made
int _strReplace(std::string&, std::string, std::string);

// Count Number of New Lines in a string
int _newlineCount(std::string);

// Count Number of New Lines in an ifstream
int _newlineCount(std::string);

// Get Multilined User Input from std::cin
std::string _getMultiLineInput(int);

// Get Multilined User Input from an std::ifstream
std::string _getMultiLineInput(std::ifstream&, int, std::string);


// Close Include Guard
#endif
