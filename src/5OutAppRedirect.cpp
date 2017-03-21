#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "5OutAppRedirect.h"

OutAppRedirect::OutAppRedirect()
{
    inputFD = 0;
    outputFD = 1;
}

OutAppRedirect::OutAppRedirect(Component* left, Component* right)
{
    inputFD = 0;
    outputFD = 1;
    this->leftChild = left;
    this->rightChild = right;
}

bool OutAppRedirect::run()
{
    string rightFilePath = this->rightChild->getUserCommand();
    
    int newFd = open(rightFilePath.c_str(), O_RDWR | O_APPEND | O_CREAT, 
                                            S_IRWXU);   // this will append to
    if (newFd == -1)                                    // existing files and
    {                                                   // open if it doesnt
        perror("open() has failed");                    // exist
        return false;
    }
    
    this->leftChild->setFD(inputFD, newFd);
    
    if (this->leftChild->run())
    {
        return true;
    }
    else
    {
        return false;
    }
}

string OutAppRedirect::getUserCommand() 
{
    return "";
}

void OutAppRedirect::setFD(int in, int out)
{
    inputFD = in;
    outputFD = out;
}

int OutAppRedirect::getInputFD()
{
    return inputFD;
}

int OutAppRedirect::getOutputFD()
{
    return outputFD;
}
