/*

Contains Templates for Creating Various Project Files
and System Commands

*/

// Includes
#include <iostream>
#include <string>

#include "../include/genlab.h"

// Helpful Message about functionality
 const std::string tHelp[]  = 
 {
	 "--init\t\tInitialize the Project Directory\n",
	 "Usage:\n\t--init <ProjectName> [file1 file2 ...]\n",
	 
	 "--add\t\tAdd new files to the Project Directory\n",
	 "Usage:\n\t--add [file1 file2 ...]\n",
	 
	 "--rem\t\tRemove a file from the Project Directory\n",
	 "Usage:\n\t--rem [file1 file2 ...]\n",
	 
	 "--build\t\tCompile the Project and produce an executable\n",
	 "Usage:\n\t--build\n",
	 
	 "--run\t\tRun the compiled Project executable\n",
	 "Usage:\n\t--run\n",
	 
	 "--test\t\tRun Test Wizard and test compiled Project\n"
	 "Usage:\n\t--test [test1 test2 ...]\n", 
	 
	 "--doc\t\tRun Documentary Wizard and generate a TeX File\n",
	  "Usage:\n\t--doc\n ",
	 
	 "--pkg\t\tPackage the Project Directory for submission\n",
	 "Usage:\n\t--pkg\n",
	 
	  "--info\t\tPrint information about current Project\n",
	 "Usage:\n\t--info\n",
	 
	  "--help\t\tPrint the help or help about a specific argument\n",
	 "Usage:\n\t--help [arg]\n"
 };

// Template For holding Project Header Information like
//	- Author Name
//	- Email
//	- Dates
//	- Tags
 //	- Desc
 const std::string tHeader = 
 "/*\n@author: %AUTHOR%\n"
 "@email: %EMAIL%\n"
 "%TAG%\n\n"
 "Description:\n%DESC%""\n*/";

// Template for Project Makefile
 const std::string tMakeFile =
 "# %PROJECT% Makefile\n"
"PRJCT=%PROJECT%\n\n"

"# Include Directory\n"
"IDIR:=include/\n\n"

"# Other Include Directories\n"
"OIDIR:=%OIDIRS%\n\n"

"# Header Files\n"
"INCS=$(wildcard $(IDIR)*.h)\n\n"

"# Source Directory\n"
"SDIR:=srcs/\n\n"

"# Source Files\n"
"SRCS=$(wildcard $(SDIR)*.cpp)\n"

"# Docs Directory\n"
"DDIR:=docs/\n\n"

"# Build Directory\n"
"BDIR:=bin/build/\n\n"

"# Pack Directory\n"
"PDIR:=bin/package/\n\n"

"# Directories to Package\n"
"PKGS=$(IDIR) $(OIDIR) $(SDIR) $(DDIR) $(BDIR) $(TDIR)\n\n"

"# Test Directory\n"
"TDIR:=bin/test/\n"

"# C++ Compiler\n"
"CXX=g++\n"

"# C++ Flags to Pass to Compiler\n"
"CXXFLAGS=-pedantic -Wall -I $(IDIR) $(O_IDIRS)\n"

"# Other C++ Flags\n"
"OFLAGS=%OFLAGS%\n\n"

"# Output Flag\n"
"OUT:= -o $(BDIR)\n\n"

"# TEX Compiler\n"
"TEX=latex\n\n"

"# DVI to PS Program\n"
"DTPS=dvips\n\n"

"# PS to PDF Program\n"
"PSTPDF=ps2pdf\n\n"

"# DVI to PDF Program\n"
"DTP=dvipdf\n\n"

"# Make sure make does not operate files\n"
"# with reserved targets\n"
".PHONY: all project prjct proj pro clean run docs pack backup recover\n\n"

"all: project docs pack"
"\n\t$(info Making $(PRJCT) and Docs...)\n\n\n"

