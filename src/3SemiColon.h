#ifndef SEMICOLON_H   // remember to change file name
#define SEMICOLON_H

#include "Connector.h"  // remember to change file name before compiling
using namespace std;

class SemiColon : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        
    public:
        SemiColon(Component* left, Component* right);
        void run();
};

#endif