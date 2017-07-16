/*

Contains Templates for Creating Various Project Files
and System Commands

*/

// Include Guard
#ifndef _template_h
#define _template_h

// Includes
#include <iostream>
#include <string>


// Helpful Message about functionality
extern const std::string tHelp[];

// Template For holding Project Header Information like
//  - Author Name
//  - Email
//  - Dates
//  - Tags
extern const std::string tHeader;

// Template for Project Makefile
extern const std::string tMakeFile;

// Template for Project Latex Document
extern const std::string tDocFile;

// Template for Latex Implementation Slide Command
extern const std::string tImplmntPage;

// Template for Latex Test Slide A Command with an Image
extern const std::string tTestPageA;

// Template for Latex Test Slide B Command with no Image
extern const std::string tTestPageB;

// Template for C++ *.h Header File
extern const std::string tHFile;

// Template for C++ *.cpp Source File
extern const std::string tCPPFile;

// Template for  a C++ Main Function that prints 'Hello World'
extern const std::string tMainFunct;

// Template for Project Directory Structure
extern const std::string tProjectDirectories[];

// Template for the  Shell Test File
extern const std::string tTestFile;

#endif
