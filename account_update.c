#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void update_name(char *name);
void update_password(char *name);

void check_acc_exist(FILE *fptr, size_t acc_number, bool *is_account)
{
	char char_acc_num[9];
	char buffer[9];
	char *line = NULL;
	size_t len = 0;
	ssize_t read_offset;

	// get read offset for future use in update_name and pw
	sprintf(char_acc_num, "%lu", acc_number);
	while ((read_offset = getline(&line, &len, fptr)) != -1) {
		strncpy(buffer, line, 8);
		if (strcmp(buffer, char_acc_num) == 0) {
			*is_account = true;
		}
	}
}

int update_account()
{
	FILE *fptr;
	size_t acc_number;
	bool is_account = {false};

	printf("please enter your account number: \n");
	scanf("%lu", &acc_number);

	fptr = fopen("account_db", "r");
	if (fptr == NULL) {
		exit(1);
	}

	check_acc_exist(fptr, acc_number, &is_account);

	if (is_account == true) {
		printf("account exists\n");
	} else {
		printf("account doesn't exist\n");
		exit(1);
	}

	fclose(fptr);
	
	return 1;
}
