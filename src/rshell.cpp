#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
using namespace std;

#include "1Component.h"
#include "2Command.h"
#include "2Connector.h"
#include "3And.h"
#include "3Or.h"
#include "3SemiColon.h"
#include "4Test.h"
#include "5Pipe.h"
#include "5InRedirect.h"
#include "5OutRedirect.h"
#include "5OutAppRedirect.h"

void printCommandPrompt(bool &userInfoAvailable)
{
    if (userInfoAvailable)
    {
        char* userName = getlogin(); // gets user name
        if (userName == NULL)
        {
            perror("getlogin() failed");
            userInfoAvailable = false;
        }
    
        char hostName[256] = "/0";
        gethostname(hostName, 256); // gets host name
        if (hostName == NULL)
        {
            perror("gethostname() failed");
            userInfoAvailable = false;
        }
        
        if (userInfoAvailable)
        {
            cout << "[" << userName << "@" << hostName << "]";
        }
    }

    cout << "$ ";
}

void ignoreComments(string &input) // Ignores any user input after the first "#"
{
    size_t firstPound = input.find_first_of("#");
    if (firstPound != string::npos)
    {
        input.erase(input.begin() + firstPound, input.end());
    }
}

void parseInput(const string& input, vector<string>& separatedInput)
{
    unsigned int i = 0;
    char* c_strInput = new char[input.size() + 1];
    strcpy(c_strInput, input.c_str());
    
    char* parsedInput = strtok(c_strInput, " ");
    
    while (parsedInput != NULL) 
    { 
        string test = parsedInput;
        separatedInput.push_back(test);
        
        if (separatedInput.at(i).at(0) == '/')
            separatedInput.at(i).erase(0, 1);
        
        parsedInput = strtok(NULL, " ");
        ++i;
    }
}

