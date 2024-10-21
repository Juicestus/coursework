#include <iostream>
#include <string>
#include <sstream>
#include "functions.h"
using std::cin, std::cout, std::endl, std::string, std::istringstream;

int eval(Stack& stack) {
  if (peek(stack) >= '0' && peek(stack) <= '9') {
    return pop(stack) - '0';
  } 
  char opch = pop(stack);
  int lhs = eval(stack);
  int rhs = eval(stack);
  switch (opch) {
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '*': return lhs * rhs;
    case '/': return lhs / rhs;
    default:
      cout << "Invalid operator: " << opch << endl;
      exit(1);
  }
}

int main() {
  // prompt user input
  cout << "Type RPN expression (end with '=')." << endl;
  cout << "> ";
  
  // //TODO: create a command-line interface for calculator GUI

  Stack stack;

  char in = '\0';
  while (in != '=') {
    cin >> in;
    push(stack, in);
  }

  // while (stack.count > 0) {
  //   cout << pop(stack) << " ";
  // }
  pop(stack); // pop = 
  int res = eval(stack);
  cout << "= " << res << endl;

  return 0;
}

