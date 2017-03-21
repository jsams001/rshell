#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "5OutRedirect.h"

OutRedirect::OutRedirect() {}

OutRedirect::OutRedirect(Component* left, Component* right)
{
    this->leftChild = left;
    this->rightChild = right;
}

bool OutRedirect::run()
{
    string rightFilePath = this->rightChild->getUserCommand();
    
    int newFd = open(rightFilePath.c_str(), O_RDWR | O_TRUNC | O_CREAT, 
                                            S_IRWXU);   // this will truncate
    if (newFd == -1)                                    // existing files and
    {                                                   // open if it doesnt
        perror("open() has failed");                    // exist
        return false;
    }
    
    this->leftChild->setFD(rightChild->getInputFD(), newFd);
    
    if (this->leftChild->run())
    {
        return true;
    }
    else
    {
        return false;
    }
}

string OutRedirect::getUserCommand() 
{
    return "";
}

void OutRedirect::setFD(int in, int out) {}

int OutRedirect::getInputFD()
{
    return 0;
}

int OutRedirect::getOutputFD()
{
    return 0;
}
