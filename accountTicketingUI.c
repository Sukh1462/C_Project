#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"
#include "ticket.h"





void displayAccountSummaryHeader(void) {
	printf("\nAcct# Acct.Type Birth\n");
	printf("----- --------- -----\n");

}

void displayAccountDetailHeader(void) {
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");

}

void displayAccountSummaryRecord(const struct Account* ptrAccount) {
	printf("%05d %-9s %5d\n", ptrAccount->accountNumber, ptrAccount->accountType == 'C' ? "CUSTOMER" : "AGENT", ptrAccount->DemographicVariable.birthYear);
}

void displayAccountDetailRecord(const struct Account* ptrAccount) {



	int j;


	char password[9];
	for (j = 0; j < 9; j++) {
		if (j % 2 == 1) {
			password[j] = '*';

		}
		else if (j % 2 == 0) {
			password[j] = ptrAccount->UserLoginVariable.password[j];

		}

	}



	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", ptrAccount->accountNumber, ptrAccount->accountType == 'C' ? "CUSTOMER" : "AGENT", ptrAccount->DemographicVariable.birthYear, ptrAccount->DemographicVariable.income, ptrAccount->DemographicVariable.country, ptrAccount->UserLoginVariable.displayName, ptrAccount->UserLoginVariable.name, password);


}

void applicationStartup(struct AccountTicketingData* data) {
	int indexNumber;
	do {
		indexNumber = menuLogin(data->accounts, data->ACCOUNT_MAX_SIZE);
		if (indexNumber != -1) {
			if (data->accounts[indexNumber].accountType == 'A') {
				menuAgent(data, &data->accounts[indexNumber]);
			}
			else {
				//printf("\nCUSTOMER: home menu currently unavailable...\n");
				//pauseExecution();
				menuCustomer(data, &data->accounts[indexNumber]);
			}
		}

	} while (indexNumber != -1);
	printf("\n==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");
}

int menuLogin(const struct Account arrayAccount[], int arraySize) {
	int flag1 = 1, flag2 = 0;
	int selection, accountNum, loggedindex = -1, flag = 1;
	char exitOption;
	do {
		flag = 1, flag1 = 1;

		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 1);
	

		if (selection == 1) {
			flag2 = 0;
			char userLogin[11], password[100];
			int attemptsLeft = 3;
			//int flag2 = 0;
			printf("\n");
			loggedindex = 0;
			do {
				printf("Enter the account#: ");
				accountNum = getInteger();
				printf("User Login    : ");
				getCString(userLogin, 0, 100);
				//scanf_s("%[^\n]c", userLogin);
				//printf("username is %s\n", userLogin);
				printf("Password      : ");
				getCString(password, 0, 100);
				//scanf_s("%[^\n]c", password);
				//printf("passowrd is %s", password);


				int j, anotherFlag = 0;
				//finding logged index
				for (j = 0; j < arraySize; ) {

					//printf("\naccount is %d\n", arrayAccount[j].accountNumber);
					//printf("you had selected %d \n", accountNum);


					if (accountNum == arrayAccount[j].accountNumber) {
						loggedindex = j;
						flag = 0;
						flag1 = 0;
					}

					j++;


				}
				int passwordFlag = 0, nameFlag = 0;
				if (strcmp(password, arrayAccount[loggedindex].UserLoginVariable.password) == 0) {
					passwordFlag = 1;
				}
				if (strcmp(userLogin, arrayAccount[loggedindex].UserLoginVariable.name) == 0) {
					nameFlag = 1;
				}
				if ((flag == 0) && (passwordFlag == 1) && (nameFlag == 1)) {
					//correct
					flag2 = 1;
				}
				else {
					attemptsLeft = attemptsLeft - 1;
					printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", attemptsLeft);
					//flag2 = 1;
					anotherFlag = 1;
				}
				if ((attemptsLeft == 0) && (anotherFlag == 1)) {
					printf("ERROR:  Login failed!\n");
					clearStandardInputBuffer();
					pauseExecution();
					//printf("\n");
					flag2 = 1;
					flag1 = 1;
				}
				
			} while (flag2 == 0);
		}
		else if (selection == 0) {
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			exitOption = getCharOption("yYnN");
			if ((exitOption == 'Y') || (exitOption == 'y')) {
				loggedindex = -1;
				flag1 = 0;
			}
			else {
				flag = 1;
				printf("\n");
			}


		}
		//printf("fag1 is %d", flag1);
	} while (flag1 == 1);

	return loggedindex;
}

