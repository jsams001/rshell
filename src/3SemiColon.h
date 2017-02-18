#ifndef SEMICOLON_H   
#define SEMICOLON_H

#include "1Component.h"
#include "2Connector.h" 

class SemiColon : public Connector
{
    protected:
        Component* leftChild;
        Component* rightChild;
        bool hasRightChild;
        
    public:
        SemiColon();
        SemiColon(Component* left);
        SemiColon(Component* left, Component* right);
        bool run();

};

#endif