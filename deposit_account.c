#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bank.h"

#define ONE_LINE (19)
#define TEMP_BUFFER (100)

void deposit_to_account(FILE *fptr, size_t amount, size_t line_num)
{
	FILE *temp;
	char buffer[TEMP_BUFFER];
	int count = 0;
	
	temp = fopen("temp_db", "w");

	while ((fgets(buffer, TEMP_BUFFER, fptr)) != NULL) {
		count++;

		if (count == line_num) {
			fprintf(temp, "%lu\n", amount);
		} else {
			fputs(buffer, temp);
		}
	}

	fclose(fptr);

	remove("balance_db");
	rename("temp_db", "balance_db");
}

int make_deposit()
{
	FILE *afptr, *bfptr;
	char line_data[ONE_LINE];
	size_t acc_number, amount, line_num = 0;
	bool is_account = {false};

	printf("Please enter your account number: ");
	scanf("%lu", &acc_number);

	afptr = fopen("account_db", "r+");
	if (afptr == NULL) {
		exit(1);
	}

	check_acc_exist(afptr, acc_number, &is_account, &line_num, line_data);

	bfptr = fopen("balance_db", "r+");

	if (is_account == true) {
		printf("Deposit amount: ");
		scanf("%lu", &amount);

		deposit_to_account(bfptr, amount, line_num);
	} else {
		printf("Account doesn't exist\n");
		exit(1);
	}

	fclose(afptr);

	return 1;
}
