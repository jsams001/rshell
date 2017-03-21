#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "5Pipe.h"

Pipe::Pipe() {}

Pipe::Pipe(Component* left, Component* right) 
{
    this->leftChild = left;
    this->rightChild = right;
    inputFD = 0;
    outputFD = 1;
}

bool Pipe::run()
{
    int pipefd[2];
    bool check;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return false;
    }    
    
    leftChild->setFD(inputFD, pipefd[1]);
    check = leftChild->run();
    
    if (check == false) { 
        return false;
    }
     
    if (close(pipefd[1]) == -1) {
        perror("close");
        return false;
    }
    
    rightChild->setFD(pipefd[0], outputFD);
    check = rightChild->run();
    if (close(pipefd[0]) == -1) {
        perror("close");
        return false;
    }

    if (check == false) {
       return false;
    }
    
    return true;
}

string Pipe::getUserCommand() 
{
    return "";
}

void Pipe::setFD(int in, int out) {
    this->inputFD = in;
    this->outputFD = out; 
}

int Pipe::getInputFD()
{
    return 0;
}

int Pipe::getOutputFD()
{
    return 0;
}