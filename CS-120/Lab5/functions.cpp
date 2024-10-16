#include <iostream>
#include "functions.h"
using namespace std;

void function_one(int i, int& j) {
    i += 2;
    j++;
}

void function_two(example& e) {
    e.value++;
}

void function_three(int* k, int& l) {
    (*k)++;
    l++;
}

void function_four(int* arr, int size, int& lowest, int& highest) {
    highest = (-2147483647 -1);
    lowest = 2147483647;
    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] + 2;
        if (arr[i] < lowest) {
            lowest = arr[i];
        }
        if (arr[i] > highest) {
            highest = arr[i];
        }
    }
}
