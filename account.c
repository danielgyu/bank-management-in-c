#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bank.h"

#define NAME_LENGTH (10)
#define ACCOUNT_LENGTH (8)


void generate_number_for_account(size_t count, char account_number[])
{
	int rd1, rd2;

	srand(time(0));
	rd1 = 1000 + (rand() % 9000);
	rd2 = 1000 + (rand() % 9000);

	sprintf(account_number, "%d%d", rd1, rd2);	
}


char* create_account(char* account_number)
{
	generate_number_for_account(ACCOUNT_LENGTH, account_number);

	return account_number;
}


int create_new_account()
{
	char name[NAME_LENGTH];	
	char account_num[ACCOUNT_LENGTH+1];

	printf("### CREATE ACCOUNT ###\n");

	printf("Enter your name: ");
	fgets(name, NAME_LENGTH, stdin);

	create_account(account_num);
	printf("\n");
	printf("Your account number is: %s\n", account_num); 

	printf("Enter your account password: ");

	printf("\n");
	printf("Hello, %s\n", name);
	printf("Account, %s\n", account_num);

	return 1;	
}
