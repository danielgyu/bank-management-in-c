#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bank.h"

void get_account_balance(FILE *fptr, size_t target_line_num)
{
	int count = 0;
	char line_data[1];
	
	while (fgets(line_data, sizeof(line_data), fptr) != NULL) {
		printf("in fgets\n");
		if (count == target_line_num) {
			fclose(fptr);
			printf("Your balance is %s\n", line_data);
		} else {
			count ++;
		}
	}
}

void check_balance()
{
	FILE *afptr, *bfptr;
	bool is_account = {false};
	size_t account_number, current_line, line_num = 0;

	printf("Enter account number: ");
	scanf("%lu", &account_number);

	afptr = fopen("account_db", "r");

	check_acc_exist(afptr, account_number, &is_account, line_num);

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