void menuAgent(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount) {
	int done = 0;
	int highest;
	int selection, accountToUpdate, s, accountToDelete;
	char deletionconfirmation;
	printf("\n");
	do {
		printf("AGENT: %s (%d)\n", ptrLoggedAccount->UserLoginVariable.displayName, ptrLoggedAccount->accountNumber);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");

		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 12);
		if (selection == 1) {
			int i = 0, emptyFlag = 0;
			do {
				if ((data->accounts[i].accountNumber == 0) && (i < data->ACCOUNT_MAX_SIZE)) {
					//printf("Testing: n is %d", i);
					//emptyIndex = i;
					emptyFlag = 1;
					printf("\n");
					//finding highest account number
					highest = data->accounts[0].accountNumber;
					int j = 0;
					for (j = 0; j < data->ACCOUNT_MAX_SIZE; j++) {

						if (data->accounts[j].accountNumber > highest) {
							highest = data->accounts[j].accountNumber;
						}
					}
					data->accounts[i].accountNumber = highest + 1;
					getAccount(&data->accounts[i]);
					getUserLogin(&data->accounts[i].UserLoginVariable);
					getDemographic(&data->accounts[i].DemographicVariable);
					printf("\n*** New account added! ***\n");
					clearStandardInputBuffer();
					pauseExecution();
					//printf("\n");

				}

				/*else if ((data->accounts[i].accountNumber > 0) && (i > data->ACCOUNT_MAX_SIZE))*/
				else if (i >= data->ACCOUNT_MAX_SIZE) {
					emptyFlag = 1;
					printf("\nERROR: Account listing is FULL, call ITS Support!\n");
					pauseExecution();
				}
				i = i + 1;
				//pauseExecution();
			} while (emptyFlag == 0);
		}

		else if (selection == 2) {
			int  updateFlag = 0;
			printf("\nEnter the account#: ");
			accountToUpdate = getPositiveInteger();
			for (s = 0; s < data->ACCOUNT_MAX_SIZE; s++) {
				if (accountToUpdate == data->accounts[s].accountNumber) {
					updateAccount(&data->accounts[s]);
					//printf("procedure to update account\n");
					updateFlag = 1;
				}
				if (updateFlag == 1) {
					break;
				}

			}
			if (updateFlag == 0) {
				printf("ERROR: The account you want to update couldn't be found\n");
			}
		}

		else if (selection == 3) {

			printf("\nEnter the account#: ");
			accountToDelete = getPositiveInteger();
			for (s = 0; s < data->ACCOUNT_MAX_SIZE; s++) {
				if (accountToDelete == data->accounts[s].accountNumber) {
					if (accountToDelete == ptrLoggedAccount->accountNumber) {
						printf("\nERROR: You can't remove your own account!\n");
						pauseExecution();
					}
					else if (accountToDelete != ptrLoggedAccount->accountNumber) {
						//int indexToDelete = s;
						displayAccountDetailHeader();
						displayAccountDetailRecord(&data->accounts[s]);
						printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
						deletionconfirmation = getCharOption("YN");
						if (deletionconfirmation == 'Y') {

							int i;
							for (i = 0; i < data->TICKET_MAX_SIZE; i++) {
								if (data->tickets[i].custAccountNumber == accountToDelete) {


									if (data->tickets[i].ticketStatus == 0) {

										archiveRemovedAccountTickets(data->tickets[i], data->TICKET_MAX_SIZE);
									}
									data->tickets[i].ticketNumber = 0;
									data->tickets[i].custAccountNumber = 0;
								}
								/*data->tickets[s].custAccountNumber = 0;

								if (data->tickets[s].ticketStatus == 1) {
									data->tickets[s].ticketNumber = 0;*/

							}
							archiveRemovedAccountRecord(data->accounts[s], data->ACCOUNT_MAX_SIZE);
							data->accounts[s].accountNumber = 0;

							printf("\n*** Account Removed! ***\n");
							pauseExecution();
						}
						else if (deletionconfirmation == 'N') {
							printf("\n*** No changes made! ***\n");
							pauseExecution();
						}
						//pauseExecution();


					}
				}
			}
		}

		else if (selection == 4) {

			displayAllAccountSummaryRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}
		else if (selection == 5) {
			displayAllAccountDetailRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}

		else if (selection == 6) {

			//pauseExecution();
			printf("\n");
			displayNewTickets(data);
		}

		else if (selection == 7) {

			//pauseExecution();
			printf("\n");
			displayActiveTickets(data);
		}

		else if (selection == 8) {
			printf("\n");
			displayClosedTickets(data);

		}

		else if (selection == 9) {
			int done1 = 0, index = 0;
			printf("\n");
			do {
				int ticketNum, found = 0;
				printf("Enter ticket number: ");
				ticketNum = getPositiveInteger();
				int i;


				for (i = 0; i < data->TICKET_MAX_SIZE; i++) {
					if (ticketNum == data->tickets[i].ticketNumber) {
						index = i;

						done1 = 1;
						found = 1;
						break;

					}
				}

				if (found == 1) {
					agentManageTicket(&data->tickets[index], ptrLoggedAccount);
					printf("\n");
					//printf("\ntesting\n%s", data->tickets[index].subject);
				}
				else if (found == 0) {
					printf("\nERROR: Invalid ticket number\n");
					pauseExecution();
					done1 = 0;
				}

			} while (done1 == 0);

			//modifyTicket(data->tickets);
			//printf("\nFeature #%d currently unavailable!\n", selection);
			//pauseExecution();
			//printf("\n");
		}

		else if (selection == 10) {
			char YN;
			int counter = 0;

			printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			YN = getCharOption("YN");

			if (YN == 'Y') {

				const char filename[] = "tickets_arc.txt";

				FILE* fp = fopen(filename, "a");
				int m;

				int i;
				if (fp != NULL) {
					for (i = 0; i < data->TICKET_MAX_SIZE; i++) {

						if ((data->tickets[i].ticketStatus == 0) && (data->tickets[i].custAccountNumber > 0)) {
							fprintf(fp, "%d|%d|%d|%s|%d|", data->tickets[i].ticketNumber, data->tickets[i].custAccountNumber, data->tickets[i].ticketStatus, data->tickets[i].subject, data->tickets[i].numMessages);
							for (m = 0; m < data->tickets[i].numMessages; m++) {

								fprintf(fp, "~%c|%s|%s|", data->tickets[i].MessageArray[m].authorAccountType, data->tickets[i].MessageArray[m].displayName, data->tickets[i].MessageArray[m].messageDetails);

							}
							fprintf(fp, "\n");

							data->tickets[i].ticketNumber = 0;
							data->tickets[i].custAccountNumber = 0;
							counter++;

						}
					}


					fclose(fp);
					fp = NULL;

				}
				else {
					printf("ERROR: file couldn't be found for appending.");
				}

			}
			printf("\n*** %d tickets archived ***\n", counter);
			pauseExecution();
		}

		else if (selection == 11) {

			const char filename[] = "accounts_arc.txt";
			//int nrecs;

			numArchivedAccountRecords(filename);

			pauseExecution();


		}

		else if (selection == 12) {

			const char filename[] = "tickets_arc.txt";
			numArchivedTicketRecords(filename);
			pauseExecution();
		}

		else if (selection == 0) {
			int nsavedAccounts, nsavedTickets;
			nsavedAccounts = saveAccounts(data->accounts, data->ACCOUNT_MAX_SIZE);
			nsavedTickets = saveTickets(data->tickets, data->TICKET_MAX_SIZE);
			printf("\nSaving session modifications...\n");
			printf("   %d account saved.\n", nsavedAccounts);
			printf("   %d tickets saved.\n", nsavedTickets);
				
			printf("### LOGGED OUT ###\n\n");
			done = 1;
		}



	} while (done == 0);
}


