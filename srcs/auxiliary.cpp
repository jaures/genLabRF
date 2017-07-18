/*

Contains Useful Auxiliary Functions

*/

#include "../include/genlab.h"


const int kMaxBuff = 256;

// Perform a system call
//  @Return the exit code
int _checkCall(std::string call, bool display)
{
    // Add to Append stderr to stdout results
    call += " 2>&1";

    FILE* call_stream = popen(call.c_str(), "r");

    char buff[kMaxBuff];
    std::string out = "";

    if(!call_stream)
        return -1;

    while(std::fgets(buff, kMaxBuff, call_stream) != NULL)
    {
        out += buff;
    }

    if(display)
        std::cout << out << "\n";

    // Might need to be right shifted 8 bits to get
    //  actual exit code of the subprocess
    return pclose(call_stream);
}


// Takes a the first argument, and replaces all instances of
//  the second argument with the third argument.
//  @Return the new string
std::string _strReplace(std::string str, std::string ori, std::string rep)
{
    int p = str.find(ori);

    while( p != std::string::npos)
    {
        // Remove first instance of @param ori and insert
        //  into the location @param rep into @param str
        str = str.substr(0,p) + rep +
            str.substr(p + ori.size(), str.size() - p - ori.size());

        // Look for Next Instance of @param ori in @param str
        p = str.find(ori);
    }
}


// Takes a the first argument, and replaces all instances of
//  the second argument with the third argument in place.
//  @Return number of swaps made
int _strReplaceI(std::string& str, std::string ori, std::string rep)
{
    int p = str.find(ori);
    int cnt;

    for(cnt = 1; p != std::string::npos; cnt++)
    {
        // Remove first instance of @param ori and insert
        //  into the location @param rep into @param str
        str = str.substr(0,p) + rep +
            str.substr(p + ori.size(), str.size() - p - ori.size());

        // Look for Next Instance of @param ori in @param str
        p = str.find(ori);
    }

    return cnt;
}


// Count Number of New Lines in a string
int _newlineCount(std::string str)
{
    std::string tmp = str;

    // Count the number of times
    return _strReplaceI(str, "\n", "");
}


// Count Number of New Lines in a file
int _newlineCountF(std::string file)
{
    std::ifstream fr(file.c_str());

    // Check For Error
    if( !fr.good() )
        return false;

    int cnt;
    char buff[kMaxBuff];

    for( cnt = 1; !fr.eof(); cnt++)
    {
        fr.getline(buff, kMaxBuff);
    }

    fr.close();

    return cnt;
}

// Get Multilined User Input from std::cin
std::string _getMultiLineInput(int lineLimit)
{
    std::string lines, line;
    lines = "";

    while( lineLimit > 0)
    {
        getline(std::cin, line);

        if(line.empty())
        {
            break;
        }
        else
        {
            lines += line + '\n';
        }

        lineLimit--;
    }

    return lines;
}

// Get Multilined User Input from an std::ifstream, @param fr
std::string _getMultiLineInputF(std::ifstream& fr, int lineLimit, std::string delim)
{
    std::string lines, line;
    lines = "";

    while( lineLimit > 0)
    {
        getline(fr, line);

        if(line.empty() || line == delim)
        {
            break;
        }
        else
        {
            lines += line + '\n';
        }

        lineLimit--;
    }

    return lines;
}
