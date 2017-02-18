#ifndef AND_H   // remember to change file name
#define AND_H

#include "1Component.h"
#include "2Connector.h"  // remember to change file name before compiling

class And : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        
    public:
        And();
        And(Component* left, Component* right);
        bool run();
};

#endif