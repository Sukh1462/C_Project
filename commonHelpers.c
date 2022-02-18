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
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"
#include "ticket.h"
#include <string.h>

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

//Function #1
int getInteger(void) {
	int integerValue;
	char newline = 'x';
	do {
		scanf("%d%c", &integerValue, &newline);

		if (newline != '\n') {
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}

	} while (newline != '\n');

	return integerValue;
}

//function #2


int getPositiveInteger(void) {
	int positiveIntegerValue;
	char newline = 'x';
	int flag = 1;
	do {
		scanf("%d%c", &positiveIntegerValue, &newline);
		if (newline == '\n') {
			if (positiveIntegerValue > 0) {
				flag = 0;
			}
			else {

				printf("ERROR: Value must be a positive integer greater than zero: ");
			}


		}
		else {
			clearStandardInputBuffer();
			printf("ERROR: Value must be a positive integer greater than zero: ");

		}


	} while (flag == 1);

	return positiveIntegerValue;

}

//Function #3
double getDouble(void) {
	double doubleValue;
	char newline = 'x';
	do {
		scanf("%lf%c", &doubleValue, &newline);

		if (newline != '\n') {
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}

	} while (newline != '\n');

	return doubleValue;
}

//function #4

double getPositiveDouble(void) {
	double positiveDoubleValue;
	char newline = 'x';
	int flag = 1;
	do {
		scanf("%lf%c", &positiveDoubleValue, &newline);
		if (newline == '\n') {
			if (positiveDoubleValue > 0) {
				flag = 0;
			}
			else {

				printf("ERROR: Value must be a positive double floating-point number: ");
			}
		}
		else {
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}


	} while (flag == 1);

	return positiveDoubleValue;

}

//function #5
int getIntFromRange(int lowerBound, int upperBound) {
	int intFromRangeValue;
	char newline = 'x';
	int flag = 1;
	do {
		newline = 'x';
		//clearStandardInputBuffer();
		scanf("%d%c", &intFromRangeValue, &newline);
		if (newline == '\n') {

			if ((intFromRangeValue >= lowerBound) && (intFromRangeValue <= upperBound)) {
				flag = 0;
			}
			else {
				printf("ERROR: Value must be between %d and %d inclusive: ", lowerBound, upperBound);
				//clearStandardInputBuffer();
				flag = 1;
			}

		}
		else {
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
			flag = 1;

		}

	} while (flag == 1);

	return intFromRangeValue;
}

//function #6
char getCharOption(const char validCharacters[]) {
	char inputchar;
	int lengthOfString, flag = 1;
	//flag1 = 1;
	char newline = 'x';
	do {
		scanf("%c%c", &inputchar, &newline);
		if (newline == '\n') {
			int i = 0;
			/*do {
				if (validCharacters[i] == '\0') {
					lengthOfString = i;
					flag1 = 0;
				}
				i++;
			} while (flag1 == 1);*/
			lengthOfString = strlen(validCharacters);

			for (i = 0; i < lengthOfString; i++) {
				if (inputchar == validCharacters[i])
					flag = 0;
			}
			if (flag == 1) {
				printf("ERROR: Character must be one of [%s]: ", validCharacters);
			}

		}
		else {
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", validCharacters);
		}

	} while (flag == 1);
	return inputchar;
}

//function #7
void getCString(char stringptr[], int minChar, const int maxChar) {

	int lengthOfString = 0;

	int flag1 = 1;
	char stringPointer[1000];

	do {

		//int flag = 1;

		//int i = 0;

		scanf(" %[^\n]c", stringPointer);
		/*do {
			if (stringPointer[i] == '\0') {
				lengthOfString = i;
				flag = 0;
			}
			i++;
		} while (flag == 1);*/
		lengthOfString = strlen(stringPointer);



		if ((lengthOfString < minChar) && (minChar < maxChar)) {
			clearStandardInputBuffer();
			printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
		}
		else if ((lengthOfString > maxChar) && (minChar < maxChar)) {
			clearStandardInputBuffer();
			printf("ERROR: String length must be no more than %d chars: ", maxChar);
		}
		else if ((lengthOfString != minChar) && (minChar == maxChar)) {
			clearStandardInputBuffer();
			printf("ERROR: String length must be exactly %d chars: ", minChar);
		}
		else if ((lengthOfString >= minChar) || (lengthOfString <= minChar)) {

			flag1 = 0;
		}

	} while (flag1 == 1);

	/*int j;
	for (j = 0; j < lengthOfString + 1; j++) {
		stringptr[j] = stringPointer[j];
	}*/
	strcpy(stringptr, stringPointer);

}

int getPositiveOrZeroInt(void) {
	int positiveOrZeroIntegerValue;
	char newline = 'x';
	int flag = 1;
	do {
		scanf("%d%c", &positiveOrZeroIntegerValue, &newline);
		if (newline == '\n') {
			if (positiveOrZeroIntegerValue >= 0) {
				flag = 0;
			}
			else {

				/*printf("ERROR: Value must be a positive integer greater than zero: ");
			}*/
				printf("ERROR: Value must be positive or zero: ");
			}
		}
		else {
			clearStandardInputBuffer();
			/*printf("ERROR: Value must be a positive integer greater than zero: ");*/
			printf("ERROR: Value must be positive or zero: ");
		}


	} while (flag == 1);

	return positiveOrZeroIntegerValue;



}




