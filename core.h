/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Khushi Arora
Student ID#: 146209234
Email      : karora63@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/



// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Takes integer input from user and guarantees that the Returns is a valid integer number 
int inputInt(void);

// Guarantees that the return integer is greater than 0
int inputIntPositive(void);

// Guarantees that the return integer is within the range(inclusive)
int inputIntRange(int lowerLimit, int upperLimit);

// Guarantee a single character value is entered within the list of valid characters
char inputCharOption(const char charArray[]);

// Guarantee’s a C string value contains the number of characters within the range specified by the 2nd and 3rd arguments 
void inputCString(char* string, int minCharLimit, int maxCharLimit);

// Return a number in (###)###-#### format is number has 10 characters and all integers
void displayFormattedPhone(const char *string);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
