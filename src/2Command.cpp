#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "2Command.h"

Command::Command() {} // default constructor

Command::Command(string userCmd) // constructor with only command as constructor
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

Command::Command(string userCmd, vector<string> userFlags) // constructor with
                                                    // both command and flag
{
    this->userCommand = userCmd;

    for (unsigned int i = 0; i < userFlags.size(); ++i)
    {
        char* temp = new char(100);
        strcpy(temp, userFlags[i].c_str());
        flags.push_back(temp);
    }
}

bool Command::run()
{
    if (userCommand == "exit")
    {
        exit(EXIT_SUCCESS);
    }
    
    bool returnedVal = true;
    
    char* inputs[500];
    char* temp = new char[100];
    strcpy(temp, userCommand.c_str());
    inputs[0] = temp;
    if (flags.size() != 0)
    {
		for (unsigned int i = 1; i <= flags.size(); ++i)
		{
			inputs[i] = flags[i - 1];
		}
    }
    inputs[this->flags.size() + 1] = NULL; // execvp() requires a char array  
                                           //terminated by a NULL pointer
                                           
    pid_t pid = fork();
    if (pid == -1) // this is for the case that fork fails
    {
        returnedVal = false;
        perror("fork() has failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // child pid is 0
    {
        if (execvp(userCommand.c_str(), inputs) == -1)
        {
            returnedVal = false;
            perror("execvp() has failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0) // parent pid is greater than 0
    {
        int status; // passed into waitpid
        if (waitpid(pid, &status, 0) == -1) // waitpid forces parent to wait 
                                            // for child process
        {
            perror("wait() has failed");
        }
        if (WIFEXITED(status) == 1)
        {
            if (WEXITSTATUS(status) != 0)
            {
                returnedVal = false;
            }
        }
    }
    
    return returnedVal;
}
