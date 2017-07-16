/*

Contains all the definitions for Commandline Arguments that do not take
any extra arguments, with the exception of the 'handleDocArg()'

*/

// Includes
#include "../include/genlab.h"



// Build and Compile the Project
int handleBuildArg()
{
	int exitCode = ( (checkProjInit() && checkMakeFileInit()) ? InitError : NoError );
	exitCode |= (_checkCall("make build") ? BuildError : NoError);
	
	//If Everything Build, then backup the build
	if(!exitCode)
		exitCode |= (_checkCall("make bkpBuild") ? PackError : NoError);
	
	return exitCode;
}

// Run the Project
int handleRunArg()
{
	int exitCode = ( (checkProjInit() && checkMakeFileInit()) ? InitError : NoError );
	exitCode = (_checkCall("make run") ? RunError : NoError);

	//If Everything Build, then backup the run
	if(!exitCode)
		exitCode |= (_checkCall("make bkpRun") ? PackError : NoError);
	
	return exitCode;
}

// Package the Project
int handlePackArg()
{
	return ( (checkProjInit() && checkMakeFileInit()) ? InitError : NoError ) |
		( _checkCall("make pkg") ? PackError : NoError );
}

// Diplay Information about the Project
int handleInfoArg()
{
	GenFile gf;
	int exitCode = (gf.load() ? InitError : NoError);
	
	if(exitCode)
		return exitCode;
	
	std::cout << "Project Overview:\n\n" << gf.info() << "n\n\nModules:\n";
	
	for(int i = 0; i < gf.projFiles.size(); i++)
	{
		std::cout << gf.projFiles[i].info() << "\n\n";
	}
	
	return exitCode;
}