void combineCommands(const vector<string>& separatedInput, 
                 vector<string>& combinedCommands) 
    {             
    string change;
    
    for (unsigned int i = 0; i < separatedInput.size(); ++i) 
    {
        string semi = ";";
        string amp = "&&";
        string bar = "||";
        string parenLeft = "(";
        string parenRight = ")";
        string testLeft = "[";
        string testRight = "]";
        string pipe = "|";
        string input = "<";
        string output1 = ">";
        string output2 = ">>";

        if (separatedInput.at(i).compare(amp) == 0) 
        {
            if(!change.empty())
            {
                combinedCommands.push_back(change);
                change.clear();
            }
            combinedCommands.push_back(amp);
        }
        
        else if (separatedInput.at(i).compare(bar) == 0) 
        {
            if(!change.empty())
            {
                combinedCommands.push_back(change);
                change.clear();
            }
            combinedCommands.push_back(bar);
        }
        
        else if (separatedInput.at(i).compare(pipe) == 0) 
        {
            if(!change.empty())
            {
                combinedCommands.push_back(change);
                change.clear();
            }
            combinedCommands.push_back(pipe);
        }
        
        else if (separatedInput.at(i).compare(input) == 0) 
        {
            if(!change.empty())
            {
                combinedCommands.push_back(change);
                change.clear();
            }
            combinedCommands.push_back(input);
        }
        
        else if (separatedInput.at(i).compare(output1) == 0) 
        {
            if(!change.empty())
            {
                combinedCommands.push_back(change);
                change.clear();
            }
            combinedCommands.push_back(output1);
        }
        
        else if (separatedInput.at(i).compare(output2) == 0) 
        {
            if(!change.empty())
            {
                combinedCommands.push_back(change);
                change.clear();
            }
            combinedCommands.push_back(output2);
        }
        
        else if (separatedInput.at(i).compare(separatedInput.at(i).size() - 1, 
                                              1, semi) == 0) 
        {
            if (!change.empty())
            {
                change += separatedInput.at(i);
                change.erase(change.size() - 1, 1);
                combinedCommands.push_back(change);
                change.clear();
            }
            combinedCommands.push_back(semi);
        }
        
        else if (separatedInput.at(i).compare(0, 1, parenLeft) == 0)
        {
            bool parenEnd = false;
            bool semiEnd = false;
            while (!semiEnd && !parenEnd)
            {
                if (separatedInput.at(i).compare(separatedInput.at(i).size() - 1,
                                                    1, parenRight) == 0)
                    parenEnd = true;
                if (separatedInput.at(i).compare(separatedInput.at(i).size() - 1, 
                                                    1, semi) == 0)
                    semiEnd = true;
                if (!semiEnd && !parenEnd) 
                {
                    change += separatedInput.at(i);
                    change += " ";
                    i++;
                }
            }
            if (parenEnd)
            {
                change += separatedInput.at(i);
                combinedCommands.push_back(change);
                change.clear();
            }
            else if(semiEnd)
            {
                change += separatedInput.at(i);
                change.erase(change.size() - 1, 1);
                combinedCommands.push_back(change);
                combinedCommands.push_back(semi);
                change.clear();
            }
        }
        
        else if (separatedInput.at(i) == testLeft)
        {
            bool checkForTestRight = false; // checks for right bracket
            unsigned testRightPos;
            
            for (unsigned k = i; k < separatedInput.size(); ++k) 
            {
                if (separatedInput.at(k) == testRight)
                {
                    checkForTestRight = true;
                    testRightPos = k;
                } 
            }
            if (!checkForTestRight)
            {
                cout << "Must either input right bracket or put spaces between"
                     << " brackets." << endl;
                
                combinedCommands.pop_back();
                break;
            }
            
            for (unsigned j = i; j <= testRightPos; ++j)
            {   
                change += separatedInput.at(j);
                change += " ";
            }
            //change += separatedInput.at(i);
            combinedCommands.push_back(change);
            change.clear();
            i += testRightPos - i;
        }
        
        else if (i == separatedInput.size() - 1) 
        {
            change += separatedInput.at(i);
            combinedCommands.push_back(change);
            change.clear();
        }
        
        else 
        {
            change += separatedInput.at(i);
            change += " ";
        }
    }
}

bool checkValidInput(const vector<string>& parsedInput) // IMPLEMENT LATER
{
       
    if (parsedInput.front() == "&&" || parsedInput.front() == "||") 
    {
        cout << "ERROR: INVALID INPUT - ";
        cout << "CAN'T BEGIN COMMAND LINE WITH AND/OR CONNECTOR " << endl;
        return false;
    }
    
    if (parsedInput.back() == "&&" || parsedInput.back() == "||") 
    {
        cout << "ERROR: INVALID INPUT - ";
        cout << "CAN'T END COMMAND LINE WITH AND/OR CONNECTOR " << endl;
        return false;
    }
    
    return true;
}

