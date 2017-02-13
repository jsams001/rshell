#ifndef CONNECTOR_H   // remember to change file name
#define CONNECTOR_H

#include "Component.h" // remember to change file name before compiling
using namespace std;

class Connector : public Component
{
    protected:
        Component* leftChild;
        Component* rightChild;
    
    public:
        Connector();
        Connector(Component* left, Component* right);
        virtual void run();
}

#endif