int findAccountIndexByAcctNum(int accountNum, const struct Account arrayAccountArray[], int arraySize, int accountNumCheck) {
	int matchedIndex = -1;
	int i, accountNumber;
	if (accountNumCheck == 0) {
		for (i = 0; i < arraySize; i++) {
			if (arrayAccountArray[i].accountNumber == accountNum) {
				matchedIndex = i;
				//found = 1;
				//break;
			}
		}

	}
	else if (accountNumCheck == 1) {
		printf("Enter the account#:");
		accountNumber = getPositiveInteger();
		for (i = 0; i < arraySize; i++) {
			if (arrayAccountArray[i].accountNumber == accountNumber) {
				matchedIndex = i;
				//found1 = 1;
				//break;
			}
		}

	}
	return matchedIndex;
}

void displayAllAccountSummaryRecords(const struct Account arrayAccount[], int arraySize) {
	int i;
	displayAccountSummaryHeader();
	for (i = 0; i <= arraySize; i++) {
		if (arrayAccount[i].accountNumber > 0) {
			displayAccountSummaryRecord(&arrayAccount[i]);
		}
	}


}

void displayAllAccountDetailRecords(const struct Account arrayAccount[], int arraySize) {
	int i;
	printf("\n");
	displayAccountDetailHeader();
	for (i = 0; i < arraySize; i++) {
		if (arrayAccount[i].accountNumber > 0) {
			displayAccountDetailRecord(&arrayAccount[i]);
		}
	}


}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
	printf("\n<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

void menuCustomer(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount) {
	int logoutFlag = 0, selection;
	printf("\n");
	do {
		printf("CUSTOMER: %s (%d)\n", ptrLoggedAccount->UserLoginVariable.displayName, ptrLoggedAccount->accountNumber);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 4);

		if (selection == 1) {
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(ptrLoggedAccount);
			pauseExecution();
		}

		else if (selection == 2) {
			createTicket(data, ptrLoggedAccount);
			//printf("\nFeature #%d currently unavailable!\n", selection);
			pauseExecution();
			//printf("\n");
		}

		else if (selection == 3) {
			int done = 0, index = 0;
			printf("\n");
			do {
				int ticketNum, found = 0, flag = 0;
				printf("Enter ticket number: ");
				ticketNum = getPositiveInteger();
				int i;
				for (i = 0; i < data->TICKET_MAX_SIZE; i++) {
					if ((ticketNum == data->tickets[i].ticketNumber) && (data->tickets[i].custAccountNumber == ptrLoggedAccount->accountNumber) && (data->tickets[i].ticketStatus == 1)) {
						index = i;

						flag = 1;
						done = 1;
						found = 1;
						break;

					}
					else if ((ticketNum == data->tickets[i].ticketNumber) && (data->tickets[i].custAccountNumber == ptrLoggedAccount->accountNumber) && (data->tickets[i].ticketStatus == 0)) {
						printf("\nERROR: Ticket is closed - changes are not permitted.\n");
						flag = 1;
						//found = 1;
						done = 1;
						//pauseExecution();
					}
				}

				if (found == 1) {
					modifyTicket(&data->tickets[index], ptrLoggedAccount);
					//printf("\ntesting\n%s", data->tickets[index].subject);
				}
				else if (flag == 0) {
					printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n");
					//pauseExecution();
					done = 1;
				}

			} while (done == 0);

			//modifyTicket(data->tickets);
			//printf("\nFeature #%d currently unavailable!\n", selection);
			pauseExecution();
			//printf("\n");
		}

		else if (selection == 4) {
			//printf("\nFeature #%d currently unavailable!\n", selection);
			//pauseExecution();
			printf("\n");
			listTickets(data, ptrLoggedAccount);
		}
		else if (selection == 0) {
			int savedTickets;

			savedTickets = saveTickets(data->tickets, data->TICKET_MAX_SIZE);
			printf("\nSaving session modifications...\n");
			printf("   %d tickets saved.\n", savedTickets);


			printf("### LOGGED OUT ###\n\n");
			logoutFlag = 1;
		}


	} while (logoutFlag == 0);
}

