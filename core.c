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

#define _CRT_SECURE_NO_WARNINGS

// System library
#include <stdio.h>
#include <string.h>

// User-defined library
#include "core.h"
#include "clinic.h"


// Clear the standard input buffer 
void clearInputBuffer(void) 
{ 
    
    // Discard all remaining char's from the standard input buffer: 
    while (getchar() != '\n' )
    { 
        ; // do nothing! 
    } 
} 
 
// Wait for user to input the "enter" key to continue 
void suspend(void) 
{ 
    printf("<ENTER> to continue..."); 
    clearInputBuffer(); 
    putchar('\n'); 
}

// Takes integer input from user and guarantees that the Returns is a valid integer number 
int inputInt(void)
{
    // Variable Decleration
    int flag = 1; // Flag 0 means all conditions are met
    int userInput; // Stores user input
    char newLineChar; // if new character after input is newline = input is integer

    // Loop until input is integer 
	do 
    {
		scanf(" %d%c", &userInput, &newLineChar); // Input

		if (newLineChar != '\n') // Input is not a number
		{
            clearInputBuffer(); //  Discards all remaining char's from the standard input buffer
			printf("Error! Input a whole number: ");
		}
		else
		{  
			flag = 0; // All conditins are met
		}
	} while (flag); // Loop until flag == 1

    return userInput;
}

// Guarantees that the return integer is greater than 0
int inputIntPositive(void)
{
    // Variable Decleration
    int flag = 1; // Flag 0 means all conditions are met
    int userInput; // Stores user input
    char newLineChar; // if new character after input is newline = input is integer

    // Loop until input is positive 
    do 
    {
        scanf(" %d%c", &userInput, &newLineChar); // Input

        if (newLineChar != '\n') // Input is not a number
		{
            clearInputBuffer(); //  Discards all remaining char's from the standard input buffer
			printf("Error! Input a whole number: ");
		}
        else if (userInput <= 0) // Input is negative
        {
            printf("ERROR! Value must be > 0: ");
        }
        else
        {
            flag = 0; // All conditins are met
        }
    } while (flag); // Loop until flag == 1


    // Function returns the Positive input
    return userInput;

}

// Guarantesss that the return integer is within the range(inclusive)
int inputIntRange(int lowerLimit, int upperLimit)
{
    // Variable Decleration
    int flag = 1; // Flag 0 means all conditions are met
    int userInput; // Stores user input
    char newLineChar; // if new character after input is newline = input is integer

    // Loop until input is positive 
    do 
    {
        scanf(" %d%c", &userInput, &newLineChar); // Input

        if (newLineChar != '\n') // Input is not a number
		{
            clearInputBuffer(); //  Discards all remaining char's from the standard input buffer
			printf("Error! Input a whole number: ");
		}
        else if (userInput > upperLimit || userInput < lowerLimit)// Input is out of range
        {
            
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerLimit, upperLimit);
           
        }
        else // All conditins are met
        {
            flag = 0; 
        }
    } while (flag); // Loop until flag == 1


    // Function returns the integer
    return userInput;
}

// Guarantee a single character value is entered within the list of valid characters
char inputCharOption(const char charArray[])
{
    // Variable Decleration
    int flag = 1; // Flag 0 means all conditions are met
    char userInput; // Stores user input
    int i; // Used in for loop

    do
    {
        // User input
        scanf(" %c", &userInput);

        // Loop to check if input is in the Array
        for (i = 0; charArray[i] != '\0'; i++) // Loop until Null terminator arrives
        {
            if (charArray[i] == userInput) // Input is Valid
            {
                flag = 0; // Flag changed
            }
        }
        
        // Invalid Character
        if (flag) // if flag == 1
        {
            printf("ERROR: Character must be one of [%s]: ", charArray); // Error p
        }
        
    } while (flag);
    
    // Function returns valid character
    return userInput;
}

// Guarantee’s a C string value contains the number of characters within the range specified by the 2nd and 3rd arguments 
void inputCString(char *stringValue, int minCharLimit, int maxCharLimit)
{
    // Variable Decleration
    int flag = 1; // Flag 0 means all conditions are met
    int stringLength = 0;
    int i = 0; // Used in for loop
    char stringInput[20] = { "\0" }; // Stores user input
    
    do
    {
        // Loop to reset final string value
        for (i = 0; i < NAME_LEN; i++)
        {
            stringValue[i] = '\0'; // change to null value
        }
        
        scanf("%[^\n]", stringInput); // Input
        clearInputBuffer();
        //getchar(); // Consume newline character from the input buffer
        
        // Loop to Find string Length
        stringLength = 0; // reset string length
        for (i = 0; stringInput[i] != '\0'; i++) // Loop until Null terminator arrives
        {
            stringLength++; // Update String 
        }

        //If string skips scanf i.e string is NULL (BUG)
        if (stringInput[0] == '\0' || stringInput[0] == '\n')
        {
            flag = 1; // Set flag to 1 i.e condition not met
        }
        else if ((stringLength > maxCharLimit || stringLength < minCharLimit) && !(stringInput[0] == '\0' || stringInput[0] == '\n'))// Input String is out of range
        {
            // ERROR prints
            if (maxCharLimit == minCharLimit) // Upper and Lower limit are equal
            {
                printf("ERROR: String length must be exactly %d chars: ", maxCharLimit);
            }
            else if (stringLength > maxCharLimit) 
            {
                printf("ERROR: String length must be no more than %d chars: ", maxCharLimit);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", minCharLimit, maxCharLimit);
            }
        }
        else
        {
            
            flag = 0; 
        }

    } while (flag);
    
    // Change argument's value to latest
    for (i = 0; i < stringLength && stringInput[i] != '\0'; i++)
    {
        stringValue[i] = stringInput[i];
    }
    
    // Function returns when input string is valid
    return;
}

// Return a number in (###)###-#### format is number has 10 characters and all integers
void displayFormattedPhone(const char *string)
{
    // Variable Decleration
    int flag = 0; // Flag 0 means all conditions are met
    int stringLength = 0;
    int i; // Used in for loop

    // Check if string is NULL
    if (string == NULL) 
    {
        flag = 1; // Flag changed
    }
    else // String not Null
    {
        // Loop to find String's length
        for (i = 0; string[i] != '\0'; i++) // Loop until Null terminator arrives
        {
            stringLength++; // Length value

            // Used ASCII values to find if character is integer or not
            if (string[i] < '0' || string[i] > '9') 
            {
                flag = 1; // Character not integer
            }
        }
    }
    
    // Final Check to print String
    if (stringLength == 10 && flag == 0) // Valid Number
    {
        // Print number (xxx)xxx-xxxx

        // Print (xxx)
        printf("(");
        for (i = 0; i < 3; i++)
        {
            printf("%c", string[i]);
        }
        printf(")");

        // Print xxx-
        for (i = 3; i < 6; i++)
        {
            printf("%c", string[i]);
        }
        printf("-");

        // Print xxxx
        for (i = 6; i < 10; i++)
        {
            printf("%c", string[i]);
        }
    }
    else // Invalid Number
    {
        printf("(___)___-____");
    }

    // Function call return
    return;
    
}