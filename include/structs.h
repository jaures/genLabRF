/*

Useful Struts for Dealing with Abstraction of
Project Components

*/

// Include Guard
#ifndef _structs_h
#define _structs_h

//Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <cstdio>

#include "auxiliary.h"


// Delimiter for Seperating and Identifiying Sections '%#%'
extern const std::string kFileDelim;


// Structures

// Struct for Holding Project File Information
 struct ProjFile
{
    std::string name;
    std::string desc;
    std::string content;
    std::string dir;

    ProjFile()
    {
        name = desc = content = dir = "";
    }

    ProjFile(std::string _name, std::string _desc, std::string _content, std::string _dir = "")
    {
        name    = _name;
        desc        = _desc;
        content     = _content;
        dir         = _dir;
    };

    std::string info()
    {
        return (name + "\nDescription:\n" + desc);
    };

    std::string ffn()
    {
        return (dir + name);
    };

    // Write ProjFile Struct to File
    bool write(std::string _dir = "")
    {
        // Check For Default Value
        if (_dir == ""){ _dir = dir;}

        std::fstream fw( (_dir + name).c_str(),
            std::fstream::in | std::fstream::out);

        if( !fw.good() || fw.peek() == EOF)
            return false;

        fw << content;

        fw.close();

        return true;
    };
};


// Struct for Holding Parsed genFile Information
 struct GenFile
{
    std::string prjName;
    std::string prjAuthor;
    std::string prjEmail;
    std::string prjTag;
    std::string prjDesc;

    std::vector< ProjFile > projFiles;

    GenFile()
    {
        prjName =
            prjAuthor =
            prjEmail =
            prjTag =
            prjDesc = "";
    }

    GenFile( std::string _name, std::string _author, std::string _email,
            std::string _tag, std::string _desc)
    {
        prjName     = _name;
        prjAuthor   = _author;
        prjEmail    = _email;
        prjTag      = _tag;
        prjDesc     = _desc;
    }

    GenFile(std::string file)
    {
        load(file);
    };

    // Write GenFile Struct to File
    bool write(std::string _dir = "")
    {
        // File Writer For Creating .genFile
        std::ofstream fw( (_dir + ".genFile").c_str(),
                        std::ofstream::out | std::ofstream::trunc );

        // Check For Error
        if(!fw.good())
            return false;

        fw << prjName + '\n';
        fw << prjAuthor + '\n' ;
        fw << prjEmail + '\n';
        fw << prjTag + '\n';
        fw << kFileDelim << '\n';
        fw << prjDesc;


        for(int i = 0; i < projFiles.size() && fw.good(); i++)
        {
            fw << kFileDelim << '\n';
            fw << projFiles[i].name << '\n' << projFiles[i].desc
                << '\n' << projFiles[i].content << '\n'
                << projFiles[i].dir << '\n';
        }

        // Check For Error
        if( !fw.good() )
            return false;

        // Mark the End of the File
        fw << kFileDelim << kFileDelim;

        fw.close();

        return true;
    };

    // Load GenFile Struct from File
    bool load(std::string file = ".genFile")
    {
        // Return False if  there  has already
        //  been an attempt to load a .genFile.
        //  projFiles must be cleared first to reuse
        //  an loaded GenFile.
        if(!projFiles.empty())
            return false;

        // File Reader For Loading .genFile
        std::ifstream fr( file.c_str() );

        // Check For Error
        if(!fr.good())
            return false;

        getline(fr, prjName);
        getline(fr, prjAuthor);
        getline(fr, prjEmail);
        getline(fr, prjTag);

        // Error Checking
        getline(fr, prjDesc);
        if(prjDesc != kFileDelim)
            return false;
        else
            prjDesc = "";

        std::string tmp;
        do{
            getline(fr, tmp);
            prjDesc += tmp + "\n";
        }while(!prjDesc.empty());

        // Error Checking
        getline(fr, tmp);
        if( tmp != kFileDelim )
            return false;

        getline(fr, tmp);

        while(fr.good() && tmp != (kFileDelim + kFileDelim))
        {
            if(tmp.empty())
            {
                getline(fr, tmp);
            }
            else
            {
                // Error Check
                if(tmp != kFileDelim)
                    return false;

                ProjFile prj;

                getline(fr, prj.name);

                getline(fr, prj.desc);

                getline(fr, prj.content);

                getline(fr, prj.dir);

                getline(fr, tmp);
                projFiles.push_back(prj);
            }
        }
        fr.close();
    };



