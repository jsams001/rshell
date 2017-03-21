#include "3Or.h"

Or::Or() {} 

Or::Or(Component* left, Component* right) 
{
    this->inputFD = 0;
    this->outputFD = 1;
    this->leftChild = left;
    this->rightChild = right;
}

bool Or::run()
{
    if ((this->inputFD != 0) || this->outputFD != 1) // checks if outFD or inFD
    {                                               // are not default
        this->rightChild->setFD(inputFD, outputFD);
    }
    
    if (this->leftChild->run() == false)
    {
        if (this->rightChild->run())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
    return false;
}

string Or::getUserCommand()
{
    return "";
}
void Or::setFD(int in, int out)
{
    inputFD = in;
    outputFD = out;
}

int Or::getInputFD()
{
    return 0;
}

int Or::getOutputFD()
{
    return 0;
}