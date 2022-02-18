#ifndef TICKET_H_
#define TICKET_H_


struct Message {
	char authorAccountType;
	char displayName[31];
	char messageDetails[151];
};

struct Ticket {
	int ticketNumber;
	int custAccountNumber;
	int ticketStatus;
	char subject[31];
	int numMessages;
	struct Message MessageArray[20];
};

void modifyTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount);
void modifySubject(struct Ticket* tickets);
void addMessage(struct Ticket* tickets, const struct Account* ptrLoggedAccount);
void closeTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount);
void agentManageTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount);

void reopenTicket(struct Ticket* tickets, const struct Account* ptrLoggedAccount);

//int loadTickets(struct Ticket tickets[], const int TICKET_SIZE);





#endif 