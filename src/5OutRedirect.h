#ifndef OUTREDIRECT_H
#define OUTREDIRECT_H

#include "1Component.h"
#include "2Connector.h"

class OutRedirect : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        int inputFD;
        int outputFD; 
        
    public:
        OutRedirect();
        OutRedirect(Component* left, Component* right);
        bool run();
        string getUserCommand();
        void setFD(int in, int out);
        int getOutputFD();
        int getInputFD();
};

#endif