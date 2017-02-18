#include "1Component.h"
#include "2Connector.h"

Connector::Connector() {} 

Connector::Connector(Component* left, Component* right) 
{
    this->leftChild = left;
    this->rightChild = right;
}