"project: $(BDIR)$(PRJCT)\n"
"prjct: $(BDIR)$(PRJCT)\n"
"proj: $(BDIR)$(PRJCT)\n"
"pro: $(BDIR)$(PRJCT)\n\n\n"

"%$(PRJCT): $(INCS) $(SRCS)"
"\n\t$(warning On Error try running 'make clean' first)"
"\n\t$(info compiling files: $?)"
"\n\t$(CXX) $(SRCS) $(OFLAGS) $(OIDIR) $(CXXFLAGS) -o $@\n\n\n"

"clean:"
"\n\trm -rf include/*.gch"
"\n\trm -rf bin/build/*\n\n\n"

"run: $(BDIR)$(PRJCT)"
"\n\t./$<\n\n\n"

"docs: $(DDIR)$(PRJCT).tex $(SRCS) $(INCS) "
"\n\tlatex -output-directory $(DDIR) $<"
"\n\tdvipdf $(DDIR)$(PRJCT).dvi $(DDIR)$(PRJCT).pdf\n\n\n"

"pack: $(INCS) $(SRCS) $(DDIR)$(PRJCT).pdf"
"\n\ttar czvf $(PDIR)$(PRJCT)_pkg.tgz $(PKGS) Makefile"
"\n\tcp -uvf $(DDIR)$(PRJCT).pdf $(PDIR)\n\n\n"

"%.test: $(TDIR)%.test"
"\n\tsh $< > $(DDIR)$(@:.test=.out"
"\n\tcat $(DDIR)$(@:.test=.out)"

"backup: pack"
"\n\ttar czvf $(PDIR)/.backup.tgz $(PDIR)*\n\n\n";


// Template for Project Latex Document
 const std::string tDocFile =
 // Import Packages
"\\documentclass{ffslides}\n"
"\\ffpage{25}{\\numexpr 16/9}\n"
"\\usepackage{fancyvrb}\n"
"\\usepackage{enumitem}\n"
"\\usepackage[T1]{fontenc}\n"
"\\usepackage{underscore}\n"
"\\usepackage{color}\n"
"\\usepackage{listings}\n"
"\\usepackage{newclude}\n\n"

// Add Implementation Page Command
"\\newcommand{\\implpage}[5]\n{%\n\t"
"\\normalpage{Implementation of #1}\n\t{%\n\t\t"
"#3\n\t\t"
"\\lstinputlisting[language=C++, firstnumber=#4, firstline=#4, "
"lastline=#5]\n\t\t{#2}\n\t}\n}\n\n"

// Add Test Page Commands
"\\newcommand{\\testpagea}[4]\n{%\n\t"
"\\normalpage{Test: #1}\n\t{%\n\t\t"
"\\ctext{0}{0}{0.24}\n\t\t{%\n\t\t\t"
"#2\\\\\\\\%\n\t\t\tTest:\n\t\t\t"
"\\lstinputlisting[language=C++, firstnumber=#3, firstline=#3, "
"lastline=#4]\n\t\t\t{../bin/test/#1.test}\n\t\t}\n\t\t"
"\\putfig{0.26}{0}{0.68}{#1}\n\t}\n}\n\n"

"\\newcommand{\\testpageb}[6]\n{%\n\t"
"\\normalpage{Test: #1}\n\t{%\n\t\t"
"\\ctext{0}{0}{0.24}\n\t\t{%\n\t\t\t"
"#2\\\\\\\\%\n\t\t\tTest:\n\t\t\t"
"\\lstinputlisting[language=C++, firstnumber=#3, firstline=#3, "
"lastline=#4]\n\t\t\t{../bin/test/#1.test}\n\t\t}\n\t\t"
"\\ctext{0}{0}{0.24}\n\t\t{%\n\t\t\t"
"%\n\t\t\tResults:\n\t\t\t"
"\\lstinputlisting[language=C++, firstnumber=#5, firstline=#5, "
"lastline=#6]\n\t\t\t{#1.out}\n\t\t}\n\t\t"
"\n\t}\n}\n\n"

