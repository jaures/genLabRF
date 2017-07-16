/*

Contains Functions and Structs Directly Related to the Operation
And Logic of the Genlab Project

*/

// Include Guard
#ifndef _genlab_h
#define _genlab_h

// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <sys/stat.h>

#include "templates.h"
#include "structs.h"



// mode_t Value for all permissions (777)
#define MOD777  S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP |\
    S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH


enum ExitCode
{
    NoError     = 0x0,
    InitError   = 0x1,
    BuildError  = 0x2,
    RunError    = 0x4,
    DocError    = 0x8,
    TestError   = 0x10,
    PackError   = 0x20,
    AddError    = 0x40,
    RemError    = 0x80
};

// Exit Code Messages for the ExitCode Enum
extern const std::string kExitCodeErrors[9];

// Commandline Argument Handlers

// Init the Project Directory
int handleInitArg(int, char*[]);

// Build and Compile the Project
int handleBuildArg();

// Run the Project
int handleRunArg();

// Run the Documentation Wizard and Produce a Document
int handleDocArg();

// Run the Test Wizard and Generate Test Documentation
int handleTestArg(int=2, char*[]=0);

// Package the Project
int handlePackArg();

// Add a New File to the Project
int handleAddArg(int, char*[]);

// Remove a File from the Project
int handleRemArg(int, char*[]);

// Diplay Information about the Project
int handleInfoArg();

// Produce the Help Message
int handleHelpArg( char*);


// Helper Functions

// Check if Current Directory Contains an
//  Initialized Project .genFile
bool checkProjInit();

// Check if Current Directory Contains an
//  Initialized Project Makefile
bool checkMakeFileInit();

// Check if Current Directory Contains an
//  Initialized Project .testFile
bool checkTestsInit();

// Check if Current Directory Contains Initialized
//  Project Documentation
bool checkDocsInit();

// Creates a stream to write to a .TeX File
//  @Returns a Stream to Content of the Doc File
std::string importTests(TestFile);



// Create the Project Directory
bool projDirectoryInit(std::string);

// Creates a stream to write to a .TeX File
//  @Returns a Stream to Content of the Doc File
std::string docFileInit(GenFile);

// Creates a Stream to write a Makefile
//  @Returns a Stream to the Content of the Makefile
std::string makeFileInit(GenFile);



// Close Include Guard
#endif
