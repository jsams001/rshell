#include "1Component.h"
#include "3SemiColon.h"

SemiColon::SemiColon() {} // default constructor

SemiColon::SemiColon(Component* left, Component* right) // constructor with left and right children
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