void listTickets(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount) {
	int loopStop = 0;
	int loggedIndex = -1;
	do {
		printf("------ ------ ------------------------------ --------\n");
		printf("Ticket Status Subject                        Messages\n");
		printf("------ ------ ------------------------------ --------\n");

		int j;
		int i;



		for (i = 0; i < data->TICKET_MAX_SIZE; i++) {
			if ((data->tickets[i].custAccountNumber == ptrLoggedAccount->accountNumber) && (data->tickets[i].ticketNumber > 0) && (data->tickets[i].custAccountNumber > 0)) {
				loggedIndex = i;
				printf("%06d %-6s %-30s    %2d\n", data->tickets[loggedIndex].ticketNumber, data->tickets[loggedIndex].ticketStatus == 1 ? "ACTIVE" : "CLOSED", data->tickets[loggedIndex].subject, data->tickets[loggedIndex].numMessages);
			}
		}
		printf("------ ------ ------------------------------ --------\n\n");
		int enteredTicketNumber;
		int ticketFound = 0;
		int foundTicketNumberIndex = -1;
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		enteredTicketNumber = getPositiveOrZeroInt();
		if (enteredTicketNumber > 0) {
			for (j = 0; j < data->TICKET_MAX_SIZE; j++) {
				if ((enteredTicketNumber == data->tickets[j].ticketNumber) && (ptrLoggedAccount->accountNumber == data->tickets[j].custAccountNumber)) {
					foundTicketNumberIndex = j;
					ticketFound = 1;
					//loopStop = 1;
					break;
				}
			}
			if (ticketFound == 1) {
				viewMessages(data, foundTicketNumberIndex);
			}
			else if (ticketFound == 0) {
				printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n");
				pauseExecution();
				loopStop = 0;
			}
		}
		else if (enteredTicketNumber == 0) {
			loopStop = 1;
			printf("\n");
		}
	} while (loopStop == 0);



}

