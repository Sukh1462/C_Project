#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H
#include "account.h"
#include "ticket.h"




struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
};





void displayAccountSummaryHeader(void);
void displayAccountDetailHeader(void);
void displayAccountSummaryRecord(const struct Account* ptrAccount);
void displayAccountDetailRecord(const struct Account* ptrAccount);

void applicationStartup(struct AccountTicketingData* data);
int menuLogin(const struct Account arrayAccount[], int arraySize);
void menuAgent(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount);
int findAccountIndexByAcctNum(int accountNum, const struct Account arrayAccountArray[], int arraySize, int accountNumCheck);
void displayAllAccountSummaryRecords(const struct Account arrayAccount[], int arraySize);
void displayAllAccountDetailRecords(const struct Account arrayAccount[], int arraySize);
// Pause execution until user enters the enter key
void pauseExecution(void);


void menuCustomer(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount);

void listTickets(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount);
void viewMessages(struct AccountTicketingData* data, int foundTicketNumberIndex);
void displayNewTickets(struct AccountTicketingData* data);
void displayActiveTickets(struct AccountTicketingData* data);

void displayClosedTickets(struct AccountTicketingData* data);
void createTicket(struct AccountTicketingData* data, const struct Account* ptrLoggedAccount);

int loadAccounts(struct Account accounts[], int arrSize);

int loadTickets(struct Ticket tickets[], int arrSize);

int saveTickets(struct Ticket tickets[], int arrSize);
int saveAccounts(struct Account accounts[], int arrSize);

void archiveRemovedAccountTickets(struct Ticket ticket, int arrSize);
void archiveRemovedAccountRecord(struct Account account, int arrSize);

void numArchivedAccountRecords(const char filename[]);
void numArchivedTicketRecords(const char filename[]);





#endif 

