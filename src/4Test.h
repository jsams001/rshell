#ifndef TEST_H
#define TEST_H

#include <string>
#include <vector>

#include "2Command.h"

class Test : public Command
{
    protected:
        string userCommand;
        vector<char*> flags;
        int inputFD;    // input file descriptor used for redirection
        int outputFD;   // output file descriptor used for redirection
        
    public:
        Test();
        Test(string userCmd);
        Test(string userCmd, vector<string> userFlags);
        bool run();
        void setFD(int in, int out);
        string getUserCommand();
        int getOutputFD();
        int getInputFD();
};

#endif