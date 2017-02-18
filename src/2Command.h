#ifndef COMMAND_H   // remember to change file name
#define COMMAND_H

#include <string>
#include <vector>

#include "1Component.h" 

class Command : public Component
{
    protected: 
        string userCommand;
        vector<char*> flags; // there may be multiple flags per command
    
    public:
        Command();
        Command(string userCmd);
        Command(string userCmd, vector<string> userFlags);
        bool run();
};

#endif