# rshell
shell written in c++ for cs100

## Description
For this program we designed our own command shell that prompts the user for commands, 
which can be one single command, or multiple ones separated by any number of operators.
We used the executables in usr/bin/ to run these commands, and the connectors available 
for the user to use are **;**, **&&**, **||**. The function of each unique character
is defined below:

---
* ; - The command following this operator is always executed
* && - The next command is run only if the preceding one succeeds
* || - The next command is run only if the preceding one fails
* # - Any input after this character is taken as a comment
---

User can continue to input command lines until the unique input string is reached. Once
this command is run, the program executes any commands that precedes it on the command line
if present, then exits the program.

## Known Bugs

* Whitespace is a major requirement for our command line. On a terminal, the command 
echo A&&echo B will result in A and B being output on their own lines, while our program
will read everything after the first echo as the lone flag. Whitespace must be present 
between each command and connector, with the semicolon being the lone exception.
* Program might not work with multiple flags passed in. Works with a single flag passed in
for some commands (ex. ls -a), but errors might occur when multiple flags are passed in for 
the same object
* Immediately outputs error message for inputs where && and || are the first or last characters
the user inputs. Due to the way our vector is constructed, this is so an out of range won't occur
during the runtime of the program. If this occurs, user is prompted for commands once again. Strongly
suggested to start every command line with an actual command to avoid similar errors.

