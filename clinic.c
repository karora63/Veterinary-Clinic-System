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

// System Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User Defined Libraries
// Milestone 1 Functions
#include "core.h"
// Milestone 2 Functions
#include "clinic.h"


// Function to sort the values using bubble sort
void sort(struct Appointment appoints[], int max) {
    int i, j;
    struct Appointment temp;

    // Storing all the date and time values in minutes for comparison
    for (i = 0; i < max; i++) {
        appoints[i].time.min = (appoints[i].date.year * 12 * 30 * 24 * 60) + (appoints[i].date.month * 30 * 24 * 60) + (appoints[i].date.day * 24 * 60) + (appoints[i].time.hour * 60) + appoints[i].time.min;
    }

    // Using bubble sort to compare minutes and then swap the structs
    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appoints[j].time.min > appoints[j + 1].time.min)
            {
                temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
            }
        }
    }

    // Converting total minutes back to minutes
    for (i = 0; i < max; i++) {
        appoints[i].time.min = appoints[i].time.min - (appoints[i].date.year * 12 * 30 * 24 * 60) - (appoints[i].date.month * 30 * 24 * 60) - (appoints[i].date.day * 24 * 60) - (appoints[i].time.hour * 60);
    }

}

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) 
{
    int i; // Used in loop

    if (patient == NULL) // If structure is empty
    {
        printf("*** No records found ***\n");
    }
    else
    {
        if (fmt == FMT_TABLE) // Display table header when input fmt if for tables
        {
            displayPatientTableHeader();
        }

        // Loop to display patient data
        for (i = 0; i < max; i++) 
        {
            if (patient[i].patientNumber != 0) // Non empty record
            {
                displayPatientData(&patient[i], fmt);
            }
        }
        printf("\n");
    }
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) 
{
    // Variable Decleration
    int searchOption;

    // Loop until input is 0
    do
    {
        // Print statements
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf(" %d", &searchOption); // Input
        printf("\n");

        // User input's response
        if (searchOption == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (searchOption == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
    } while (searchOption != 0);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) 
{
    int i; // Used in loop

    // Loop to find empty patient element
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0) // If empty element
        {
            patient[i].patientNumber = nextPatientNumber(patient, max); // Get and add patient Unique number
            inputPatient(&patient[i]); // Add patient's detail

            printf("*** New patient record added ***\n\n"); // Process done
            
            return; // Callout
        }
        
    }
    
    // No empty element found
    printf("ERROR: Patient listing is FULL!\n\n");

    return;

}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) 
{
    // Variable Decleration
    int patientNum; // Stores patient unique number
    int patientIndex; // Stores patient record index

    // Patient Number Input
    printf("Enter the patient number: ");
    scanf(" %d", &patientNum); // Input
    printf("\n");

    // Find index of record
    patientIndex = findPatientIndexByPatientNum(patientNum, patient, max);

    if (patientIndex == -1) // Record not found
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else // Record found
    {
        menuPatientEdit(&patient[patientIndex]);
    }
    
    // Fuction callout
    return;

}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) 
{
    // Variable Decleration
    int patientNum; // Stores patient unique number
    int patientIndex; // Stores patient record index
    char userConformation[4]; // Stores user choice to continue

    // Patient Number Input
    printf("Enter the patient number: ");
    scanf(" %d", &patientNum); // Input
    printf("\n");

    // Find index of record
    patientIndex = findPatientIndexByPatientNum(patientNum, patient, max);

    if (patientIndex == -1) // Record not found
    {
        printf("ERROR: Patient record not found!\n\n");
	getchar();
    }
    else // Record found
    {
        displayPatientData(&patient[patientIndex], FMT_FORM); // Display record information

        // Conformation Input
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        getchar();

        // Loop until input is valid
        do
        {
            fgets(userConformation, sizeof(userConformation), stdin); // Read input using fgets
            
            if (strlen(userConformation) != 2) // More than 1 character input
            {
                printf("ERROR: Character must be one of [yn]: ");
                getchar();
            }
        } while (strlen(userConformation) != 2); // Input is single character
        
        // Check to proceed deletion
        if (userConformation[0] == 'n')
        {
            printf("Operation aborted.\n\n"); // Do not delete data
        }
        else // Delete date
        {
            patient[patientIndex].patientNumber = 0; // Patient Number set to 0
            printf("Patient record has been removed!\n\n");
        }
    }
    
    // Fuction callout
    return;

}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data) 
{
    // Variable Decleration
    int i, j; // Used in Variables

    // Sort the data 
    sort(data->appointments, data->maxAppointments);

    // Display the patients geader
    displayScheduleTableHeader(NULL, 1);

    // Display the data
    for (i = 0; i < data->maxAppointments; i++) 
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            if (data->appointments[i].patientNumber == data->patients[j].patientNumber) 
            {
                displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }
        }
    }
    printf("\n");
    
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) 
{
    // Variable Decleration
    int lastDay;
    int i, j; // Used in loops
    struct Date date;
    
    // Year Input
    printf("Year        : ");
    date.year = inputIntPositive();
    

    // Month Input
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);
   


    // Determine last Day of the month
    if (date.month == 4 || date.month == 6 || date.month == 9 ||  date.month == 11) 
    {
        lastDay = 30;
    }
    else if (date.month == 2) // February
    {
        if (date.year % 4 == 0) // Check Leap Year
        {
            lastDay = 29;
        }
        else
        {
            lastDay = 28;
        }
    }
    else
    {
        lastDay = 31;
    }

    // Day Input
    printf("Day (1-%d)  : ", lastDay);
    date.day = inputIntRange(1, lastDay);
    printf("\n");
    

    // Sort the data
    sort(data->appointments, data->maxAppointments);
    
    // Displaying the patients header
    displayScheduleTableHeader(&date, 0);

    // Loop to display data
    for (i = 0; i < data->maxAppointments; i++) 
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            // Display Data if Paitent Id, year, month and day Matches 
            if (data->appointments[i].patientNumber == data->patients[j].patientNumber && data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day) 
            {
                displayScheduleData(&data->patients[j], &data->appointments[i], 0);
            }
        }
    }
    printf("\n");

}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment *app, int maxAppointments, struct Patient *pt, int maxPatients)
{
    // Declare temporary structures
    struct Date date;
    struct Time time;

    // Variable Decleration
    int lastDay;
    int patientNumber, index; // Stores user Input
    int slotFlag = 1; // If flag = 0, loops stops

    // Patient Number input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    
    // Find index of input
    index = findPatientIndexByPatientNum(patientNumber, pt, maxPatients);

    // Main Logic
    if (index >= 0) // Run if index is valid
    {
        while (slotFlag) // While slotFlag == 1
        {
            // Year Input
            printf("Year        : ");
            date.year = inputIntPositive();

            // Month Input
            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            // Determine last Day of the month
            if (date.month == 4 || date.month == 6 || date.month == 9 ||  date.month == 11) 
            {
                lastDay = 30;
            }
            else if (date.month == 2) // February
            {
                if (date.year % 4 == 0) // Check Leap Year
                {
                    lastDay = 29;
                }
                else
                {
                    lastDay = 28;
                }
            }
            else
            {
                lastDay = 31;
            }

            // Day Input
            printf("Day (1-%d)  : ", lastDay);
            date.day = inputIntRange(1, lastDay);
            
            // Hour Input
            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            // Minute Input
            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            // Check if Slot is available
            if (timeSlotAvailable(date, time, app, maxAppointments)) // if function returns 0, time slot not available
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else 
            {
                // Loop until time input is valid
                do
                {
                    // Error print
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);

                    // Hour Input
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0,23);

                    // Minute Input
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0,59);

                } while ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.hour == END_HOUR && time.min > 0) || (time.min % MINUTE_INTERVAL != 0));

                // Slot found
                slotFlag = 0;
            }
        }

        // Finds index of next available slot
        index = nextSlotAvailable(app, maxAppointments); 

        // Assign values to next available Slot
        app[index].date = date;
        app[index].time = time;
        app[index].patientNumber = patientNumber;

        // Success print
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else // If patient Id was invalid
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
    return;
}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment *app, int maxAppointments, struct Patient *pt, int maxPatients) 
{
   // Variable Decleration
    int lastDay, patientNumber;
    struct Date date;
    int index, appointmentIndex; // Stores index of data
    
    // Patient Number Input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, pt, maxPatients);

    if (index >= 0)
    {
        // Year Input
        printf("Year        : ");
        date.year = inputIntPositive();

        // Month Input
        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        // Determine last Day of the month
        if (date.month == 4 || date.month == 6 || date.month == 9 ||  date.month == 11) 
        {
            lastDay = 30;
        }
        else if (date.month == 2) // February
        {
            if (date.year % 4 == 0) // Check Leap Year
            {
                lastDay = 29;
            }
            else
            {
                lastDay = 28;
            }
        }
        else
        {
            lastDay = 31;
        }

        // Day Input
        printf("Day (1-%d)  : ", lastDay);
        date.day = inputIntRange(1, lastDay);
        printf("\n"); 

        // Find appointment Index
        appointmentIndex = validAppointment(patientNumber, date, app, maxAppointments);

        // Check if Index is valid
        if(appointmentIndex >= 0)
        {

            // Display Data
            displayPatientData(&pt[index],FMT_FORM);

            // Conformation to remove data
            printf("Are you sure you want to remove this appointment (y,n): ");
            
            // Get user input for conformation
            if(inputCharOption("yn") == 'y') 
            {
                // Remove Data
                app[appointmentIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }
            else 
            {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
        clearInputBuffer();
    }
    else // Patient ID not found
    {
        printf("ERROR: Patient record not found!\n\n");
    }

    return;

}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) 
{
    // Variable Decleration
    int patientNumber; 
    int patientIndex;

    // User Input
    printf("Search by patient number: ");
    scanf(" %d", &patientNumber);
    printf("\n");

     // Function to find index of record and -1 if not found
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (patientIndex == -1) // Patient element not found
    {
        printf("*** No records found ***\n");
    }
    else // Element present
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);
        
    }
    printf("\n");

    // Ending Statements
    clearInputBuffer();
    suspend();

    return;
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) 
{
    // Variable Decleration
    char phoneNumber[PHONE_LEN + 1];
    int phoneNumFlag = 0;
    int i; // Used in loop

    // User Input 
    clearInputBuffer();
    printf("Search by phone number: ");
    scanf("%[^\n]", phoneNumber); // Input
    printf("\n");

    // Loop to check if Phone number is present
    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0) // Check
        {
            if (phoneNumFlag == 0) // Display header for the first time only
            {
                displayPatientTableHeader();  
            }
            displayPatientData(&patient[i], FMT_TABLE); // Display data
            phoneNumFlag++;
        }
        
    }

    if (phoneNumFlag == 0) // If no record was found
    {
        displayPatientTableHeader(); 
        printf("\n*** No records found ***\n");
    }
    
    // Ending
    printf("\n");
    clearInputBuffer();
    suspend();

    // Function callout
    return;
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) 
{
    // Variable Decleration
    int largestPatientNum; // Stores largest patient num
    int i = 0;

    largestPatientNum = patient[i].patientNumber; // Initial value

    // Loop to find maximum patient Num
    for (i = 1; i < max; i++)
    {
        if (patient[i].patientNumber > largestPatientNum) // Bigger patient num found
        {
            // Latest biggest patient num
            largestPatientNum = patient[i].patientNumber; 
        }
        
    }

    return largestPatientNum + 1; // returns latest patient num
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) 
{
    int i; // Used in loop

    // Loop to check if patient number exists
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber) // If patient number matches return index
        {
            return i;
        }
        
    }
    
    return -1; // Patient not found, return -1
}

