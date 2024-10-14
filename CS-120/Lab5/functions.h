#ifndef PASSING_BY_REFERENCE
#define PASSING_BY_REFERENCE

struct example {
	int value = 2;
};

void function_one(int, int&);
void function_two(example&);
void function_three(int* k, int& l);
void function_four(int*, int, int&, int&);

#endif