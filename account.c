#include <stdio.h>

#include "bank.h"

#define NAME_LENGTH (10)
#define ACCOUNT_LENGTH (8)

int create_new_account()
{
	char name[NAME_LENGTH];	
	char account_num[ACCOUNT_LENGTH];

	printf("### CREATE ACCOUNT ###\n");

	printf("Enter your name: ");
	fgets(name, NAME_LENGTH, stdin);
	printf("Enter your account number: ");
	fgets(account_num, ACCOUNT_LENGTH, stdin);
	printf("Enter your account password: ");

	printf("\n");
	printf("Hello, %s\n", name);
	printf("Account, %s\n", account_num);

	return 1;	
}
