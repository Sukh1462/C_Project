/*
+---------------------------------+
| ASSIGNMENT 2 MILESTONE 3        |
+---------------------------------+
| NAME: SUKHMANPREET KAUR MALHI   |
| EMAIL: skmalhi2@myseneca.ca     |
| SECTION: NBB                    |
+---------------------------------+
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"
#include "ticket.h"


void getAccount(struct Account* ptrAccount) {
	/*printf("Account Data: New Record\n");
	printf("----------------------------------------\n");
	printf("Enter the account number: ");
	ptrAccount->accountNumber = getInteger();*/
	//printf("\n");
	printf("New Account Data (Account#:%d)\n", ptrAccount->accountNumber);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	ptrAccount->accountType = getCharOption("AC");
	//printf("number is: %d \n type is: %c\n", ptrAccount->accountNumber, ptrAccount->accountType);
}



void getUserLogin(struct UserLogin* ptrUserLogin) {
	printf("\n");
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	int flag = 0;
	do {
		printf("Enter user login (10 chars max): ");
		getCString(ptrUserLogin->name, 1, 10);
		int s = 0, spaceCheck = 0, length;

		length = strlen(ptrUserLogin->name);


		for (s = 0; s < length; s++) {
			spaceCheck = isspace(ptrUserLogin->name[s]);
			if (spaceCheck) {
				printf("ERROR:  The user login must NOT contain whitespace characters.\n");
				break;
			}
		}
		if (spaceCheck == 0) {
			flag = 1;
		}
	} while (flag == 0);

	printf("Enter the display name (30 chars max): ");
	getCString(ptrUserLogin->displayName, 1, 30);


	int s = 0, done = 0;
	do {
		int digitCheck = 0, upperCaseCheck = 0, lowerCaseCheck = 0, symbolCheck = 0, length = 0;
		printf("Enter the password (must be 8 chars in length): ");
		getCString(ptrUserLogin->password, 8, 8);
		length = strlen(ptrUserLogin->password);
		for (s = 0; s < length; s++) {
			if (isdigit(ptrUserLogin->password[s])) {
				digitCheck++;
			}
			if (isupper(ptrUserLogin->password[s])) {
				upperCaseCheck++;
			}
			if (islower(ptrUserLogin->password[s])) {
				lowerCaseCheck++;
			}
			if ((ptrUserLogin->password[s] == '!') || (ptrUserLogin->password[s] == '@') || (ptrUserLogin->password[s] == '#') || (ptrUserLogin->password[s] == '$') || (ptrUserLogin->password[s] == '%') || (ptrUserLogin->password[s] == '^') || (ptrUserLogin->password[s] == '&') || (ptrUserLogin->password[s] == '*')) {
				symbolCheck++;
			}
		}
		if ((digitCheck == 2) && (lowerCaseCheck == 2) && (upperCaseCheck == 2) && (symbolCheck == 2)) {

			done = 1;
		}
		else {
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
			done = 0;

		}
	} while (done == 0);

	//printf("loginname is %s \n displayname is %s \n password is %s\n", ptrUserLogin->name, ptrUserLogin->displayName, ptrUserLogin->password);
}

void getDemographic(struct Demographic* ptrDemographic) {
	int presentYear;
	char country[31];
	int length, i;
	printf("\n");
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	presentYear = currentYear();
	int lowerClass;
	int upperClass;
	lowerClass = presentYear - 110;
	upperClass = presentYear - 18;
	printf("Enter birth year (current age must be between 18 and 110): ");
	ptrDemographic->birthYear = getIntFromRange(lowerClass, upperClass);
	printf("Enter the household Income: $");
	ptrDemographic->income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	//getCString(ptrDemographic->country, 1, 30);
	getCString(country, 1, 30);
	//printf("\n");
	length = strlen(country);
	for (i = 0; i < length; i++) {
		ptrDemographic->country[i] = toupper(country[i]);
	}
	ptrDemographic->country[length] = '\0';
	//ptrDemographic->country[length] = '\0';

}

void updateAccount(struct Account* AccountPointer) {
	int selection, exitFlag = 0;
	char newAccType;
	printf("\n");
	do {
		printf("Account: %d - Update Options\n", AccountPointer->accountNumber);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", AccountPointer->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		if (selection == 1) {
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			newAccType = getCharOption("AC");
			AccountPointer->accountType = newAccType;
		}
		if (selection == 2) {
			updateUserLogin(&AccountPointer->UserLoginVariable);
			printf("\n");
		}
		if (selection == 3) {
			updateDemographic(&AccountPointer->DemographicVariable);
			printf("\n");
		}
		if (selection == 0) {
			printf("\n");
			exitFlag = 1;
		}
	} while (exitFlag == 0);

}

void updateUserLogin(struct UserLogin* UserLoginPointer) {
	int selection, flag = 1;
	do {
		printf("\nUser Login: %s - Update Options\n", UserLoginPointer->name);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", UserLoginPointer->displayName);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 2);

		if (selection == 1) {
			printf("\nEnter the display name (30 chars max): ");
			getCString(UserLoginPointer->displayName, 1, 30);
		}
		else if (selection == 2) {
			int s = 0, done = 0;
			printf("\n");
			do {
				int digitCheck = 0, upperCaseCheck = 0, lowerCaseCheck = 0, symbolCheck = 0, length = 0;
				printf("Enter the password (must be 8 chars in length): ");
				getCString(UserLoginPointer->password, 8, 8);
				length = strlen(UserLoginPointer->password);
				for (s = 0; s < length; s++) {
					if (isdigit(UserLoginPointer->password[s])) {
						digitCheck++;
					}
					if (isupper(UserLoginPointer->password[s])) {
						upperCaseCheck++;
					}
					if (islower(UserLoginPointer->password[s])) {
						lowerCaseCheck++;
					}
					if ((UserLoginPointer->password[s]=='!')|| (UserLoginPointer->password[s] == '@') || (UserLoginPointer->password[s] == '#') || (UserLoginPointer->password[s] == '$') || (UserLoginPointer->password[s] == '%') || (UserLoginPointer->password[s] == '^') || (UserLoginPointer->password[s] == '&') || (UserLoginPointer->password[s] == '*')) {
						
						symbolCheck++;
					}
				}
				if ((digitCheck == 2) && (lowerCaseCheck == 2) && (upperCaseCheck == 2) && (symbolCheck == 2)) {

					done = 1;
				}
				else {
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: !@#$%%^&*\n");
					done = 0;

				}
			} while (done == 0);
		}
		else if (selection == 0) {
			flag = 0;
		}
	} while (flag == 1);
}

void updateDemographic(struct Demographic* DemographicPointer) {
	int selection, flag = 1;
	char country[31];
	double newIncome;
	int length, i;
	do {
		printf("\nDemographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", DemographicPointer->income);
		printf("2) Country (current value: %s)\n", DemographicPointer->country);
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 2);

		if (selection == 1) {
			printf("\nEnter the household Income: $");
			newIncome = getPositiveDouble();
			DemographicPointer->income = newIncome;

		}
		if (selection == 2) {
			printf("\nEnter the country (30 chars max.): ");
			
			getCString(country, 1, 30);
			
			length = strlen(country);
			for (i = 0; i < length; i++) {
				DemographicPointer->country[i] = toupper(country[i]);
			}
			DemographicPointer->country[length] = '\0';
		}
		if (selection == 0) {
			flag = 0;
		}
	} while (flag == 1);
}

//int loadAccounts(struct Account accounts[], const int ACCOUNT_SIZE) {
//	printf("ienf");
//	return 1;
//}