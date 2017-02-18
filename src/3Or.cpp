#include "1Component.h"
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
