#ifndef CONNECTOR_H   // remember to change file name
#define CONNECTOR_H

#include "Component.h" // remember to change file name before compiling

class Connector : public Component
{
    protected:
        Component* leftChild;
        Component* rightChild;
    
    public:
        virtual void run();
}

#endif