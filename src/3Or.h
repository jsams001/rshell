#ifndef OR_H   // remember to change file name
#define OR_H

#include "1Component.h"
#include "2Connector.h"

class Or : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        int inputFD;
        int outputFD;
        
    public:
        Or();
        Or(Component* left, Component* right);
        bool run();
        string getUserCommand();
        void setFD(int in, int out);
        int getOutputFD();
        int getInputFD();
};

#endif