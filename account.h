#ifndef ACCOUNT_H_
#define ACCOUNT_H_
//#include "commonHelpers.h"



struct Demographic {
	int birthYear;
	double income;
	char country[31];
};
//struct Demographic DemographicInstance;

struct UserLogin {

	char displayName[31];
	char name[11];
	char password[9];
};
//struct UserLogin UserLoginInstance;

struct Account {
	int accountNumber;
	char accountType;
	struct UserLogin UserLoginVariable;
	struct Demographic DemographicVariable;
};
//struct Account AccountArray[50];

void getAccount(struct Account* ptrAccount);
void getUserLogin(struct UserLogin* ptrUserLogin);
void getDemographic(struct Demographic* ptrDemographic);
void updateAccount(struct Account* AccountPointer);
void updateUserLogin(struct UserLogin* UserLoginPointer);
void updateDemographic(struct Demographic* DemographicPointer);


//int loadAccounts(struct Account accounts[], const int ACCOUNT_SIZE);



#endif   // !ACCOUNT_H_



