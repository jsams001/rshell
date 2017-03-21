#include "3And.h"

And::And() {} 

And::And(Component* left, Component* right) 
{
    this->leftChild = left;
    this->rightChild = right;
}

bool And::run()
{
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
    
void And::setFD(int in, int out) {}

int And::getInputFD()
{
    return 0;
}

int And::getOutputFD()
{
    return 0;
}