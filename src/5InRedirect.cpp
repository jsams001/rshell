#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "5InRedirect.h"

InRedirect::InRedirect()
{
    inputFD = 0;
    outputFD = 1;
}

InRedirect::InRedirect(Component* left, Component* right)
{
    inputFD = 0;
    outputFD = 1;
    this->leftChild = left;
    this->rightChild = right;
}

bool InRedirect::run()
{
    string rightFilePath = this->rightChild->getUserCommand(); // get file path
    
    int newFD = open(rightFilePath.c_str(), O_RDWR);    // call open() to get
    if (newFD == -1)                        // FD for the right child text file
    {
        perror("open() has failed");
        return false;
    }
    
    this->leftChild->setFD(newFD, outputFD); // sets the file 
                                                   // descriptors for left child
                                     // to match the new FD from open
    if (this->leftChild->run())
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

string InRedirect::getUserCommand() 
{
    return "";
}

void InRedirect::setFD(int in, int out)
{
    inputFD = in;
    outputFD = out;
}

int InRedirect::getInputFD()
{
    return inputFD;
}

int InRedirect::getOutputFD()
{
    return outputFD;
}