#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bank.h"

#define ACCOUNT_LENGTH (9)
#define NAME_LENGTH (10)
#define PW_LENGTH (4)

struct AccountInfo {
	char holder_name[NAME_LENGTH];
	char account_num[ACCOUNT_LENGTH];
	char password[PW_LENGTH];
};

void generate_number_for_account(struct AccountInfo* acc_info)
{
	int rd1, rd2;

	srand(time(0));
	rd1 = 1000 + (rand() % 9000);
	rd2 = 1000 + (rand() % 9000);

	sprintf(acc_info->account_num, "%d%d", rd1, rd2);	
}


struct AccountInfo* create_account(struct AccountInfo* acc_info)
{
	generate_number_for_account(acc_info);

	return acc_info;
}


void save_account(struct AccountInfo* acc_info)
{
	// make file for account's name, password, acc_number, balance
	FILE *fptr;
	if (fopen("account_db", "r") == NULL) {
		fptr = fopen("account_db", "w");
	} else {
		fptr = fopen("account_db", "a");
	}

	fprintf(fptr, "%s, %s, %s\n", acc_info->account_num, acc_info->holder_name, acc_info->password);

	fclose(fptr);
}


int create_new_account()
{
	struct AccountInfo* acc_info = malloc(sizeof(struct AccountInfo));
	size_t i;
	char buffer[PW_LENGTH + 1];

	printf("### CREATE ACCOUNT ###\n");

	printf("Enter your two word initial(e.g. KG): ");
	scanf("%s", acc_info->holder_name);

	printf("Enter your 4 PIN password: ");
	scanf("%s", buffer);
	
	if (buffer[4]) {
		printf("not four digits\n");
		exit(1);
	}
	for (i = 0; i <= PW_LENGTH; i++) {
		acc_info->password[i] = buffer[i];
	}

	create_account(acc_info);
	save_account(acc_info);

	printf("\n");
	printf("Hello %s, your account number is: %s\n", acc_info->holder_name, acc_info->account_num);

	free(acc_info);
	return 1;	
}