void viewMessages(struct AccountTicketingData* data, int foundTicketNumberIndex) {
	printf("\n================================================================================\n");
	printf("%06d (%s) Re: %s\n", data->tickets[foundTicketNumberIndex].ticketNumber, data->tickets[foundTicketNumberIndex].ticketStatus == 1 ? "ACTIVE" : "CLOSED", data->tickets[foundTicketNumberIndex].subject);
	printf("================================================================================\n");
	int s;
	//ptrAccount->accountType == 'C' ? "CUSTOMER" : "AGENT"
	for (s = 0; s < data->tickets[foundTicketNumberIndex].numMessages; s++) {
		printf("%s (%s):\n", data->tickets[foundTicketNumberIndex].MessageArray[s].authorAccountType == 'C' ? "CUSTOMER" : "AGENT", data->tickets[foundTicketNumberIndex].MessageArray[s].displayName);
		printf("   %s\n", data->tickets[foundTicketNumberIndex].MessageArray[s].messageDetails);

		if (((s + 1) % 5 == 0) || (s == data->tickets[foundTicketNumberIndex].numMessages - 1)) {
			pauseExecution();
		}
		else if (s < data->tickets[foundTicketNumberIndex].numMessages - 1) {
			printf("\n");
		}
	}
	//pauseExecution();
}


