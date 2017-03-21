#include "3Or.h"

Or::Or() {} 

Or::Or(Component* left, Component* right) 
{
    this->leftChild = left;
    this->rightChild = right;
}

bool Or::run()
{
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
void Or::setFD(int in, int out) {}

int Or::getInputFD()
{
    return 0;
}

int Or::getOutputFD()
{
    return 0;
}