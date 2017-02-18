#include "1Component.h"
#include "3SemiColon.h"

SemiColon::SemiColon() {} 

SemiColon::SemiColon(Component* left, Component* right) 
{
    this->leftChild = left;
    this->rightChild = right;
    hasRightChild = true;
}

SemiColon::SemiColon(Component* left) // constructor with only left child
{
    this->leftChild = left;
    hasRightChild = false;
}

bool SemiColon::run()
{
    this->leftChild->run();
    
    if (hasRightChild)
    {
        if (this->rightChild->run())
            return true;
        else
            return false;
    }
    
    return true;
    
}
