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
    
    if (!get_driver_data(times, countries, nums, names)) {
        cout << "Bad input";
        return 1;
    }
      
    // TODO: determine ranking, notice the rank array receives the results
    unsigned int ranks[SIZE];
    prep_unsigned_int_array(ranks);
    
    set_rankings(times, ranks);
    
    print_results(times, countries, names, ranks);

    // this is not required in C++ but many people still explitly add it
    return 0; 
}

