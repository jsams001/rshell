#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;


int main() {
    
    Component* reference;
    bool setRightChild = false;
    bool firstConnector = true;
    // bool noReferenceToCommand = true;
    
    for (unsigned int i = 0; i < combinedCommands.size(); ++i) 
    {
        if (combinedCommands.at(i) == "&&")
        {
            if (firstConnector)
            {
                Command* andNewCommand = new Command(combinedCommands.at(i + 1));
                And* newAnd = new And(reference, andNewCommand);
                reference = newAnd;
                setRightChild = true;
                firstConnector = false;
            }
            else
            {
                Command* andNewCommand2 = new Command(combinedCommands.at(i + 1));
                And* newAnd2 = new And(reference, andNewCommand2);
                reference = newAnd2;
                setRightChild = true;
                // noReferenceToCommand - true;
            }
        }
        else if (combinedCommands.at(i) == "||")
        {
            if (firstConnector)
            {
                Command* orNewCommand = new Command(combinedCommands.at(i + 1));
                Or* newOr = new Or(reference, orNewCommand);
                reference = newOr;
                setRightChild = true;
                firstConnector = false;
            }
            else 
            {
                Command* orNewCommand2 = new Command(combinedCommands.at(i + 1));
                Or* newOr2 = new Or(reference, orNewCommand2);
                reference = newOr2;
                setRightChild = true;
                // noReferenceToCommand = true;
            }
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
        // else if (!noReferenceToCommand)
        // {
        //     Command* newCommand = new Command(combinedCommands.at(i));
        //     reference = newCommand;
        //     noReferenceToCommand = false;
            
        //     if(i == combinedCommands.size() - 1)
        //         reference->run();
        // }
        // else
        // {
        //     reference->run();
        //     Command* newerCommand = new Command(combinedCommands.at(i));
        //     reference = newerCommand;
        // }
    }
    
    return reference;
}
    
    // CODE USED FOR FILLING VECTOR: IMPLEMENTED
    // string userinput;
    // vector<string> myvector;
    // vector<string> secondvector;
    // string change;
    
    // cout << "Enter user input: " << endl;
    
    // getline(cin, userinput);  
    
    // char* c_strInput = new char[userinput.size() + 1];
    // strcpy(c_strInput, userinput.c_str());
    
    // char* parsedInput = strtok(c_strInput, " ");
    
    // while(parsedInput != NULL) {
    //     string test = parsedInput;
    //     myvector.push_back(test);
    //     parsedInput = strtok(NULL, " ");
    // }
    
    // // for(unsigned int i = 0; i < myvector.size(); ++i) {
        
    // //     cout << i << " " << myvector.at(i) << endl;

    // // }
    
    // for(unsigned int i = 0; i < myvector.size(); ++i) {
        
    //     //cout << i << " " << myvector.at(i) << endl;

    //     string semi = ";";
    //     string amp = "&&";
    //     string bar = "||";
        
    //     if(myvector.at(i).compare(amp) == 0) {
    //         secondvector.push_back(change);
    //         change.clear();
    //         secondvector.push_back(amp);
    //     }
    //     else if(myvector.at(i).compare(bar) == 0) {
    //         secondvector.push_back(change);
    //         change.clear();
    //         secondvector.push_back(bar);
    //     }
    //     else if(myvector.at(i).compare(myvector.at(i).size() - 1, 1, semi) == 0) {
    //         change += myvector.at(i);
    //         // cout << "Before change: " << change << endl;
    //         change.erase(change.size() - 1, 1);
    //         // cout << "Change " << i << ": " << change << endl;
    //         secondvector.push_back(change);
    //         change.clear();
    //     }
    //     else if(i == myvector.size() - 1) {
    //         change += myvector.at(i);
    //         secondvector.push_back(change);
    //         change.clear();
    //     }
    //     else {
    //         change += myvector.at(i);
    //         change += " ";
    //         // cout << change << endl;
    //     }
    // }
    
    // cout << "START OF VECTOR: " << endl;
    // for(unsigned int i = 0; i < secondvector.size(); ++i) {
        
    //     cout << i << ": " << secondvector.at(i) << endl;
    // }
    
    