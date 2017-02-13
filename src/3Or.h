#ifndef OR_H   // remember to change file name
#define OR_H

#include "Connector.h"  // remember to change file name before compiling

class Or : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        
    public:
        void run();
}