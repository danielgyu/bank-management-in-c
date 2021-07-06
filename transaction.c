#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bank.h"

#define ONE_LINE (19)
#define TEMP_BUFFER (100)

void remit(FILE *fptr, unsigned int sender_line, unsigned int receiver_line, unsigned int amount)
{
	FILE *temp;
	char buffer[TEMP_BUFFER];
	int left, balance, count = 0;

	temp = fopen("temp_db", "w");

	while ((fgets(buffer, TEMP_BUFFER, fptr)) != NULL) {
		count++;

		if (count == sender_line) {
			balance = atoi(buffer);
			assert (balance - amount > 0);

			left = balance - amount;
			fprintf(temp, "%d\n", balance);	
		} else if (count == receiver_line) {
			balance = atoi(buffer);

			balance = balance + amount;
			fprintf(temp, "%d\n", balance);
		} else {
			fputs(buffer, temp);
		}
	}

	printf("Remaining budget: %d\n", left);

	fclose(fptr);

	remove("balance_db");
	rename("temp_db", "balance_db");
}

int make_transaction()
{
	FILE *afptr, *bfptr;
	char sender_data[ONE_LINE], receiver_data[ONE_LINE];
	size_t sender_acc, receiver_acc, sender_line = 0, receiver_line = 0;
	unsigned int amount;
	bool is_sender, is_receiver;

	printf("Please enter your account number: ");
	scanf("%lu", &sender_acc);

	printf("Please enter recipient's account number: ");
	scanf("%lu", &receiver_acc);

	afptr = fopen("account_db", "r+");

	fseek(afptr, 0, SEEK_SET);
	check_acc_exist(afptr, sender_acc, &is_sender, &sender_line, sender_data);
	fseek(afptr, 0, SEEK_SET);
	check_acc_exist(afptr, receiver_acc, &is_receiver, &receiver_line, receiver_data);

	fclose(afptr);

	bfptr = fopen("balance_db", "r+");

	if (is_sender & is_receiver) {
		printf("Transaction amount: ");
		scanf("%d", &amount);

		remit(bfptr, sender_line, receiver_line, amount);
	} else {
		printf("Check account number\n");
		exit(1);
	}

	return 1;
}