void displayNewTickets(struct AccountTicketingData* data) {
	int loopStop = 0;
	//int loggedIndex = -1;
	do {
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
		printf("------ ----- --------------- ------ ------------------------------ --------\n");

		int j;
		int i;



		for (i = 0; i < data->TICKET_MAX_SIZE; i++) {
			if ((data->tickets[i].ticketStatus == 1) && (data->tickets[i].numMessages == 1) && (data->tickets[i].ticketNumber > 0)) {
				//loggedIndex = i;
				printf("%06d %d %-15s %-6s %-30s    %2d\n", data->tickets[i].ticketNumber, data->tickets[i].custAccountNumber, data->tickets[i].MessageArray->displayName, data->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", data->tickets[i].subject, data->tickets[i].numMessages);
			}
		}
		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
		int enteredTicketNumber;
		int ticketFound = 0;
		int foundTicketNumberIndex = -1;
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		enteredTicketNumber = getPositiveOrZeroInt();
		if (enteredTicketNumber > 0) {
			for (j = 0; j < data->TICKET_MAX_SIZE; j++) {
				if ((enteredTicketNumber == data->tickets[j].ticketNumber) && (data->tickets[j].ticketStatus == 1) && (data->tickets[j].numMessages == 1)) {
					foundTicketNumberIndex = j;
					ticketFound = 1;
					//loopStop = 1;
					break;
				}
			}
			if (ticketFound == 1) {
				viewMessages(data, foundTicketNumberIndex);
			}
			else if (ticketFound == 0) {
				printf("\nERROR: Invalid ticket number.\n");
				pauseExecution();
				loopStop = 0;
			}
		}
		else if (enteredTicketNumber == 0) {
			loopStop = 1;
			printf("\n");
		}
	} while (loopStop == 0);


}

void displayActiveTickets(struct AccountTicketingData* data) {
	int loopStop = 0;
	//int loggedIndex = -1;
	do {
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
		printf("------ ----- --------------- ------ ------------------------------ --------\n");

		int j;
		int i;



		for (i = 0; i < data->TICKET_MAX_SIZE; i++) {

			if ((data->tickets[i].ticketStatus == 1) && (data->tickets[i].ticketNumber > 0) && (data->tickets[i].custAccountNumber > 0)) {
				//loggedIndex = i;
				printf("%06d %d %-15s %-6s %-30s    %2d\n", data->tickets[i].ticketNumber, data->tickets[i].custAccountNumber, data->tickets[i].MessageArray->displayName, data->tickets[i].ticketStatus == 0 ? "CLOSED" : "ACTIVE", data->tickets[i].subject, data->tickets[i].numMessages);
			}
		}
		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
		int enteredTicketNumber;
		int ticketFound = 0;
		int foundTicketNumberIndex = -1;
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		enteredTicketNumber = getPositiveOrZeroInt();
		if (enteredTicketNumber > 0) {
			for (j = 0; j < data->TICKET_MAX_SIZE; j++) {
				if ((enteredTicketNumber == data->tickets[j].ticketNumber) && (data->tickets[j].ticketStatus == 1)) {
					foundTicketNumberIndex = j;
					ticketFound = 1;
					//loopStop = 1;
					break;
				}
			}
			if (ticketFound == 1) {
				viewMessages(data, foundTicketNumberIndex);
			}
			else if (ticketFound == 0) {
				printf("\nERROR: Invalid ticket number.\n");
				pauseExecution();
				loopStop = 0;
			}
		}
		else if (enteredTicketNumber == 0) {
			loopStop = 1;
			printf("\n");
		}
	} while (loopStop == 0);


}

void displayClosedTickets(struct AccountTicketingData* data) {
	int loopStop = 0;
	//int loggedIndex = -1;
	do {
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
		printf("------ ----- --------------- ------ ------------------------------ --------\n");

		int j;
		int i;



		for (i = 0; i < data->TICKET_MAX_SIZE; i++) {
			if ((data->tickets[i].ticketStatus == 0) && (data->tickets[i].custAccountNumber > 0)) {
				//loggedIndex = i;
				printf("%06d %d %-15s %-6s %-30s    %2d\n", data->tickets[i].ticketNumber, data->tickets[i].custAccountNumber, data->tickets[i].MessageArray->displayName, data->tickets[i].ticketStatus == 1 ? "ACTIVE" : "CLOSED", data->tickets[i].subject, data->tickets[i].numMessages);
			}
		}
		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
		int enteredTicketNumber;
		int ticketFound = 0;
		int foundTicketNumberIndex = -1;
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		enteredTicketNumber = getPositiveOrZeroInt();
		if (enteredTicketNumber > 0) {
			for (j = 0; j < data->TICKET_MAX_SIZE; j++) {
				if ((enteredTicketNumber == data->tickets[j].ticketNumber) && (data->tickets[j].ticketStatus == 0)) {
					foundTicketNumberIndex = j;
					ticketFound = 1;
					//loopStop = 1;
					break;
				}
			}
			if (ticketFound == 1) {
				viewMessages(data, foundTicketNumberIndex);
			}
			else if (ticketFound == 0) {
				printf("\nERROR: Invalid ticket number.\n");
				pauseExecution();
				loopStop = 0;
			}
		}
		else if (enteredTicketNumber == 0) {
			loopStop = 1;
			printf("\n");
		}
	} while (loopStop == 0);


}


void createTicket(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount) {
	//listTickets(data, ptrLoggedAccount);
	int emptyFlag = 0, i = 0, highest;
	//for (i=0; emptyFlag==0;i++){
	do {
		//if (data->tickets[i].ticketNumber == 0) {
		if ((data->tickets[i].ticketNumber == 0) && (i < data->TICKET_MAX_SIZE)) {
			emptyFlag = 1;
			printf("\n");
			highest = data->tickets[0].ticketNumber;
			int j = 0;
			for (j = 0; j < data->TICKET_MAX_SIZE; j++) {
				if (data->tickets[j].ticketNumber > highest) {
					highest = data->tickets[j].ticketNumber;
				}
			}
			data->tickets[i].ticketNumber = highest + 1;
			data->tickets[i].ticketStatus = 1;
			data->tickets[i].custAccountNumber = ptrLoggedAccount->accountNumber;
			printf("New Ticket (Ticket#:%06d)\n", data->tickets[i].ticketNumber);
			printf("----------------------------------------\n");
			printf("Enter the ticket SUBJECT (30 chars. maximum): ");
			getCString(data->tickets[i].subject, 1, 30);
			printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
			getCString(data->tickets[i].MessageArray[0].messageDetails, 1, 150);
			data->tickets[i].MessageArray[0].authorAccountType = 'C';
			strcpy(data->tickets[i].MessageArray[0].displayName, ptrLoggedAccount->UserLoginVariable.displayName);
			data->tickets[i].numMessages = 1;
			printf("\n*** New ticket created! ***\n");
			//printf("checking %s  \n %s \n %c", data->tickets[i].subject, data->tickets[i].MessageArray[0].messageDetails, data->tickets[i].MessageArray[0].authorAccountType);
			clearStandardInputBuffer();
			//pauseExecution();

			//data->tickets[i].MessageArray[0].displayName = ptrLoggedAccount->UserLoginVariable.displayName;

		}
		else if (i >= data->TICKET_MAX_SIZE) {
			emptyFlag = 1;
			printf("\nERROR: Ticket listing is FULL, call ITS Support!\n");
		}
		i = i + 1;

	} while (emptyFlag == 0);
}

int loadAccounts(struct Account accounts[], int arrSize) {
	int i = 0;

	const char filename[] = "accounts.txt";

	FILE* fp = fopen(filename, "r");

	//if (fp != NULL) {
	if (fp != NULL) {

		while (i < arrSize && fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%[^\n]", &accounts[i].accountNumber, &accounts[i].accountType, accounts[i].UserLoginVariable.displayName, accounts[i].UserLoginVariable.name, accounts[i].UserLoginVariable.password, &accounts[i].DemographicVariable.birthYear, &accounts[i].DemographicVariable.income, accounts[i].DemographicVariable.country) == 8) {

			i++;

		}

		fclose(fp);
		fp = NULL;
	}
	else {
		printf("ERROR: Unable to open file for reading.\n");
	}

	//int s;
	//for (s = 0; s < i; s++) {
	//	printf("\n %d | %c | %s | %s | %s | %d | %.2lf | %s |\n", accounts[s].accountNumber, accounts[s].accountType, accounts[s].UserLoginVariable.displayName, accounts[s].UserLoginVariable.name, accounts[s].UserLoginVariable.password, accounts[s].DemographicVariable.birthYear, accounts[s].DemographicVariable.income, accounts[s].DemographicVariable.country);
	//}
	return i;
}


int loadTickets(struct Ticket tickets[], int arrSize) {

	int i = 0;

	const char filename[] = "tickets.txt";

	FILE* fp = fopen(filename, "r");

	int j;
	char ch;


	if (fp != NULL) {


		while (i < arrSize && fscanf(fp, "%d|%d|%d|%[^|]|%d|", &tickets[i].ticketNumber, &tickets[i].custAccountNumber, &tickets[i].ticketStatus, tickets[i].subject, &tickets[i].numMessages) == 5) {

			j = 0;




			while (j < tickets[i].numMessages && fscanf(fp, "%c|%30[^|]|%[^|]%c", &tickets[i].MessageArray[j].authorAccountType, tickets[i].MessageArray[j].displayName, tickets[i].MessageArray[j].messageDetails, &ch) == 4) {

				if (j + 1 == tickets[i].numMessages) {

					//if (ch != '\n') {

					//	while (fgetc(fp) != '\n');
					//}

				}
				else {
					if (ch != '|') {

						while (fgetc(fp) != '|');
					}

				}
				j++;
			}

			i++;

		}

		fclose(fp);
		fp = NULL;
	}
	else {
		printf("ERROR: Unable to open file for reading.\n");
	}

	//int s;
	//int m;
	/*for (s = 0; s < i; s++) {
		printf("\n %d | %d | %d | %s | %d |\n", tickets[s].ticketNumber, tickets[s].custAccountNumber, tickets[s].ticketStatus, tickets[s].subject, tickets[s].numMessages);
		for (m = 0; m < tickets[s].numMessages; m++) {

			printf(" %c | %s | %s |\n", tickets[s].MessageArray[m].authorAccountType, tickets[s].MessageArray[m].displayName, tickets[s].MessageArray[m].messageDetails);

		}
	}*/
	return i;



}


int saveTickets(struct Ticket tickets[], int arrSize) {

	int i = 0, count = 0, m;
	const char filename[] = "tickets.txt";
	FILE* fp = fopen(filename, "w");

	if (fp != NULL) {

		for (i = 0; i < arrSize; i++) {

			if ((tickets[i].ticketNumber > 0) && (tickets[i].custAccountNumber > 0)) {


				fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].ticketNumber, tickets[i].custAccountNumber, tickets[i].ticketStatus, tickets[i].subject, tickets[i].numMessages);
				for (m = 0; m < tickets[i].numMessages; m++) {

					fprintf(fp, "%c|%s|%s|", tickets[i].MessageArray[m].authorAccountType, tickets[i].MessageArray[m].displayName, tickets[i].MessageArray[m].messageDetails);

				}


				count++;
			}
		}

		fclose(fp);
		fp = NULL;



	}
	else {
		printf("ERROR: can't open file for writing!");
	}

	//int s;
	////int m;
	//for (s = 0; s < i; s++) {
	//	printf("\n %d | %d | %d | %s | %d |\n", tickets[s].ticketNumber, tickets[s].custAccountNumber, tickets[s].ticketStatus, tickets[s].subject, tickets[s].numMessages);
	//	for (m = 0; m < tickets[s].numMessages; m++) {

	//		printf(" %c | %s | %s |\n", tickets[s].MessageArray[m].authorAccountType, tickets[s].MessageArray[m].displayName, tickets[s].MessageArray[m].messageDetails);

	//	}
	//}

	return count;
}