    // Create All the Project Files
    bool gen(std::string dir = "")
    {
        for( int i = 0; i < projFiles.size(); i++)
        {
            if( !projFiles[i].write(dir) )
                return false;
        }

        return true;
    };

    // Get information for headers about the Project
    std::string hInfo()
    {
        return ("Author:\t"     + prjAuthor +
                "\nEmail:\t"    + prjEmail +
                "\nTag:\t\t"    + prjTag);
    };

    // Get Header Information as well as the project description
    std::string info()
    {
        return hInfo() + "\nDescription:\n" + prjDesc;
    };
};


// Struct for All Necessary Information for a Unit Test
 struct UnitTest
{
    std::string name;
    std::string content;
    std::string stdin;
    bool img;

    // Initialize All the Unit Test Members
    UnitTest(std::string _name, std::string _content, std::string _stdin)
    {
        name = _name
        content = _content;
        stdin = _stdin;
        img = false;
    }

    // Return the Expected Location of Ouput File
    std::string out()
    {
        return "docs/" + name + ".out";
    }

    // Returns the Full File Name of the Unit Test
    //  File, Including its Path
    std::string ffn()
    {
        return "bin/tests/" + name + ".test";
    }

    // Write the UnitTest Struct to File
    bool write(std::string dir = "bin/tests/")
    {
        std::ofstream fw( (dir + name).c_str(),
                        std::ofstream::out | std::ofstream::trunc );

        if( !fw.good() )
            return false

        fw << "#!/usr/bin/env bash\n\necho \"Test "
            << name << ":\n[INPUT]:\n" << stdin
            << "\n[OUTPUT]:\"\necho \"" << stdin
            << "\" | bin/build/*";

        fw.close();
    }

    // Return Information about Unit Test
    std::string info()
    {
        return "Name: " + name + "\nContent:\n" + content;
    }
};


// Struct for Holding Parsed Test File Information
 struct TestFile
{
    std::string prjName;

    std::vector< UnitTest > tests;

    TestFile(std::string file)
    {
        load(file);
    }

    // Write TestFile Struct to File
    bool write(std::string dir = "bin/tests/")
    {
        // File Writer For Creating .testFile
        std::ofstream fw( (dir + ".testFile").c_str(),
                        std::ofstream::out | std::ofstream::trunc );

        // Check For Error
        if(!fw.good())
            return false;

        fw << prjName << '\n'

        for(int i = 0; i < tests.size() && fw.good(); i++)
        {
            fw << kFileDelim << '\n';
                << tests[i].name << "\n";
                << kFileDelim << '\n';
                << tests[i].content << "\n";
                << kFileDelim << '\n';
                << tests[i].stdin << "\n";
        }

        // Check For Error
        if( !fw.good() )
            return false;

        // Mark the End of the File
        fw << kFileDelim << kFileDelim;

        fw.close();

        return true;
    }


    // Load TestFile Struct from File
    bool load(std::string file = "bin/tests/.testFile")
    {
        // Return False if  there  has already
        //  been an attempt to load a .testFile.
        //  tests must be cleared first to reuse
        //  an loaded TestFile.
        if(!tests.empty())
            return false;

        // File Reader For Loading .genFile
        std::ifstream fr(file.c_str());

        // Check For Error
        if(!fr.good())
            return false;

        std::string tmp;
        getline(fr, prjName);

        // Error Checking
        getline(fr, tmp);
        if(tmp != kFileDelim)
            return false;

        getline(fr, tmp);

        while(fr.good() && tmp != (kFileDelim + kFileDelim))
        {
            if(fr.empty())
            {
                getline(fr, tmp);
            }
            else
            {
                // Error Check
                if(tmp != kFileDelim)
                    return false;

                UnitTest utest;

                utest.name = tmp;

                utest.content = _getMultiLine(fr, kFileDelim);

                utest.stdin = _getMultiLine(fr, kFileDelim);

                getline(fr, tmp);
                tests.push_back(utest);
            }
        }
        fr.close();
    }

    // Writes all the UnitTest Shell Scripts
    bool writeTests(std::string dir = "bin/tests/")
    {
        for( int i = 0; i < tests.size(); i++)
        {
            if( !tests[i].write())
                return false;
        }
        return true;
    }
};

// Close Include Guard
#endif