// Begin the Document
"\\begin{document}\n\n"

// Set Listings Style
"\\lstset{\n\t"
"frame=single,\n\tkeepspaces=true,\n\t"
"columns=flexible,\n\tbreaklines=true,\n\t"
"breakatwhitespace=true,\n\tnumbers=left,\n\t"
"numbersep=5pt,\n\tnumberstyle=\\tiny\\color{gray},\n\t"
"keywordstyle=\\color{blue},\n\tstringstyle=\\color{red},\n\t"
"showstringspaces=false,\n\tcommentstyle=\\color{green}\n}\n\n"

// Specification Page
"\\normalpage{Specification}\n"
"{%Description of the Expected Functionality\n%SPECS%\n}\n\n"

// Analysis Page
"\\normalpage{Analysis}\n{%Input, Outputs, and Processes\n\t"
"\\qi[\\textsc{\\textbf{Inputs:}}]{ \\\\\n%INPUTS%\t}\n\n\t"
"\\qi[\\textsc{\\textbf{Process:}}]{\n\t\\begin{enumerate}[nolistsep]\n"
"{PROCESSES}\t\\end{enumerate}\n\t}\n\n\t"
"\\qi[\\textsc{\\textbf{Outputs:}}]{ \\\\\n%OUTPUTS%\t}\n}\n\n"

// Design Page
"\\normalpage{Design}\n{\n\t"
"\\begin{description}[nolistsep]\n%DESG%\t\\end{description}\n}\n\n"

// Implementation and Test Pages Insert
"%IMPL%\n\n%TESTS%\n\n"

"\\end{document}";


// Template for Latex Implementation Slide Command
 const std::string tImplmntPage =
"\\implpage{%FN%}{%FFN%}{%DESC%}{%FL%}{%LL%}\n\n";


// Template for Latex Test Slide A Command with an Image
 const std::string tTestPageA = 
 "\\testpagea{%TN%}{%DESC}}{%FL%}{%LL%}\n\n";


// Template for Latex Test Slide B Command with no Image
 const std::string tTestPageB =
 "\\testpageb{%TN%}{%DESC%}{%FL1%}{%LL1%}"
 "{%FL2%}{%LL2%}\n\n";


// Template for C++ *.h Header File
 const std::string tHFile
 "/*\n%HEADER%\n*/\n\n"
 "// Include Guard\n#ifndef __%HFILE%\n\t#define __%HFILE%\n\n"
 "// Include Dependencies\n%INCLUDE%\n\n"
 "// Extern Variables, Structs ands Other Forward Declarations\n\n"
 "// Close Include Guard\n#endif";


// Template for C++ *.cpp Source File
 const std::string tCPPFile = 
 "%HEADER%\n\n"
 "// Include Dependencies\n%INCLUDE%\n\n"
 "// Global Declarations/Definitions\n\n"
 "/* Source Code */";


// Template for  a C++ Main Function that prints 'Hello World'
 const std::string tMainFunct = 
 "// Main Function\n"
 "int main(int argc, char** argv[])\n"
 "{\n\t/* Source Code */\n\tstd::cout << \"Hello World!\n\";\n\treturn 0;\n}";


// Template for Project Directory Structure
 const std::string tProjectDirectories[] = 
 {
	 "%PROJECT%",
	 "%PROJECT%/bin",
	 "%PROJECT%/bin/build",
	 "%PROJECT%/bin/pkgs",
	 "%PROJECT%/bin/tests",
	 "%PROJECT%/docs",
	 "%PROJECT%/include",
	 "%PROJECT%/srcs"
 };

 
// Template for the  Shell Test File 
 const std::string tTestFile = 
 "#!/usr/bin/env bash\n\n"
 "echo \"Test %TN%:\n[INPUTS]:\n%STDIN%\n[OUTPUTS]:\"\n"
 "echo \"%STDIN%\" | bin/build/%PROJECT%"; 
