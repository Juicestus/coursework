#ifndef RANKFUNCTIONS_H
#define RANKFUNCTIONS_H

const unsigned int SIZE = 9; // lines in the data
const unsigned int STRING_SIZE = 51; // max 50 characters 1 for plus '\0'

//-------------------------------------------------------
// Name: get_driver_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data gotten from standard in
//---------------------------------------------------------
bool get_driver_data(double timeArray[], char countryArray[][STRING_SIZE], 
		unsigned int numberArray[], char lastnameArray[][STRING_SIZE]);

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[]);

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[]);

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(char ary[][STRING_SIZE]);

//-------------------------------------------------------
// Name: set_rankings
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void set_rankings(const double timeArray[], unsigned int rankArray[]);

//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const char countryArray[][STRING_SIZE],
		const char lastnameArray[][STRING_SIZE], const unsigned int rankArray[]);

//-------------------------------------------------------
// Name: trim
// PreCondition:  string
// PostCondition: returns string with whitespace removed from beginning and end
//---------------------------------------------------------
void trim(char str[STRING_SIZE]);

#endif