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
        std::cout << "\nAuthor: ";
        getline(std::cin, gf.prjAuthor);

        // Set Project Email
        std::cout << "Email: ";
        getline(std::cin, gf.prjEmail);

        // Set Project Tagline
        std::cout << "Tag: ";
        getline(std::cin, gf.prjTag);

        // Set Project Description
        std::cout << "\nProject Description (leave a blank"
                    << " line to save entry and continue):\n";
        gf.prjDesc  = _getMultiLineInput();

        // Prompt User to Verify Information Before Continuing
        std::cout << "========================================\n"
                << "         ~PROJECT OVERVIEW~\n"
                << "========================================\n\n"
                << gf.info() <<"\n\n\nContinue? (y/n): ";

        getline(std::cin, ch);

    }while( std::string("yesYesYES").find(ch) == std::string::npos );

    // Add Project Header & Source File and any
    //  other files specified from the commandline
    std::strcpy(vals[1], (gf.prjName + ".h").c_str());
    std::strcpy(vals[2], (gf.prjName + ".cpp").c_str());

    // Loop Through and get Information for each File
    for(int i = 1; i < c; i++)
    {
        ProjFile pf;

        pf.name = vals[i];

        std::cout << "\nBreif description for " << pf.name 
                    << " Module (leave a blank line to save entry and continue):\n";
        pf.desc = _getMultiLineInput();

        std::cout << "Libraries to include in " << pf.name 
            << " Module (one per line, leave line empty to save and continue):\n";

        pf.content = _getMultiLineInput();

        // DEBUG LINE
        //std::cout << "AFTER GLIB\n\n";

        if( pf.name.find(".cpp") != std::string::npos)
        {
            pf.dir = "srcs/";
            
            //DEBUG LINE
            std::cout << "else cpp\n";

            // Needed to prevent infinite loop when replacing string where
            //  original is a substring of the replacement
            pf.content = _strReplace(pf.content, "\n", kFileDelim);

            // Add in Included Dependencies
            pf.content = _strReplace(tCPPFile, "%INCLUDE%", "#include <" + 
                            _strReplace( pf.content, kFileDelim, ">\n#include <") + ">\n"); 
        }
        else if (pf.name.find(".h") != std::string::npos)
        {
            // DEBUG LINE
            std::cout << "else h\n\n";

            // Needed to prevent infinite loop when replacing string where
            //  original is a substring of the replacement
            pf.content = _strReplace(pf.content, "\n", kFileDelim);

            pf.dir = "include/";

            // Add in Included Dependencies
            pf.content = _strReplace(tHFile, "%INCLUDE%", "#include <" + 
                            _strReplace( pf.content, kFileDelim, ">\n#include <") + ">\n"); 
        }
        else
        {
            // DEBUG LINE
            std::cout << "else\n\n";

            // Skip adding content if the File
            //  is not a source or header file
            pf.dir = "";
            gf.projFiles.push_back(pf);
            continue;
        }
        
        // DEBUG LINE
        std::cout << "AFTER after B\n\n";

        // Replace the Description & Check for Error
        exitCode |= ((_strReplaceI(pf.content, "%HEADER%",
                    gf.hInfo() + "\n\nDescription:\n"+ pf.desc) > 0) ?
                    NoError : InitError);


        if(!exitCode)
            gf.projFiles.push_back(pf);
    }

    // Write the GenFile to file and create all the project files if
    //  no erros have occured thus far
    if( !exitCode)
    {
		projDirectoryInit(gf.prjName);

        exitCode |= ( gf.write(gf.prjName + "/") ? 
                        NoError : InitError );

        exitCode |= ( gf.gen(gf.prjName + "/") ? 
                        NoError : InitError );

        makeFileInit(gf);

		std::cout << "\nExit Code: " << exitCode << "\n";
    }

    return exitCode;
}