int saveAccounts(struct Account accounts[], int arrSize) {
	int i = 0, count = 0;
	const char filename[] = "accounts.txt";
	FILE* fp = fopen(filename, "w");

	if (fp != NULL) {

		for (i = 0; i < arrSize; i++) {

			if (accounts[i].accountNumber > 0) {

				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", accounts[i].accountNumber, accounts[i].accountType, accounts[i].UserLoginVariable.displayName, accounts[i].UserLoginVariable.name, accounts[i].UserLoginVariable.password, accounts[i].DemographicVariable.birthYear, accounts[i].DemographicVariable.income, accounts[i].DemographicVariable.country);


				count++;
			}
		}

		fclose(fp);
		fp = NULL;



	}
	else {
		printf("ERROR: can't open file for writing!");
	}



	return count;
}





void archiveRemovedAccountTickets(struct Ticket ticket, int arrSize) {

	const char filename[] = "tickets_arc.txt";
	FILE* fp = fopen(filename, "a");
	int m;

	if (fp != NULL) {
		fprintf(fp, "%d|%d|%d|%s|%d|", ticket.ticketNumber, ticket.custAccountNumber, ticket.ticketStatus, ticket.subject, ticket.numMessages);
		for (m = 0; m < ticket.numMessages; m++) {

			fprintf(fp, "~%c|%s|%s|", ticket.MessageArray[m].authorAccountType, ticket.MessageArray[m].displayName, ticket.MessageArray[m].messageDetails);

		}
		fprintf(fp, "\n");
		fclose(fp);
		fp = NULL;

	}
	else {
		printf("ERROR: can't open file for appending!");
	}
}

