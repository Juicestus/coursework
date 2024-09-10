/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele
Author: J. Michael Moore

Input information format
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include <cstring>
#include "rank_functions.h"

using std::cin; using std::cout; using std::endl;

#define ER(C) if (C) { cout << "Bad input\n"; return 1; } 

int main()
{
    double times[SIZE];
    char countries[SIZE][STRING_SIZE];
    unsigned int nums[SIZE];
    char names[SIZE][STRING_SIZE];
    
    prep_double_array(times);
    prep_string_array(countries);
    prep_unsigned_int_array(nums);
    prep_string_array(names);

    for (unsigned int i = 0; i < 9; i++) {
        double time;
        std::cin >> time;
        ER(time <= 0);
        times[i] = time;

        char country[STRING_SIZE];
        std::cin >> country;
        strcpy(countries[i], country);
        
        int num;
        std::cin >> num;
        ER(num < 0);
        nums[i] = num;
    
        char name[STRING_SIZE];
        std::cin >> name;
        strcpy(names[i], name);

        printf("%f %s %d %s\n", times[i], countries[i], nums[i], names[i]);
    }

    // if unable to load runner data
    //   1) output "Bad input" to standard out
    //   2) exit program by returning 1

    // TODO: determine ranking, notice the rank array receives the results

    // TODO: Output results

    // this is not required in C++ but many people still explitly add it
    return 0; 
}

