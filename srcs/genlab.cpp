/*

Handles the routing logic of the program by taking the commandline
arguments and passing them to their corresposinging commandline argument
handler function.

*/

// Includes
#include "../include/genlab.h"



// Delimiter for Seperating and Identifiying Sections '%#%'
const std::string kFileDelim = "%@%";

// Exit Code Messages for the ExitCode Enum
const std::string kExitCodeErrors[9] =
{
    "\n[/]All Operation Completed Successfully.\n\n",
    "\n<InitError>: No Project found in current directory. Make sure to initialize first. "
        "Try running with argument:\n\t--init\n\n",

    "\n<BuildError>: Unable to compile and build project. Projects can be restored to "
        "last successful build by using:\n\tmake restoreBuild\n\n"
        "Use sparingly, may cause unexpected behavior.\n\n",

    "\n<RunError>: Project failed to run or exited on error. Projects can be restored to "
        "last successful build by using:\n\tmake restoreRun\n\n"
        "Use sparingly, may cause unexpected behavior.\n\n",

    "\n<DocError>: Failed to create project documentation. Try re-running the Doc "
        "Wizard by running with argument:\n\t--doc\n\n"
        "If error persists, manual intervention will be required.\n\n",

    "\n<TestError>: Failed to create and or run Project test cases. Try re-running the "
        "Test Wizard by running with argument:\n\t--test\n\n"
        "If error persists, manual intervention will be required.\n\n",

    "\n<PackError>: Failed to package Project. Make sure Project has been compiled and "
        "Documentation has been created. Make sure to first run arguments:"
        "\n\t--run\n\t--doc\n\n",
    "\n<AddError>: Failed to add new file. File may already exist or be an invalid name.\n\n",
    "\n<RemError>: Failed to remove file. Please verify file exist or check permissions.\n\n"
};


int main(int argc, char * argv[])
{
    int exitCode = 0;

    // Handle Routing the Command Line Arguments
    if( argc == 1)
    {
        // Print out the Help if no arguments were passed
        exitCode = handleHelpArg(0);
    }
    else if( argc == 2)
    {// Check for all Arguments that take no extra options
        if( std::string(argv[1]) == "--info")
        {
            exitCode = handleInfoArg();
        }
        else if( std::string(argv[1]) == "--build")
        {
            exitCode = handleBuildArg();
        }
        else if( std::string(argv[1]) == "--run")
        {
            exitCode = handleRunArg();
        }
        else if( std::string(argv[1]) == "--doc")
        {
            exitCode = handleDocArg();
        }
        else if( std::string(argv[1]) == "--pack")
        {
            exitCode = handlePackArg();
        }
        else if( std::string(argv[1]) == "--help")
        {
            exitCode = handleHelpArg(NULL);
        }
        else
        {
            // Display Error Message if there aren't any suitable routes
            std::cout << "\n<Error>: '"<< argv[1] << "' is not a recognized Argument.\n"
                    << "Try running:\n\t --help\nor\n\t--help <arg>\n\n";
            exitCode = -1;
        }
    }
    else if(argc > 2)
    {// Check for all Arguments that take extra options

        if( std::string(argv[1]) == "--init")
        {
            exitCode = handleInitArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--add")
        {
            exitCode = handleAddArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--rem")
        {
            exitCode = handleRemArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--test")
        {
            exitCode = handleTestArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--help")
        {
            exitCode = handleHelpArg(argv[2]);
        }
        else
        {
            // Display Error Message if there aren't any suitable routes
            std::cout << "\n<Error>: Invalid Argument or too many options passed.\n"
                    << "Try running:\n\t --help\nor\n\t--help <arg>\n\n";
            exitCode = -1;
        }
    }

    return exitCode;
}
