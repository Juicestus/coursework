#ifndef _LEXER_H_
#define _LEXER_H_

#include <vector>
#include <string>

#include "Command.h"

/*
 * class that tokenizes the input into vector of commands
 * vector is then accesible outside of class
 * 
 * if vector length > 1, then commands are piped together:
 *  - vector.front() is first command in piped chain
 *  - vector.back() is last command in piped chain
 */
class Tokenizer {
private:
    // full user input stored for internal convenience
    std::string input;
    // flag for if an error occurs - error will be printed by Tokenizer
    bool error;

public:
    // vector of commands
    std::vector<Command*> commands;
    
    // constructor - takes CLI input and calls internal convenience
    //               functions to tokenize into commands
    Tokenizer (const std::string _input);

    // destructor - deletes pointers in vector and erases elements
    ~Tokenizer ();

    // boolean function to return if error ocurred during parsing
    bool hasError ();

private:
    // convenience functions to trim whitespace and split input on "|"
    std::string trim (const std::string in);
    void split (const std::string delim);
};

#endif
