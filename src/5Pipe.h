#ifndef PIPE_H
#define PIPE_H

#include "1Component.h"
#include "2Connector.h"

class Pipe : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        int inputFD;
        int outputFD; 
        
    public:
        Pipe();
        Pipe(Component* left, Component* right);
        bool run();
        string getUserCommand();
        void setFD(int in, int out);
        int getOutputFD();
        int getInputFD();
};

#endif