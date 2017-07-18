/*

Include Definition for Functions Related to the Creation
of Project Documentation

*/

// Includes
#include "../include/genlab.h"



// Run the Documentation Wizard and Produce a Document
int handleDocArg()
{
    GenFile gf;
    int exitCode = ( (checkProjInit() && gf.load()) ? InitError : NoError );

    // Check for Error
    if(exitCode)
        return exitCode;

    std::stringstream ss;
    std::string content, line;

    std::cout << "Run Documentation Wizard? (y/n): ";
    getline(std::cin, line);
    // Run Doc Wizard if yes
    if( std::string("yesYesYES").find(line) != std::string::npos)
    {
        ss << docFileInit(gf);

        // If no .testFile exists, prompt user to run it
        //  the Test Wizard First
        if( !checkTestsInit())
        {
            std::cout << "Run Test Wizard? (y/n): ";

            getline(std::cin, line);
            // Run Test Wizard if yes
            if( std::string("yesYesYES").find(line) != std::string::npos)
            {
                exitCode |= handleTestArg(2,0);

                // Check for Error
                if(exitCode)
                    return exitCode;
            }
        }

        std::cout << "Import Test? (y/n): ";
        getline(std::cin, line);

        // Import Tests for Test Slides if yes
        if( std::string("yesYesYES").find(line) != std::string::npos)
        {
            TestFile tf;

            exitCode |= (tf.load() ? NoError : TestError);

            std::stringstream tss;
            tss << importTests(tf);

            exitCode |= (_strReplaceI(content, "%TESTS%", tss.str()));
        }

        content = tDocFile;

        // Insert Project Specifications
        content = _strReplace(content, "%SPECS%", gf.prjDesc);

        // Cycle Through and Build Design Content
        //  And Implementation Slides
        std::string designSlide = "";

        for(int i = 0; i < gf.projFiles.size(); i++)
        {
            std::string implSlide, desg;

            getline(ss, desg);

            // Check for Error/Bad Formatting
            if (desg != kFileDelim)
            {
                exitCode |= DocError;
                break;
            }
            getline(ss, desg);
            designSlide += desg;

            if(gf.projFiles[i].dir == "srcs/" || gf.projFiles[i].dir == "include/")
            {
                std::cout << "Implementation of " << gf.projFiles[i].name << ":\n\t"
                        << "(leave a blank line to save entry and continue):\n";


                std::stringstream tmpSS;

                // Get the number of lines of the file
                int numOfLines = _newlineCount(gf.projFiles[i].dir + gf.projFiles[i].name);

                // Add the First Page of the Implementation Slide
                implSlide = _strReplace(tImplmntPage, "%DESC%", implSlide);

                // Start Cycling through each file to create its Implementation Slides
                for(int j = 1; j <= numOfLines; j += 15)
                {
                    std::string fLine, lLine;

                    // Add First line and Last line
                    tmpSS << j << " " << std::min( j + 14, numOfLines);
                    tmpSS.clear();  // Reset to allow you to extract from stream
                    tmpSS >> fLine >> lLine;

                    // Place First and Last line variables into Template
            std::string dummy = _strReplace( implSlide, "%FL%", fLine);
                    exitCode |= (_strReplaceI( dummy,"%LL%", lLine) ? NoError : DocError);

                    // Append New Slide to the Documentation
                    exitCode |= (_strReplaceI(content, "%IMPL%", implSlide + "\n%IMPL%")
                                ? NoError : DocError);

                    // Reset the implSlide so following pages do not have
                    //  A Description
                    implSlide = _strReplace(tImplmntPage, "%DESC%", "");
                }

                // Add File Name and Full File Name
                exitCode |= (_strReplaceI(content, "%FN%", gf.projFiles[i].name)
                                ? NoError : DocError);
                exitCode |= (_strReplaceI(content, "%FFN%", gf.projFiles[i].ffn())
                                ? NoError : DocError);
            }

            // At this point, content has all the Implementation slides
            //  and the Design Slide content has been compiled,
            //  ready to be inserted.

            // Insert into Template the DesignSlideContent
            exitCode |= (_strReplaceI(content, "%DESG%", designSlide) ?
                        NoError : DocError);
        }

        // Insert Design Content
        //  *NOTE: No Guarentee all of it will fit on the slide
        content = _strReplace(content, "%DESIGN%", designSlide);


        // Cycle Through and Create Implementation Slides


    }


    // Run Make docs to Create Documentation
    if(! exitCode )
        exitCode |= (_checkCall("make docs") ? DocError : NoError);

    return exitCode;

}
