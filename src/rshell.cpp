#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
using namespace std;

#include "1Component.h"
#include "2Command.h"
#include "2Connector.h"
#include "3And.h"
#include "3Or.h"
#include "3SemiColon.h"

void printCommandPrompt(bool &userInfoAvailable)
{
    if (userInfoAvailable)
    {
        char* userName = getlogin();
        if (userName == NULL)
        {
            perror("getlogin() failed");
            userInfoAvailable = false;
        }
    
        char hostName[256] = "/0";
        gethostname(hostName, 256);
        if (hostName == NULL)
        {
            perror("gethostname() failed");
            userInfoAvailable = false;
        }
        
        if (userInfoAvailable)
        {
            cout << userName << "@" << hostName;
        }
    }

    cout << "$ ";
}

void ignoreComments(string &input) // Ignores any user input after the first "#".
{
    size_t firstPound = input.find_first_of("#");
    if (firstPound != string::npos)
    {
        input.erase(input.begin() + firstPound, input.end());
    }
}

void parseInput(const string& input, vector<string>& separatedInput)
{
    char* c_strInput = new char[input.size() + 1];
    strcpy(c_strInput, input.c_str());
    
    char* parsedInput = strtok(c_strInput, " ");
    
    while (parsedInput != NULL) // EX. input = echo A && echo B, separatedinput.at(0) == echo, separatedinput.at(1) == A
    { 
        string test = parsedInput;
        separatedInput.push_back(test);
        parsedInput = strtok(NULL, " ");
    }
    
    /*cout << "START OF SEPARATED VECTOR: " << endl; //This vector is confirmed to work correctly
    for (unsigned int i = 0; i < separatedInput.size(); ++i) {
        
        cout << i << ": " << separatedInput.at(i) << endl;
    }
    cout << endl;*/
}

void combineCommands(const vector<string>& separatedInput, vector<string>& combinedCommands) 
{
    string change;
    
    for (unsigned int i = 0; i < separatedInput.size(); ++i) 
    {
        string semi = ";";
        string amp = "&&";
        string bar = "||";
        
        if (separatedInput.at(i).compare(amp) == 0) {
            combinedCommands.push_back(change);
            change.clear();
            combinedCommands.push_back(amp);
        }
        else if (separatedInput.at(i).compare(bar) == 0) {
            combinedCommands.push_back(change);
            change.clear();
            combinedCommands.push_back(bar);
        }
        else if (separatedInput.at(i).compare(separatedInput.at(i).size() - 1, 1, semi) == 0) {
            change += separatedInput.at(i);
            change.erase(change.size() - 1, 1);
            combinedCommands.push_back(change);
            combinedCommands.push_back(semi);
            change.clear();
        }
        else if (i == separatedInput.size() - 1) {
            change += separatedInput.at(i);
            combinedCommands.push_back(change);
            change.clear();
        }
        else {
            change += separatedInput.at(i);
            change += " ";
        }
    }
    
    /*cout << endl << "START OF COMBINED VECTOR: " << endl; // This vector is confirmed to work correctly
    for (unsigned int i = 0; i < combinedCommands.size(); ++i) {
        
        cout << i << ": " << combinedCommands.at(i) << endl;
    }
    cout << endl;*/
}

bool checkValidInput(const vector<string>& parsedInput) // IMPLEMENT LATER
{
       
    if (parsedInput.front() == "&&" || parsedInput.front() == "||") 
    {
        cout << "ERROR: INVALID INPUT - CAN'T BEGIN COMMAND LINE WITH AND/OR CONNECTOR " << endl;
        return false;
    }
    
    if (parsedInput.back() == "&&" || parsedInput.back() == "||") 
    {
        cout << "ERROR: INVALID INPUT - CAN'T END COMMAND LINE WITH AND/OR CONNECTOR " << endl;
        return false;
    }
    
    return true;
}

Component* constructTree(const vector<string>& combinedCommands) 
{
    Component* reference;
    bool setRightChild = false;
    
    for (unsigned int i = 0; i < combinedCommands.size(); ++i) 
    {
        if (combinedCommands.at(i) == "&&")
        {
            Command* andNewCommand = new Command(combinedCommands.at(i + 1));
            And* newAnd = new And(reference, andNewCommand);
            reference = newAnd;
            setRightChild = true;
        }
        else if (combinedCommands.at(i) == "||")
        {
            Command* orNewCommand = new Command(combinedCommands.at(i + 1));
            Or* newOr = new Or(reference, orNewCommand);
            reference = newOr;
            setRightChild = true;
        }
        else if (combinedCommands.at(i) == ";") // CHECK FOR CASE echo A; echo B
        {
            Command* semiNewCommand = new Command(combinedCommands.at(i + 1));
            SemiColon* newSemi = new SemiColon(reference, semiNewCommand);
            reference = newSemi;
            setRightChild = true;
        }
        else if (setRightChild)
        {
            setRightChild = false;
        }
        else 
        {
            Command* newCommand = new Command(combinedCommands.at(i));
            reference = newCommand;
        }
    }
    
    return reference;
}

int main()
{
    string userInput;
    bool userInfoAvailable = true; // Passed into printCommandPrompt so if user info is not available, the shell will not continue throwing errors.
    vector<string> separatedInput; // Separate userInput by tokens and put them in separatedInput
    vector<string> combinedCommands; // Combines the connectors with the commands 
    
    for (;;)
    {
        printCommandPrompt(userInfoAvailable); 
        
        getline(cin, userInput);
        
        ignoreComments(userInput); // Ignores any user input after the first "#".
        
        if (userInput.empty()) // returns if userinput has no commands
        {
            continue;
        }
        
        parseInput(userInput, separatedInput); // Fills up vector with the different commands in the command line
        
        if (checkValidInput(separatedInput)) // If this wasn't here, out of bounds error could occur
        {
            combineCommands(separatedInput, combinedCommands); // Construct commands, keeps connectors separate
            Component* head = constructTree(combinedCommands);
            head->run();
        }
        
        separatedInput.clear();
        combinedCommands.clear();
        
    }
    
    return 0;
}