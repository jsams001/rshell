#ifndef COMMAND_H   // remember to change file name
#define COMMAND_H

#include Component.h // remember to change file name before compiling

class Command : public Component
{
    private:
        string userCommand;
        bool cmdSucceed;
    
    public:
        void run();
};

#endif