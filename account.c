#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bank.h"

#define NAME_LENGTH (10)
#define ACCOUNT_LENGTH (9)
#define PW_LENGTH (10)

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
	FILE *fptr;
	if (fopen("account_db", "r") == NULL) {
		fptr = fopen("account_db", "w");
	} else {
		fptr = fopen("account_db", "a");
	}

	fprintf(fptr, "%s, %s, %s\n", acc_info->holder_name, acc_info->password, acc_info->account_num);

	fclose(fptr);
}


int create_new_account()
{
	struct AccountInfo* acc_info = malloc(sizeof(struct AccountInfo));

	printf("### CREATE ACCOUNT ###\n");

	printf("Enter your name: ");
	scanf("%s", acc_info->holder_name);

	printf("Enter your account password(8-10): ");
	scanf("%s", acc_info->password);

	create_account(acc_info);
	save_account(acc_info);

	printf("\n");
	printf("Hello %s, your account number is: %s\n", acc_info->holder_name, acc_info->account_num);

	free(acc_info);
	return 1;	
}
