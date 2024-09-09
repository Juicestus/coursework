#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
    int i;
    for (i = 0; str[i] != 0; i++);
    return i;
}

unsigned int find(char str[], char character) {
    int i;
    for (i = 0; str[i] != 0 && str[i] != character; i++);
    return i;
}

bool equalStr(char str1[], char str2[]) {
    int i;
    for (i = 0; str1[i] != 0 && str2[i] != 0; i++)
        if (str1[i] != str2[i]) return false;
    return str1[i] == str2[i];
}
