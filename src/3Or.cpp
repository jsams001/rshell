#include "1Component.h"
#include "3Or.h"

Or::Or() {} // default constructor

Or::Or(Component* left, Component* right) // constructor with left and right children
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

/*void Or::print() {}

void Or::printLeft() 
{
    cout << "OR LEFT CHILD: ";
    this->leftChild->print();
    cout << endl;
}
void Or::printRight() 
{
    cout << "OR RIGHT CHILD: ";
    this->rightChild->print();
    cout << endl;
}*/