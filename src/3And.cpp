#include "1Component.h"
#include "3And.h"

And::And() {} // default constructor

And::And(Component* left, Component* right) // constructor with left and right children
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
