#ifndef OUTAPPREDIRECT_H
#define OUTAPPREDIRECT_H

#include "1Component.h"
#include "2Connector.h"

class OutAppRedirect : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        int inputFD;
        int outputFD;
        
    public:
        OutAppRedirect();
        OutAppRedirect(Component* left, Component* right);
        bool run();
        string getUserCommand();
        void setFD(int in, int out);
        int getOutputFD();
        int getInputFD();
};

#endif