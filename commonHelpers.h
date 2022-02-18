/*
__________________________________________________________________________
              ******ASSIGNMENT-2 (MILESTONE-3)******
   -----------------------------------------------------------------
NAME: SUKHMANPREET KAUR MALHI
STUDENT ID: 134893205
EMAIL: skmalhi2@myseneca.ca
COURSE: IPC144
SECTION: NBB
__________________________________________________________________________
*/

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
//#include "accountTicketingUI.h"

int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
double getDouble(void);
double getPositiveDouble(void);
int getIntFromRange(int lowerBound, int upperBound);
char getCharOption(const char validCharacters[]);
void getCString(char stringptr[], int minChar, const int maxChar);
//new
int getPositiveOrZeroInt(void);



#endif  



