#ifndef AND_H   // remember to change file name
#define AND_H

#include "Connector.h"  // remember to change file name before compiling
using namespace std;

class And : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        
    public:
        And(Component* left, Component* right);
        void run();
};

#endif