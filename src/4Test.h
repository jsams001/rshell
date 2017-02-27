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
        
    public:
        Test();
        Test(string userCmd);
        Test(string userCmd, vector<string> userFlags);
        bool run();
};

#endif