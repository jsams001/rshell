#ifndef CONNECTOR_H   // remember to change file name
#define CONNECTOR_H

#include "1Component.h" // remember to change file name before compiling

class Connector : public Component
{
    protected:
        Component* leftChild;
        Component* rightChild;
    
    public:
        Connector();
        Connector(Component* left, Component* right);
        virtual bool run() = 0;
        virtual string getUserCommand() = 0;
        virtual void setFD(int, int) = 0;
        virtual int getOutputFD() = 0;
        virtual int getInputFD() = 0;
};

#endif