void archiveRemovedAccountRecord(struct Account account, int arrSize) {
	const char filename[] = "accounts_arc.txt";
	FILE* fp = fopen(filename, "a");
	//int m;

	if (fp != NULL) {

		fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", account.accountNumber, account.accountType, account.UserLoginVariable.displayName, account.UserLoginVariable.name, account.UserLoginVariable.password, account.DemographicVariable.birthYear, account.DemographicVariable.income, account.DemographicVariable.country);

		//fprintf(fp, "\n");

		fclose(fp);
		fp = NULL;
	}
	else {
		printf("ERROR: can't open file for appending!");
	}
}

void numArchivedAccountRecords(const char filename[]) {
	FILE* fp = fopen(filename, "r");
	int c, nrecs = 0;

	if (fp != NULL) {
		do {
			c = fgetc(fp);
			if (c != EOF) {
				if (c == '\n') {
					nrecs++;
				}
			}
		} while (feof(fp) == 0);

		fclose(fp);
		fp = NULL;

		printf("\nThere are %d account(s) currently archived.\n", nrecs);


	}
	else {
		printf("ERROR: couldn't open file for reading.\n");
	}


}

void numArchivedTicketRecords(const char filename[]) {
	FILE* fp = fopen(filename, "r");
	int c, nrecs = 0, nmsgs = 0;

	if (fp != NULL) {
		do {
			c = fgetc(fp);
			if (c != EOF) {
				if (c == '\n') {
					nrecs++;
				}
				else if (c == '~') {
					nmsgs++;
				}
			}
		} while (feof(fp) == 0);

		fclose(fp);
		fp = NULL;

		printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n", nrecs, nmsgs);

	}
	else {
		printf("ERROR: couldn't open file for reading.\n");
	}

	//return nrecs;
}
