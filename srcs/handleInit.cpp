/*

Include Definition for Functions Related to the Initialization
of the Project Directory and its Files.

*/

// Includes
#include "../include/genlab.h"



// Init the Project Directory
int handleInitArg(int c, char* vals[])
{
	int exitCode = NoError;
	GenFile gf;
	std::string ch;
	
	// Set Project Name
	gf.prjName = vals[2];
	
	do
	{
		// Set Project Author
		std::cout << "Author: ";
		getline(gf.prjAuthor);
		
		// Set Project Email
		std::cout << "Email: ";
		getline(gf.prjEmail);
		
		// Set Project Tagline
		std::cout << "Tagline: ";
		getline(gf.prjTag);
		
		// Set Project Description
		std::cout << "Project Description (leave a blank line to save entry and continue):\n";
		gf.prjEmail  = _getMultiLineInput();
		
		// Prompt User to Verify Information Before Continuing
		std::cout << "========================================\n"
				<< "\t\t\tPROJECT OVERVIEW\n"
				<< "========================================\n\n"
				<< gf.info() <<"\n\n\nContinue? (y/n): ";
				
	}while( std::string("yesYesYES").find(ch) != std::string::npos );	
	
	// Loop Through and get Information for each File
	for(int i = 3; i < c; i++)
	{
		ProjFile pf;
		
		pf.name = vals[i];
		
		std::cout << "Breif description for " << pf.name << " Module:\n";
		getline(std::cin, pf.desc);
		
		if( pf.name.find(".cpp") != std::string::npos)
		{
			pf.dir = "srcs/";
		}
		else if (pf.name.find(".h") != std::string::npos)
		{
			pf.dir = "include/";
		}
		else
		{
			// Skip adding content if the File
			//	is not a source or header file
			pf.dir = "";
			gf.projFiles.push_back(pf);
			continue;
		}
		
		std::cout << "Libraries to include in " << pf.name << " Module (Seperate with spaces):\n"; 
		std::string line;
		getline(std::cin, line);
		
		// Set the Template based on the filetype
		pf.content = ((pf.dir == "srcs/") ? tHFile : tCPPFile);
		
		// Replace the Description & Check for Error
		exitCode |= ((_strReplace(pf.content, "%DESC%", 
					gf.hInfo() + "\n\nDescription:\n"+ pf.desc) > 0) ?
					NoError : InitError);
		
		// Add in Included Dependencies & Check for Error
		exitCode |= ((_strReplace(pf.content, "%INCLUDE%",
					"/*\n" + gf.info() + "\n*/\n\n#include <" +
					_strReplace(line, " ", ">\n#include <") + ">\n") > 0 ) ? 
					NoError : InitError);
	}
	
	// Write the GenFile to file and create all the project files if
	//	no erros have occured thus far
	if( !exitCode)
	{
		exitCode |= ( gf.write(gf.prjName() + "/") ? NoError : InitError );
		exitCode |= ( gf.gen(gf.prjName() + "/") ? NoError : InitError );
	}
	
	return exitCode;
}