// Checks to see whether a time slot is available
int timeSlotAvailable(struct Date date, struct Time time, struct Appointment* app, int maxAppointments) 
{
    // Variable Decleration
    int i; // Used in loops
    int SlotAvailable = 0; // If 1 means slot is available

    for (i = 0; i < maxAppointments; i++) 
    {
        // Check if Slot is available
        if (date.year == app[i].date.year && date.month == app[i].date.month && date.day == app[i].date.day && time.hour == app[i].time.hour && time.min == app[i].time.min) 
        {
            // Data matches
            SlotAvailable = 1;
        }
    }

    // Return if slot available or not
    return SlotAvailable;
}

// Checks to see which is the next slot that is available and return the index
int nextSlotAvailable(struct Appointment* app, int maxAppointments) 
{
    // Variable Decleration
    int index = 0; // Used in loop
    int availableFlag = 0;

    // Loop to find if appoint is free
    for (index = 0; index < maxAppointments && availableFlag == 0; index++)
    {
        // Check if appoint is available
        if (app[index].patientNumber < 1) 
        {
            availableFlag = 1;
        }
    }

    // Return index of next slot
    return index;
}

// Checks to see if an appointment is valid
int validAppointment(int patientNumber, struct Date date, struct Appointment *app, int maxAppointments) 
{
    // Variable Decleration
    int i = 0; // Used in Loop
    int validFlag = 0; // If Flag = 1 means data found

    // Loop to Find data
    for (i = 0; i < maxAppointments && validFlag == 0; i++)
    {
        // Check if data matches
        if ((app[i].patientNumber == patientNumber) && (app[i].date.day == date.day) && (app[i].date.month == date.month) && (app[i].date.year == date.year)) {
            validFlag = 1; 
        }
    }
    
    return i - 1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) 
{
    // Print Statements
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);

    printf("Name  : "); // Name input
    inputCString(patient->name, 1, NAME_LEN); // Input using core.c function
    putchar('\n');
    
    // Phone input
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) 
{
    // Variable Decleration
    int phoneDesc; // Stores phone description
    char phoneNum[PHONE_LEN + 2]; // Stores phone number

    // Input prints
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");

    // Selection Input
    printf("Selection: ");
    scanf(" %d", &phoneDesc);
    printf("\n");

    // Different cases for different Selection
    switch (phoneDesc)
    {
    case 1:
        // Copy the Chosen Description 
        strncpy(phone->description, "CELL", PHONE_DESC_LEN);

        // Display description
        printf("Contact: %s\n", phone->description);

        // Phone Input
        clearInputBuffer();
        printf("Number : ");

        // Loop until input is valid length number 
        do
        {
            // Scan number
            scanf("%[^\n]", phoneNum);

            // Invalid Length
            if (strlen(phoneNum) != 10)
            {
                printf("Invalid 10-digit number! Number: ");
                getchar();
            }
            
        } while (strlen(phoneNum) != 10);

        // Copy number
        phoneNum[PHONE_LEN] = '\0';
        strncpy(phone->number, phoneNum, PHONE_LEN);
        phone->number[PHONE_LEN] = '\0';
        printf("\n");
        clearInputBuffer();
        break;

    case 2:
        // Copy the Chosen Description 
        strncpy(phone->description, "HOME", PHONE_DESC_LEN);

        // Display description
        printf("Contact: %s\n", phone->description);

        // Phone Input
        clearInputBuffer();
        printf("Number : ");

        // Loop until input is valid length number 
        do
        {
            // Scan number
            scanf("%[^\n]", phoneNum);

            // Invalid Length
            if (strlen(phoneNum) != 10)
            {
                printf("Invalid 10-digit number! Number: ");
                getchar();
            }
            
        } while (strlen(phoneNum) != 10);

        // Copy number
        phoneNum[PHONE_LEN] = '\0';
        strncpy(phone->number, phoneNum, PHONE_LEN);
        phone->number[PHONE_LEN] = '\0';
        printf("\n");
        clearInputBuffer();
        break;

    case 3:
        // Copy the Chosen Description 
        strncpy(phone->description, "WORK", PHONE_DESC_LEN);

        // Display description
        printf("Contact: %s\n", phone->description);

        // Phone Input
        clearInputBuffer();
        printf("Number : ");

        // Loop until input is valid length number 
        do
        {
            // Scan number
            scanf("%[^\n]", phoneNum);

            // Invalid Length
            if (strlen(phoneNum) != 10)
            {
                printf("Invalid 10-digit number! Number: ");
                getchar();
            }
            
        } while (strlen(phoneNum) != 10);

        // Copy number
        phoneNum[PHONE_LEN] = '\0';
        strncpy(phone->number, phoneNum, PHONE_LEN);
        phone->number[PHONE_LEN] = '\0';
        printf("\n");
        clearInputBuffer();
        break;

    case 4:
        // Copy the Chosen Description 
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        *phone->number = 0; // Because Description is "To be determined"

        break;
    
    default:
        // Any value other than 1,2,3 or 4
        printf("Error:\n");
        break;
    }
    
    // Function Callout
    return;

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) 
{
    // 1024|Shaggy Yanson|CELL|3048005191

    // File variable
    FILE *file;

    // Variable Decleration
    int i; // Used in loops
    int count = 0; // Stores number of data stored


    // Open file
    file = fopen(datafile,"r");

    // The feof() function returns a nonzero value if and only if the EOF flag is set; otherwise, it returns 0.
    for (i = 0; (i < max) && (feof(file) == 0); i++) // Loop to get rows
    {
        // Read values from file
        fscanf(file, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number);       

        // Increment count until EOF not reached
        if (!feof(file)) 
        {
            count++;
        }
        
    }

    // Close File
    fclose(file);

    // Return number of rows
    return count;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) 
{
    // 1040,2024,2,29,13,0
    // Patient number, Appointment year, Appointment month, Appointment day, Appointment hour, Appointment minute

    // File variable
    FILE *file;

    // Variable Decleration
    int i; // Used in loops
    int count = 0; // Stores number of data stored


    // Open file
    file = fopen(datafile,"r");

    // The feof() function returns a nonzero value if and only if the EOF flag is set; otherwise, it returns 0.
    for (i = 0; (i < max) && (feof(file) == 0); i++) // Loop to get rows
    {
        // Read values from file
        fscanf(file, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);
        
        // Increment count until EOF not reached
        if (!feof(file)) {
            count++;
        }
        
    }

    // Close File
    fclose(file);

    // Return number of rows
    return count;
}

