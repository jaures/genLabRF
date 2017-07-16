/*

Include Definition for Functions Related to the Testing
of the Project

*/

// Includes
#include "../include/genlab.h"



// Run the Test Wizard and Generate Test Documentation
int handleTestArg(int c = 2, char*[] vals = 0)
{
	TestFile tf;
	int exitCode = ( (checkProjInit() && tf.load()) ? InitError : NoError );
	
	// Check for Error
	if(exitCode){ return (exitCode | TestError);}
	
	std::cout << "Test Wizard"
	int pre = 2;
	std::string line;
	
	do
	{
		if(pre < c )
		{
			// Set line to the commandline values
			line = vals[pre++];
		}
		
		if(line == "\\list")
		{
			// Print Out all Tests
			std::cout << "Total Count of Tests: " << tf.tests.size(); 
			for(int i = 0; i < tf.tests.size(); i++)
			{
				std::cout << "\nTest-" << i + 1
						<< tf.tests[i].name;
			}
		}
		else if(line.substr(0, 6) == "\\list " && line.size() > 6)
		{
			// Print Out Specific Test
			int tmp = 0;
			std::stringstream tmpSS;
			try
			{
				tmpSS << line.substr(6, line.size() - 6);
				tmpSS.clear();
				tmpSS >> tmp;
			}
			catch
			{
			}
			
			if( tmp || (tmp > tf.tests.size() ))
			{
				std::cout << "<Error> Invalid Input. Was not able to parse request.\n";
			}
			else
			{
				std::cout << "\nTest-" << i + 1 << ": "
						<< tf.tests[i].name 
						<< "\n\nContent: \n"
						<< tf.tests[i].content;
			}
			
			line = "yes";
		}
		else if(line == "\\clear")
		{
			// Clear All Tests 
			tf.tests.clear();
			
			line = "yes";
		}
		else if(line.substr(0, 7) == "\\clear " && line.size() > 7)
		{
			// Clear Specific Test
			int tmp = 0;
			std::stringstream tmpSS;
			try
			{
				tmpSS << line.substr(6, line.size() - 6);
				tmpSS.clear();
				tmpSS >> tmp;
			}
			catch
			{
			}
			
			if( tmp || (tmp > tf.tests.size() - 1))
			{
				std::cout << "<Error> Invalid Input. Was not able to parse request.\n";
			}
			else
			{
				tf.tests.erase(tmp - 1);
			}
			line = "yes";
			
		}
		else if( std::string("yesYesYES").find(line) != std::string::npos)
		{
			// Prompt user for what to do next
			std::cout << "\nTest Wizard Menu\n================";
			<< "\n\tTypet'\\list' to list all tests"
			<< "\n\t\t\t'\\list #' to list information about tests-#" 
			<< "\n\t\t\t'\\clear' to clear all tests"
			<< "\n\t\t\t'\\clear #' to clear tests-#"
			<< "\n\t\t\t\\q to continue to Testing" ;
			
			getline(std::cin, line);
		}
		else
		{
			// Add New Test
			std::cout << "Content for Test-" << tf.tests.size() + 1 
					<< "\nLines begining with '$' are sent to STDIN (leave a blank line to save entry and continue):\n";
			
			UnitTest ut(line, _getMultiLineInput(kMaxBuff));
			
			std::cout << "Test Overview:\n" << ut.info()
					<< "\n\nAccept and continue?(y/n): ";
			
			// Have user Review Test before Moving on
			std::string tmp;
			getline(std::cin, tmp);
			line = ((std::string("yesYesYES").find(tmp) != std::string::npos) ? "yes" : line );
		}
		
	}while( line != "\\q");
	
	
	// Write All the Tests to a file to run
	
	
	
	// Cycle Through and Run all Test and Prompt
	//	Whether or not to get images 
	std::cout << "Moving on to Testing...\n";
	for(int i = 0; i < tf.tests.size(); i++)
	{
		std::cout << "Testing " << tf.tests[i].name << "...\n";
		if(_checkCall("make test." + tf.tests[i].name))
		{
			// Make Command Failed to Run the Test
			std::cout << "\t[X]\tFailed while trying to run test.\n\n";
			exitCode |= TestError;
		}
		else
		{
			std::cout << "\t[/]\tSuccessfully ran test\n";
					<< "Add Image of Test? (y/n): ";
			
			// Prompt User Whether or not they want to create and image
			//	file for the test.
			getline(std::cin, line);
			if(std::string("yesYesYES").find(line) != std::string::npos)
			{
				if(_checkCall("import docs/" + tf.tests[i].name + ".eps"))
				{
					std::cout << "\t[/]\tImage Successfully Saved.\n";
					tf.tests[i].img = true;
				}
				else
				{
					std::cout << "\t[X]\t Failed to take an image of the Test.\n\n";
					exitCode |= TestError;
				}
			}
		}
	}
	
	return exitCode;
}