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

string SemiColon::getUserCommand()
{
    return "";
}
void SemiColon::setFD(int in, int out) {}

int SemiColon::getInputFD()
{
    return 0;
}

int SemiColon::getOutputFD()
{
    return 0;
}