Component* constructTree(const vector<string>& combinedCommands) 
{
    
    Component* reference; // used to set tree nodes
    bool setRightChild = false;
    
    string create; // string used for removing parentheses
    vector<string>pSeparateElement; // used for separating precedence commands
    vector<string>pCombinedCommands; 
    
    for (unsigned int i = 0; i < combinedCommands.size(); ++i) 
    {
        if (setRightChild)
            setRightChild = false;
            
        else if (combinedCommands.at(i) == "|") 
        {
            Command* rightCommand = 
            new Command(combinedCommands.at(i + 1));
            Pipe* newPipe = new Pipe(reference, rightCommand);
            reference = newPipe;
            setRightChild = true;
        }
        
        else if (combinedCommands.at(i) == "<") 
        {
            
            if (combinedCommands.at(i + 1).at(0) == '(')
            {
                create = combinedCommands.at(i + 1);
                create = create.substr(1, create.size() - 2);
                parseInput(create, pSeparateElement);
                combineCommands(pSeparateElement, pCombinedCommands);
                InRedirect* newInReParen = new InRedirect(reference, 
                                              constructTree(pCombinedCommands));
                reference = newInReParen;
                pSeparateElement.clear();
                pCombinedCommands.clear();
                setRightChild = true;
            }
            else    // this is for making commands right children of connectors
            {
                if (combinedCommands.at(i + 1).find("test") == 0)
                {
                    Test* rightTest = new Test(combinedCommands.at(i + 1));
                    InRedirect* newInRe = new InRedirect(reference, rightTest);
                    reference = newInRe;
                }
                else if (combinedCommands.at(i + 1).at(0) == '[')
                {
                    string tempCmd = "test";
                
                    for (unsigned k = 1; 
                         combinedCommands.at(i + 1).at(k) != ']'; ++k)
                    {
                        tempCmd += combinedCommands.at(i + 1).at(k);
                    }

                    Test* rightTest = new Test(tempCmd);
                    InRedirect* newInRe = new InRedirect(reference, rightTest);
                    reference = newInRe;
                }
                else
                {
                    Command* rightCommand = 
                    new Command(combinedCommands.at(i + 1));
                    
                    InRedirect* newInRe = new InRedirect(reference, 
                                                        rightCommand);
                    
                    reference = newInRe;
                    
                }
                setRightChild = true;
            }
        }
        
        else if (combinedCommands.at(i) == ">") 
        {
            
            if (combinedCommands.at(i + 1).at(0) == '(')
            {
                create = combinedCommands.at(i + 1);
                create = create.substr(1, create.size() - 2);
                parseInput(create, pSeparateElement);
                combineCommands(pSeparateElement, pCombinedCommands);
                OutRedirect* newOutReParen = new OutRedirect(reference, 
                                              constructTree(pCombinedCommands));
                reference = newOutReParen;
                pSeparateElement.clear();
                pCombinedCommands.clear();
                setRightChild = true;
            }
            else    // this is for making commands right children of connectors
            {
                if (combinedCommands.at(i + 1).find("test") == 0)
                {
                    Test* rightTest = new Test(combinedCommands.at(i + 1));
                    OutRedirect* newOutRe = new OutRedirect(reference, rightTest);
                    reference = newOutRe;
                }
                else if (combinedCommands.at(i + 1).at(0) == '[')
                {
                    string tempCmd = "test";
                
                    for (unsigned k = 1; 
                         combinedCommands.at(i + 1).at(k) != ']'; ++k)
                    {
                        tempCmd += combinedCommands.at(i + 1).at(k);
                    }

                    Test* rightTest = new Test(tempCmd);
                    OutRedirect* newOutRe = new OutRedirect(reference, rightTest);
                    reference = newOutRe;
                }
                else
                {
                    Command* rightCommand = 
                    new Command(combinedCommands.at(i + 1));
                    
                    OutRedirect* newOutRe = new OutRedirect(reference, 
                                                        rightCommand);
                    reference = newOutRe;
                }
                setRightChild = true;
            }
        }
        
        else if (combinedCommands.at(i) == ">>") 
        {
            
            if (combinedCommands.at(i + 1).at(0) == '(')
            {
                create = combinedCommands.at(i + 1);
                create = create.substr(1, create.size() - 2);
                parseInput(create, pSeparateElement);
                combineCommands(pSeparateElement, pCombinedCommands);
                OutAppRedirect* newOutAppReParen = new OutAppRedirect(reference, 
                                              constructTree(pCombinedCommands));
                reference = newOutAppReParen;
                pSeparateElement.clear();
                pCombinedCommands.clear();
                setRightChild = true;
            }
            else    // this is for making commands right children of connectors
            {
                if (combinedCommands.at(i + 1).find("test") == 0)
                {
                    Test* rightTest = new Test(combinedCommands.at(i + 1));
                    OutAppRedirect* newOutAppRe = new OutAppRedirect(reference, 
                                                                rightTest);
                    reference = newOutAppRe;
                }
                else if (combinedCommands.at(i + 1).at(0) == '[')
                {
                    string tempCmd = "test";
                
                    for (unsigned k = 1; 
                         combinedCommands.at(i + 1).at(k) != ']'; ++k)
                    {
                        tempCmd += combinedCommands.at(i + 1).at(k);
                    }

                    Test* rightTest = new Test(tempCmd);
                    OutAppRedirect* newOutAppRe = new OutAppRedirect(reference, 
                                                                    rightTest);
                    reference = newOutAppRe;
                }
                else
                {
                    Command* rightCommand = 
                    new Command(combinedCommands.at(i + 1));
                    
                    OutAppRedirect* newOutAppRe = new OutAppRedirect(reference, 
                                                        rightCommand);
                    reference = newOutAppRe;
                }
                setRightChild = true;
            }
        }
        
        else if (combinedCommands.at(i) == "&&")
        {
            if (combinedCommands.at(i + 1).at(0) == '(')
            {
                create = combinedCommands.at(i + 1);
                create = create.substr(1, create.size() - 2);
                parseInput(create, pSeparateElement);
                combineCommands(pSeparateElement, pCombinedCommands);
                And* newAndParen = new And(reference,constructTree(pCombinedCommands));
                reference = newAndParen;
                pSeparateElement.clear();
                pCombinedCommands.clear();
                setRightChild = true;
            }
            else    // this is for making commands right children of connectors
            {
                if (combinedCommands.at(i + 1).find("test") == 0)
                {
                    Test* rightTest = new Test(combinedCommands.at(i + 1));
                    And* newAnd = new And(reference, rightTest);
                    reference = newAnd;
                }
                else if (combinedCommands.at(i + 1).at(0) == '[')
                {
                    string tempCmd = "test";
                
                    for (unsigned k = 1; 
                         combinedCommands.at(i + 1).at(k) != ']'; ++k)
                    {
                        tempCmd += combinedCommands.at(i + 1).at(k);
                    }

                    Test* rightTest = new Test(tempCmd);
                    And* newAnd = new And(reference, rightTest);
                    reference = newAnd;
                }
                else
                {
                    Command* rightCommand = 
                    new Command(combinedCommands.at(i + 1));
                    And* newAnd = new And(reference, rightCommand);
                    reference = newAnd;
                }
                setRightChild = true;
            }
        }
        
        else if (combinedCommands.at(i) == "||")
        {
            if (combinedCommands.at(i + 1).at(0) == '(')
            {
                create = combinedCommands.at(i + 1);
                create = create.substr(1, create.size() - 2);
                parseInput(create, pSeparateElement);
                combineCommands(pSeparateElement, pCombinedCommands);
                Or* newOrParen = new Or(reference,constructTree(pCombinedCommands));
                reference = newOrParen;
                pSeparateElement.clear();
                pCombinedCommands.clear();
                setRightChild = true;
            }
            else    // this is for making commands right children of connectors
            {
                if (combinedCommands.at(i + 1).find("test") == 0)
                {
                    Test* rightTest = new Test(combinedCommands.at(i + 1));
                    Or* newOr = new Or(reference, rightTest);
                    reference = newOr;
                }
                else if (combinedCommands.at(i + 1).at(0) == '[')
                {
                    string tempCmd = "test";
                
                    for (unsigned k = 1; 
                         combinedCommands.at(i + 1).at(k) != ']'; ++k)
                    {
                        tempCmd += combinedCommands.at(i + 1).at(k);
                    }

                    Test* rightTest = new Test(tempCmd);
                    Or* newOr = new Or(reference, rightTest);
                    reference = newOr;
                }
                else
                {
                    Command* rightCommand = 
                    new Command(combinedCommands.at(i + 1));
                    Or* newOr = new Or(reference, rightCommand);
                    reference = newOr;
                }
                setRightChild = true;
            }
        }
        
        else if (combinedCommands.at(i) == ";") 
        {
            if (i == combinedCommands.size() - 1)
            {
                SemiColon* oneChild = new SemiColon(reference);
                reference = oneChild;
            }
            else if (combinedCommands.at(i + 1).at(0) == '(')
            {
                create = combinedCommands.at(i + 1);
                create = create.substr(1, create.size() - 2);
                parseInput(create, pSeparateElement);
                combineCommands(pSeparateElement, pCombinedCommands);
                SemiColon* newSemiParen = 
                    new SemiColon(reference,constructTree(pCombinedCommands));
                reference = newSemiParen;
                pSeparateElement.clear();
                pCombinedCommands.clear();
                setRightChild = true;
            }
            else    // this is for making commands right children of connectors
            {
                if (combinedCommands.at(i + 1).find("test") == 0)
                {
                    Test* rightTest = new Test(combinedCommands.at(i + 1));
                    SemiColon* newSemi = new SemiColon(reference, rightTest);
                    reference = newSemi;
                }
                else if (combinedCommands.at(i + 1).at(0) == '[')
                {
                    string tempCmd = "test";
                
                    for (unsigned k = 1; 
                         combinedCommands.at(i + 1).at(k) != ']'; ++k)
                    {
                        tempCmd += combinedCommands.at(i + 1).at(k);
                    }

                    Test* rightTest = new Test(tempCmd);
                    SemiColon* newSemi = new SemiColon(reference, rightTest);
                    reference = newSemi;
                }
                else
                {
                    Command* rightCommand = 
                    new Command(combinedCommands.at(i + 1));
                    
                    SemiColon* newSemi = new SemiColon(reference, rightCommand);
                    reference = newSemi;
                }
                setRightChild = true;
            }
        }
        
        else if (combinedCommands.at(i).at(0) == '(')
        {
            create = combinedCommands.at(i);
            create = create.substr(1, create.size() - 2);
            parseInput(create, pSeparateElement);
            combineCommands(pSeparateElement, pCombinedCommands);
            reference = constructTree(pCombinedCommands);
            pSeparateElement.clear();
            pCombinedCommands.clear();
        }
        
        else    // sets new command
        {
            if (combinedCommands.at(i).find("test") == 0)
            {
                Test* newTest = new Test(combinedCommands.at(i));
                reference = newTest;
            }
            else if (combinedCommands.at(i).at(0) == '[')  // checks for test
            {
                string tempCmd = "test";
                
                for (unsigned k = 1; combinedCommands.at(i).at(k) != ']'; ++k)
                {
                    tempCmd += combinedCommands.at(i).at(k);
                }

                Test* newTest = new Test(tempCmd);
                reference = newTest;
            }
            else
            {
                Command* newCommand = new Command(combinedCommands.at(i));
                reference = newCommand;
            }
        }
    }
    
    return reference;
}

int main()
{
    string userInput;
    
    bool userInfoAvailable = true; // Passed into printCommandPrompt so if 
                                    // user info is not available, the shell 
                                    // will not continue throwing errors.
                                    
    vector<string> separatedInput; // Separate userInput 
                                    // by tokens and put them in separatedInput
                                    
    vector<string> combinedCommands; // Reconstructs the commands and divides
                                      // them by the connectors
    
    for (;;)
    {
        printCommandPrompt(userInfoAvailable); 
        
        getline(cin, userInput);
        
        ignoreComments(userInput); // Ignores any user input after the first "#"
        
        if (userInput.empty()) // returns if userinput has no commands
        {
            continue;
        }
        
        // Fills up vector with the different commands in the command line
        parseInput(userInput, separatedInput);
        
        // Prevents out of bounds error when combining commands
        if (checkValidInput(separatedInput)) 
        {
            combineCommands(separatedInput, combinedCommands);
            Component* head = constructTree(combinedCommands);
            head->run(); 
        }
        
        separatedInput.clear();
        combinedCommands.clear();
    }
    
    return 0;
}