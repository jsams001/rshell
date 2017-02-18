#ifndef COMPONENT_H    // remember to change file name
#define COMPONENT_H

#include <iostream>
using namespace std;

class Component
{
    public:
        virtual bool run() = 0;
};

#endif