/*

Contains Functions that Perform Subtasks within the Argument
Handler Functionis, but are Significant Enough to require their
Functions.

*/

// Includes
#include "../include/genlab.h"




// Check if Current Directory Contains an
//  Initialized Project .genFile
bool checkProjInit()
{
    return std::ifstream(".genFile");
}

// Check if Current Directory Contains an
//  Initialized Project Makefile
bool checkMakeFileInit()
{
    return (checkProjInit() && std::ifstream("Makefile") );
}


// Check if Current Directory Contains an
//  Initialized Project .testFile
bool checkTestsInit()
{
    // Check if the Project has been initialized and
    //  .testFile exists
    return (checkProjInit() && std::ifstream("bin/tests/.testFile") );
}

// Check if Current Directory Contains Initialized
//  Project Documentation
bool checkDocsInit()
{
    GenFile gf;

    // Check if the Project has been initialized
    if(checkProjInit() && gf.load())
    {
        return std::ifstream( ("docs/" + gf.prjName + ".tex").c_str() );
    }

    return false;
}


// Create the Project Directory
bool projDirectoryInit(std::string pn)
{
    int err = NoError;
    for(int i = 0; i < 8 && !err; i++)
    {
        // Check for an Error After Each Operation
        err &= mkdir(_strReplace( tProjectDirectories[i], "%PROJECT%", pn).c_str(), MOD777);
    }

    return err;
}

// Creates a Stream to write a Makefile
//  @Returns a Stream to the Content of the Makefile
std::string makeFileInit(GenFile gf)
{
    int err = NoError;
    std::stringstream ss;
    std::string line;

    std::cout << "\nRun Makefile Wizard? (y/n): ";
    getline(std::cin, line);
    
    // Exit Wizard if not yes
    if( std::string("yesYesYES").find(line) == std::string::npos)
        return ss.str();


    // Set Content of ss and insert into template project name
    ss << _strReplace(tMakeFile, "%PROJECT%", gf.prjName );

    //Get Other Include Directories and insert into template
    std::cout << "Other Included Directories? (leave a blank line to save entry and continue):\n";
    line = _strReplace(ss.str(), "%OIDIRS%",
                _strReplace(_getMultiLineInput(), "\n", " "));
    
     ss.str(line); 

    //Get Other Compiler Flags and insert into template
    std::cout << "Other Compiler Flags? (seperate with spaces):\n";
    getline(std::cin, line);
    ss.str( _strReplace(ss.str(), "%OFLAGS%", line));

    // Write the Makefile
    std::ofstream fw((gf.prjName + "/Makefile").c_str(), 
            std::ofstream::out | std::ofstream::trunc);
    fw << ss.str();
    fw.close();

    return ss.str();

}

// Creates a stream to write to a .TeX File
//  @Returns a Stream to Content of the Doc File
std::string docFileInit(GenFile gf)
{
    std::stringstream ss;

    // Get User Input for Analysis Slide
    std::cout << "Inputs: (leave a blank line to save entry and continue):\n";
    ss << _getMultiLineInput() << "\n" << kFileDelim << "\n";
    std::cout << "Processes: (leave a blank line to save entry and continue):\n";
    ss << _getMultiLineInput() << "\n" << kFileDelim << "\n";
    std::cout << "Outputs: (leave a blank line to save entry and continue):\n";
    ss << _getMultiLineInput() << "\n" << kFileDelim << "\n";

    // Get User Input for Implementation Slides
    //  And build Design Slide at the same time;
    for(int i = 0; i < gf.projFiles.size(); i++)
    {
        // Build Design Description
        ss << "\t\t\\item[" + gf.projFiles[i].name +
                    "]\\hfill \\\\ " + gf.projFiles[i+1].desc + "\n";
        ss << kFileDelim << "\n";
    }
    ss << kFileDelim << kFileDelim;
    return ss.str();
}


// Creates a stream to write to a .TeX File
//  @Returns a Stream to Content of the Doc File
std::string importTests(TestFile tf)
{
    std::stringstream ss;

    // Cycle through All Tests
    for(int i = 0; i < tf.tests.size(); i++)
    {
        std::string test;
        // Check for what type of TestSlide to use
        if(tf.tests[i].img)
        {
            // Has image, use TestSlideA
            test = tTestPageA;

            std::string fLine, lLine;

            int numOfLines = _newlineCount(tf.tests[i].ffn());
            for(int j = 1; j <= numOfLines; j += 15)
            {
                std::stringstream tmpSS;


                tmpSS << j << " " << std::min( j + 14 +
                                        (j + 15 == numOfLines),
                                            numOfLines) << "\n";
                tmpSS.clear();  // Reset to allow you to extract from stream
                tmpSS >> fLine >> lLine;

                // Insert Lines Numbers Into
                test = _strReplace(test, "%FL%", fLine);
                test = _strReplace(test, "%LL%", lLine);
            }
        }
        else
        {
            // Has no image, use TestSlideB
            test = tTestPageB;

            // Make Sure *.out file Exists First
            if( !(std::ifstream(tf.tests[i].out().c_str())))
                continue;   // Skip if it doesn't exist

            std::string tmp[4];

            // Length Of Test File
            int nol1 = _newlineCount(tf.tests[i].ffn());
            int nol2 = _newlineCount(tf.tests[i].out());
            for(int j = 1, k = 1; k <= nol2; k += 15)
            {
                std::stringstream tmpSS;

                tmpSS << j << " " << std::min(j+ 14, nol1) << "\n";
                tmpSS << k << " " << std::min(k+ 14, nol2) << "\n";

                tmpSS.clear();  // Reset to allow you to extract from stream

                // Retreive the Numbers again
                for(int z = 0; z < 4; z++)
                    tmpSS >> tmp[z];

                // Insert Lines Numbers Into
                test = _strReplace(test, "%FL1%", tmp[0]);
                test = _strReplace(test, "%LL1%", tmp[1]);
                test = _strReplace(test, "%FL2%", tmp[0]);
                test = _strReplace(test, "%LL2%", tmp[1]);

                // So that last few lines are repeated of the *.test
                //  on remaining slides if the *.out file has more
                //  lines to print be displayed.
                j = std::max( std::min(j + 14, nol1 - 15), j);
            }
        }

        // Insert Test Name and Description into Test
        test = _strReplace(test, "%TN%", tf.tests[i]. name);
        test = _strReplace(test, "%DESC%", tf.tests[i].desc);

        // Add To Stream
        ss << test;
    }

    return ss.str();
}
