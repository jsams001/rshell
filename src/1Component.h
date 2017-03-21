#ifndef COMPONENT_H    // remember to change file name
#define COMPONENT_H

#include <iostream>
using namespace std;

class Component
{
    public:
        virtual bool run() = 0;
        virtual string getUserCommand() = 0;
        virtual void setFD(int, int) = 0;
        virtual int getOutputFD() = 0;
        virtual int getInputFD() = 0;
};

#endif