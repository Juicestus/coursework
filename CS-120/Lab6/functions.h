#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <sstream>

/**
 * The stack data type that is initially empty and has a singleton capacity.
 */
struct Stack {
	int* numbers = new int[1] {};	// array of numbers
	int capacity    = 1;       	// capacity of array
	int count       = 0;		// number of elements in array
};

/**
 * ----- REQUIRED -----
 * Pushes number to top of stack. If stack is full, then resize stack's array.
 * @param   stack   Target stack.
 * @param   number  Number to push to stack.
 */
void push(Stack& stack, int number);

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack);

/**
 * ----- REQUIRED -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack);

#endif