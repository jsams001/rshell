#ifndef AND_H   // remember to change file name
#define AND_H

#include "Connector.h"  // remember to change file name before compiling

class And : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        
    public:
        void run();
}