#include <stdio.h>

#include "bank.h"

int main (void)
{
	size_t num;

	printf("### BANK MANAGEMENT SYSTEM ###\n");
	printf("1.Create new account\n");
	printf("2.Update account information\n");
	printf("3.Transactions\n");
	printf("4.Check account details\n");
	printf("5.Remove existing account\n");
	printf("6.Exit\n");
	printf("\n");
	printf("Select 1-6: ");

	scanf("%lu", &num);
	getchar();
	printf("\n");

	switch(num)
	{
		case 1:
			create_new_account();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			break;
	}
}
