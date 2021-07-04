#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bank.h"

#define ONE_LINE (19)
#define BUFFER (1024)

void get_account_balance(FILE *fptr, size_t target_line_num)
{
	int count = 1;
	char line_data[BUFFER];
	
	while ((fgets(line_data, BUFFER, fptr)) != NULL) {
		if (count == target_line_num) {
			printf("Your balance: %s\n", line_data);
			fclose(fptr);
		} else {
			count ++;
		}
	}
}

void check_balance()
{
	FILE *afptr, *bfptr;
	bool is_account = {false};
	char line_data[ONE_LINE];
	size_t account_number, current_line, line_num = 0;

	printf("Enter account number: ");
	scanf("%lu", &account_number);

	afptr = fopen("account_db", "r");

	check_acc_exist(afptr, account_number, &is_account, line_num, line_data);

	if (is_account == true) {
		printf("Account exists in db\n");
		current_line = ftell(afptr) / 19;
		fclose(afptr);

		bfptr = fopen("balance_db", "r");
		get_account_balance(bfptr, current_line);
	} else {
		printf("Account doesn't exist\n");
		exit(1);
	}
}
