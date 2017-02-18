#include "1Component.h"
#include "2Connector.h"

Connector::Connector() {} // default constructor

Connector::Connector(Component* left, Component* right) // constructor with left and right children
{
    this->leftChild = left;
    this->rightChild = right;
}