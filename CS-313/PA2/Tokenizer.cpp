#include <iostream>
#include "Tokenizer.h"

using namespace std;

Tokenizer::Tokenizer (const string _input) {
    error = false;
    input = trim(_input);
    split("|");
}

Tokenizer::~Tokenizer () {
    for (auto cmd : commands) {
        delete cmd;
    }
    commands.clear();
}

bool Tokenizer::hasError () {
    return error;
}

string Tokenizer::trim (const string in) {
    int i = in.find_first_not_of(" \n\r\t");
    int j = in.find_last_not_of(" \n\r\t");

    if (i >= 0 && j >= i) {
        return in.substr(i, j-i+1);
    }
    return in;
}

void Tokenizer::split (const string delim) {
    string temp = input;
    
    vector<string> inner_strings;
    int index = 0;
    while (temp.find("\"") != string::npos || temp.find("\'") != string::npos) {
        int start = 0;
        int end = 0;
        if (temp.find("\"") != string::npos
            && (temp.find("\'") == string::npos || temp.find("\"") < temp.find("\'"))) {
            start = temp.find("\"");
            end = temp.find("\"", start+1);
            if ((size_t) end == string::npos) {
                error = true;
                cerr << "Invalid command - Non-matching quotation mark on \"" << endl;
                return;
            }
        }
        else if (temp.find("\'") != string::npos) {
            start = temp.find("\'");
            end = temp.find("\'", start+1);
            if ((size_t) end == string::npos) {
                error = true;
                cerr << "Invalid command - Non-matching quotation mark on \'" << endl;
                return;
            }
        }
        
        inner_strings.push_back(temp.substr(start+1, end-start-1));
        
        string str_beg = temp.substr(0, start);
        string str_mid = "--str " + to_string(index);
        string str_end = temp.substr(end+1);
        temp = str_beg + str_mid + str_end;
        
        index++;
    }

	size_t i = 0;
	while ((i = temp.find(delim)) != string::npos) {
		commands.push_back(new Command(trim(temp.substr(0, i)), inner_strings));
		temp = trim(temp.substr(i+1));
	}
	commands.push_back(new Command(trim(temp), inner_strings));
}
