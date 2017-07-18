/*

Contains all the definitions for Commandline Arguments that take
any extra arguments, with the exception of the 'handleInitArg()' and
'handleTestArg()'

*/

// Includes
#include "../include/genlab.h"



// Add a New File to the Project
int handleAddArg(int c, char* vals[])
{
    GenFile gf;
    int exitCode = ( (checkProjInit() && gf.load()) ? InitError : NoError );

    // Check for Error
    if(exitCode)
        return exitCode;

    // Cycle Through All Files to add
    for(int i = 2; i < c; i++)
    {
        // First Check  that file Does not Exist already
        for(int j = 0; j < gf.projFiles.size(); j++)
        {
            if(gf.projFiles[j].name == vals[i])
            {
                std::cout << "<AddError>: '" << vals[i] << "' already exists.\n";
                exitCode |= AddError;
                continue;
            }
        }

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
            //  is not a source or header file
            pf.dir = "";
            gf.projFiles.push_back(pf);

            // Write the File
            pf.write();
            continue;
        }

        std::cout << "Libraries to include in " << pf.name << " Module (Seperate with spaces):\n";
        std::string line;
        getline(std::cin, line);

        // Set the Template based on the filetype
        pf.content = ((pf.dir == "srcs/") ? tHFile : tCPPFile);

        // Replace the Description & Check for Error
        exitCode |= ((_strReplaceI(pf.content, "%DESC%",
                    gf.hInfo() + "\n\nDescription:\n"+ pf.desc) > 0) ?
                    NoError : AddError);

        // Add in Included Dependencies & Check for Error
        exitCode |= ((_strReplaceI(pf.content, "%INCLUDE%",
                    "/*\n" + gf.info() + "\n*/\n\n#include <" +
                    _strReplace(line, " ", ">\n#include <") + ">\n") > 0 ) ?
                    NoError : AddError);

        // Write the File
        pf.write();
    }

    return exitCode;
}

// Remove a File from the Project
int handleRemArg(int c, char* vals[])
{
    GenFile gf;
    int exitCode = ( (checkProjInit() && gf.load()) ? InitError : NoError );

    // Check for Error
    if(exitCode)
        return exitCode;

    // Cycle Through All files to delete
    for(int i = 2, removed = 0; i < c; i++)
    {
        for(int j = 0; j < gf.projFiles.size(); j++)
        {
            // Look for a Matching File to delete
            if(gf.projFiles[j].name == vals[i] )
            {
                std::cout << "Removing: " << vals[i] << " from project. "
                        << "Actual file must be manually removed.\n";
                gf.projFiles.erase(gf.projFiles.begin() + (j - removed));
                removed++;
                continue;
            }

            // No Match Found
            std::cout << "<RemError>: Failed to remove file '" << vals[i] << "'\n";
            exitCode |= RemError;
        }
    }

    gf.write();

    return exitCode;
}

// Produce the Help Message
int handleHelpArg( char* cmd)
{
    std::cout <<   "GENLAB - Lab Project Generator\n\n";

    std::cout << std::string(cmd).empty() << "\nYOMA.\n";

    // If no Argument is given
    if(!cmd || std::string(cmd).empty())
    {
        // Print all Help
        std::cout << "USAGE OVERVIEW:\n";

        for(int i = 0; i < 10; i++)
        {
            std::cout << tHelp[2*i];
        }
    }
    else
    {
        // Print Specific Argument Help
        for(int i = 0; i < 10; i++)
        {
            if( tHelp[2*i].find(cmd) != std::string::npos)
            {
                std::cout << tHelp[2*i] << "\t" 
                    << tHelp[2*i+1] << "\n";

                // Break loop since match is found
                break;
            }
        }

        std::cout << "<HelpError>: Argument '" << cmd 
                    << "' is not recognized\n\n";
    }
    return NoError;
}
