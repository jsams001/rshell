#include "1Component.h"
#include "3SemiColon.h"

SemiColon::SemiColon() {} 

SemiColon::SemiColon(Component* left, Component* right) 
{
    this->leftChild = left;
    this->rightChild = right;
}

SemiColon::SemiColon(Component* left) // constructor with only left child
{
    this->leftChild = left;
}

bool SemiColon::run()
{
    this->leftChild->run();
    
    if (this->rightChild->run())
        return true;
    else
        return false;
    
}
