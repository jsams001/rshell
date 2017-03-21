#ifndef INREDIRECT_H
#define INREDIRECT_H

#include "1Component.h"
#include "2Connector.h"

class InRedirect : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        int inputFD;
        int outputFD; 
        
    public:
        InRedirect();
        InRedirect(Component* left, Component* right);
        bool run();
        string getUserCommand();
        void setFD(int in, int out);
        int getOutputFD();
        int getInputFD();
};

#endif