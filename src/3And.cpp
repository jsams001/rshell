#include "3And.h"

And::And() {} 

And::And(Component* left, Component* right) 
{
    this->inputFD = 0;
    this->outputFD = 1;
    this->leftChild = left;
    this->rightChild = right;
}

bool And::run()
{
    if ((this->inputFD != 0) || this->outputFD != 1) // checks if outFD or inFD
    {                                               // are not default
        this->rightChild->setFD(inputFD, outputFD);
    }
    
    if (this->leftChild->run())
    {
        if (this->rightChild->run())
        {
            return true;
        }
    }
    
    return false;
}

string And::getUserCommand()
{
    return "";
}
    
void And::setFD(int in, int out)
{
    inputFD = in;
    outputFD = out;
}

int And::getInputFD()
{
    return 0;
}

int And::getOutputFD()
{
    return 0;
}