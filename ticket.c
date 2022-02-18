#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"
#include "ticket.h"






void modifyTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount) {
	int done = 0;
	int selection;
	printf("\n");
	do {
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", tickets->ticketNumber);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", tickets->ticketStatus == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tickets->subject);
		printf("----------------------------------------\n");

		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		if (selection == 1) {
			modifySubject(tickets);
			//printf("\n%s\nTesting\n", tickets->subject);
			printf("\n");
			//done = 1;
		}
		else if (selection == 2) {
			//printf("\n");
			addMessage(tickets, ptrLoggedAccount);

			printf("\n");
			//done = 1;
		}
		else if (selection == 3) {
			closeTicket(tickets, ptrLoggedAccount);
			//printf("\n");
			done = 1;
		}
		else if (selection == 0) {
			done = 1;
			//pauseExecution();
		}

	} while (done == 0);

}
void modifySubject(struct Ticket* tickets) {
	char newSub[31];
	printf("\nEnter the revised ticket SUBJECT (30 chars. maximum): ");
	getCString(newSub, 1, 30);
	strcpy(tickets->subject, newSub);
}



void addMessage(struct Ticket* tickets, const struct Account* ptrLoggedAccount) {
	char newMessage[151];

	int n = tickets->numMessages;
	if ((tickets->numMessages < 20) && (tickets->ticketStatus == 1)) {

		printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(newMessage, 1, 150);
		//printf("\n");
		strcpy(tickets->MessageArray[n].messageDetails, newMessage);

		tickets->MessageArray[n].authorAccountType = ptrLoggedAccount->accountType;
		strcpy(tickets->MessageArray[n].displayName, ptrLoggedAccount->UserLoginVariable.displayName);
		tickets->numMessages = tickets->numMessages + 1;

		clearStandardInputBuffer();
	}
	else if ((tickets->numMessages < 20) && (tickets->ticketStatus == 0)) {
		printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
	}
	else {
		printf("\nERROR: Message limit has been reached, call ITS Support!\n");
	}

}

void closeTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount) {
	if (tickets->ticketStatus == 1) {
		printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
		char close;
		//int done = 0;
		close = getCharOption("YN");
		if (close == 'Y') {
			if (tickets->numMessages < 20) {
				printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
				char closingMessage;
				closingMessage = getCharOption("YN");
				if (closingMessage == 'Y') {
					//printf("\n");
					addMessage(tickets, ptrLoggedAccount);
				}

			}
			//tickets->ticketStatus = 0;
			tickets->ticketStatus = 0;
			printf("\n*** Ticket closed! ***\n");

			//done = 1;
		}

	}
	else
		printf("\nERROR: Ticket is already closed!\n");

}

void agentManageTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount) {
	int done = 0;
	printf("\n");
	do {
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", tickets->ticketNumber);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", tickets->ticketStatus == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tickets->subject);
		printf("Acct#   : %d\n", tickets->custAccountNumber);
		printf("Customer: %s\n", tickets->MessageArray[0].displayName);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		int selection;
		selection = getIntFromRange(0, 3);

		if (selection == 1) {

			addMessage(tickets, ptrLoggedAccount);
			printf("\n");
		}
		if (selection == 2) {
			closeTicket(tickets, ptrLoggedAccount);
			printf("\n");
		}
		if (selection == 3) {
			reopenTicket(tickets, ptrLoggedAccount);
		}



		if (selection == 0) {
			done = 1;
		}

	} while (done == 0);
}

void reopenTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount) {
	if (tickets->ticketStatus == 0) {
		printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
		char open;
		open = getCharOption("YN");
		if (open == 'Y') {

			tickets->ticketStatus = 1;
			printf("\n*** Ticket re-opened! ***\n\n");
			//clearStandardInputBuffer();
			//pauseExecution();

		}
		else {
			printf("\n");
		}
	}
	else
		printf("\nERROR: Ticket is already active!\n\n");
}


