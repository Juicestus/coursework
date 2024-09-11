#include <iostream>
#include <iomanip>
#include <cstring>
#include "rank_functions.h"

using std::cin, std::cout, std::endl;
    
//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
{
    for (unsigned int i = 0; i < SIZE; i++) ary[i] = 0.0;
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
{
    for (unsigned int i = 0; i < SIZE; i++) ary[i] = 0;
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(char ary[][STRING_SIZE])
{
    for (unsigned int i = 0; i < SIZE; i++) strcpy(ary[i], "N/A");
}

//-------------------------------------------------------
// Name: trim
// PreCondition:  the cstring
// PostCondition: whitespace has been removed from beginning and end of string
//---------------------------------------------------------
void trim(char str[STRING_SIZE]) 
{
    char* p = str;
    int l = strlen(p);
    while (isspace(p[l - 1])) p[--l] = 0;
    while (*p && isspace(*p)) ++p, --l;
    memmove(str, p, l + 1);
}

//-------------------------------------------------------
// Name: get_driver_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_driver_data(double times[], char countries[][STRING_SIZE], 
		unsigned int nums[], char names[][STRING_SIZE]) 
{


// #define ensure(C) if (!(C)) { std::cout << __FILE__ << ":" << __LINE__ << "\n"; return false; } // debug
#define ensure(C) if (!(C)) { return false; }

  for (unsigned int i = 0; i < 9; i++) {
        double time;
        std::cin >> time;
        ensure(time > 0);
        times[i] = time;

        char country[STRING_SIZE];
        std::cin >> country;
        trim(country);
        ensure(strlen(country) == 3);
        for (int i = 0; i < 3; i++) ensure(std::isupper(country[i]));
        strcpy(countries[i], country);
        
        int num;
        std::cin >> num;
        ensure(num > 0);
        ensure(num < 100);
        nums[i] = num;
    
        char name[STRING_SIZE];
        std::cin >> name;
        trim(name);
        for (std::size_t i = 0; i < strlen(name); i++) ensure(std::isalpha(name[i]) || std::isspace(name[i]));
        strcpy(names[i], name);
    
        // printf("%f %s %d %s\n", times[i], countries[i], nums[i], names[i]); // For debugging
    }
  return true; // set so it will compile
}

//-------------------------------------------------------
// Name: set_rankings
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void set_rankings(const double times[], unsigned int ranks[])
{
    double t_floor = 0; // timefloor
    for (unsigned int r = 0; r < SIZE; r++) {
        double smol = 100000000;
        unsigned int smol_i = 0;
        for (unsigned int i = 0; i < SIZE; i++) {
            if (times[i] > t_floor && times[i] < smol) {
                smol = times[i];
                smol_i = i;
            }
        }
        ranks[smol_i] = r;
        t_floor = smol;
        //printf("%d %f\n", r, t_floor); // debug
    }
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const char countryArray[][STRING_SIZE],
		const char lastnameArray[][STRING_SIZE], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}
