#include "3SemiColon.h"

SemiColon::SemiColon() {} 

SemiColon::SemiColon(Component* left, Component* right) 
{
    this->inputFD = 0;
    this->outputFD = 1;
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
    if ((this->inputFD != 0) || this->outputFD != 1) // checks if outFD or inFD
    {                                               // are not default
        this->rightChild->setFD(inputFD, outputFD);
    }
    
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
void SemiColon::setFD(int in, int out)
{
    inputFD = in;
    outputFD = out;
}

int SemiColon::getInputFD()
{
    return 0;
}

int SemiColon::getOutputFD()
{
    return 0;
}
