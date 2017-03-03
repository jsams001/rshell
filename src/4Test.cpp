#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "4Test.h"

Test::Test() {} // default constructor

Test::Test(string userCmd) // constructor with only raw user input
{
    size_t found = userCmd.find(" ");
    
    if (found == string::npos)
    {
        this->userCommand = userCmd;
    }
    else
    {
        string tempUserCmd = userCmd; // separate the command from the flags
        this->userCommand = tempUserCmd.substr(0, found);
        tempUserCmd.erase(0, found + 1);
        char* c_strTempUserCmd = new char[500];
        strcpy(c_strTempUserCmd, tempUserCmd.c_str());
        char* temp = strtok(c_strTempUserCmd, " ");
        
        while (temp != NULL)
        {
            flags.push_back(temp);
            temp = strtok(NULL, " ");
        }
    }
}

Test::Test(string userCmd, vector<string> userFlags) // constructor with flags
{                                                    // and command
    this->userCommand = userCmd;

    for (unsigned int i = 0; i < userFlags.size(); ++i)
    {
        char* temp = new char(100);
        strcpy(temp, userFlags[i].c_str());
        flags.push_back(temp);
    }
}

bool Test::run()
{
    bool returnedVal; // bool to be returned
    string flag; // -e, -f, or -d
    char* filePath;
    struct stat sb; // stat buffer
    
    if (flags.size() == 1) // user only specifies file path
    {
        flag = "-e";
        filePath = flags[0];
    }
    else if (flags.size() == 2) // user specifies flag and file path
    {
        flag.assign(flags[0], 2);
        filePath = flags[1];
    }
    else // invalid input
    {
        perror("Invalid input");
        exit(EXIT_FAILURE);
    }

    if (stat(filePath, &sb) == 0)
    {
        if (flag == "-e") // checks if filepath exists
        {
            returnedVal = true;
        }
        else if (flag == "-f") // checks if filepath is a regular file
        {
            returnedVal = S_ISREG(sb.st_mode);
        }
        else if (flag == "-d") // checks if filepath is a directory
        {
            returnedVal = S_ISDIR(sb.st_mode);
        }
        else
        {
            cout << "Invalid input" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        returnedVal = false; // false if path does not exist
    }
    
    if (returnedVal) // prints the required (True) or (False)
    {
        cout << "(True)" << endl;
    }
    else
    {
        cout << "(False)" << endl;
    }
    
    return returnedVal;
}