#ifndef OR_H   // remember to change file name
#define OR_H

#include "1Component.h"
#include "2Connector.h"

class Or : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        
    public:
        Or();
        Or(Component* left, Component* right);
        bool run();
};

#endif