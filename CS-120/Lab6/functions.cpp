#include "functions.h"
using std::cin, std::cout, std::endl, std::ostream, std::string;

#define INFO(X)  cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#define INFO_STRUCT(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " count = " << X.count << endl;

/**
 * ----- REQUIRED -----
 * Pushes number to top of stack. If stack is full, then resize stack's array.
 * @param   stack   Target stack.
 * @param   number  Number to push to stack.
 */
void push(Stack& stack, int number) {
  if (stack.count >= stack.capacity) {
    stack.capacity *= 2;
    int* new_array = new int[stack.capacity];
    for (int i = 0; i < stack.count; ++i) {
      new_array[i] = stack.numbers[i];
    }
    delete[] stack.numbers;
    stack.numbers = new_array;
  }
  stack.numbers[stack.count] = number;
  stack.count++;
  INFO_STRUCT(stack);
  INFO(number);
}

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack) {
  // if (stack.count - 1 < stack.capacity / 2) {
  //   stack.capacity *= 2;
  //   int* new_array = new int[stack.capacity];
  //   for (int i = 0; i < stack.count; ++i) {
  //     new_array[i] = stack.numbers[i];
  //   }
  //   delete[] stack.numbers;
  // }

  if (stack.count <= 0) {
    return INT32_MAX;  // stack is empty, return INT32_MAX
  }
  int peeked = stack.numbers[stack.count - 1];
  stack.count--;
  INFO_STRUCT(stack);
  return peeked;
}

/**
 * ----- REQUIRED -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack) {
  if (stack.count <= 0) {
    return INT32_MAX;
  }
  INFO_STRUCT(stack);
  return stack.numbers[stack.count - 1];
}
