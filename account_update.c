#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int check_acc_exist(size_t acc_number, bool is_account)
{
	FILE *fptr;


	return true;
}

int update_account()
{
	size_t acc_number;
	bool is_account;

	printf("please enter your account number\n");

	scanf("%lu", &acc_number);

	check_acc_exist(acc_number, is_account);
	
	return 1;
}
