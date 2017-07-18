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
    int exitcode = 0;

        // DEBUG LINE
        std::cout << "BOOP!\n";

    // Handle Routing the Command Line Arguments
    if( argc == 1)
    {
        // DEBUG LINE
        std::cout << "BOOP1!\n";

        // Print out the Help if no arguments were passed
        exitcode = handleHelpArg(0);
    }
    else if( argc == 2)
    {// Check for all Arguments that take no extra options
        if( std::string(argv[1]) == "--info")
        {
            exitcode = handleInfoArg();
        }
        else if( std::string(argv[1]) == "--build")
        {
            exitcode = handleBuildArg();
        }
        else if( std::string(argv[1]) == "--run")
        {
            exitcode = handleRunArg();
        }
        else if( std::string(argv[1]) == "--doc")
        {
            exitcode = handleDocArg();
        }
        else if( std::string(argv[1]) == "--pack")
        {
            exitcode = handlePackArg();
        }
        else
        {
            // Display Error Message if there aren't any suitable routes
            std::cout << "\n<Error>: '"<< argv[1] << "' is not a recognized Argument.\n"
                    << "Try running:\n\t --help\nor\n\t--help <arg>\n\n";
            exitcode = -1;
        }
    }
    else if(argc > 2)
    {// Check for all Arguments that take extra options

        if( std::string(argv[1]) == "--init")
        {
            exitcode = handleInitArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--add")
        {
            exitcode = handleAddArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--rem")
        {
            exitcode = handleRemArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--test")
        {
            exitcode = handleTestArg(argc, argv);
        }
        else if( std::string(argv[1]) == "--help")
        {
            exitcode = handleHelpArg(argv[2]);
        }
        else
        {
            // Display Error Message if there aren't any suitable routes
            std::cout << "\n<Error>: Invalid Argument or too many options passed.\n"
                    << "Try running:\n\t --help\nor\n\t--help <arg>\n\n";
            exitcode = -1;
        }
    }

    return exitcode;
}
