#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define PW_LENGTH (10)

void get_password(char *password) {
	printf("type new password\n");
	scanf("%s", password);
}

void check_acc_exist(FILE *fptr, size_t acc_number, bool *is_account)
{
	char char_acc_num[9], buffer[9];
	char *line = NULL;
	size_t len = 0;
	ssize_t read_offset;

	// get read offset for future use in update_name and pw
	sprintf(char_acc_num, "%lu", acc_number);
	while ((read_offset = getline(&line, &len, fptr)) != -1) {
		strncpy(buffer, line, 8);
		if (strcmp(buffer, char_acc_num) == 0) {
			*is_account = true;
			break;
		}
	}
}

int update_account()
{
	FILE *fptr;
	size_t acc_number;
	bool is_account = {false};
	long current_position;
	char new_password[PW_LENGTH];

	printf("please enter your account number: \n");
	scanf("%lu", &acc_number);

	fptr = fopen("account_db", "r");
	if (fptr == NULL) {
		exit(1);
	}

	check_acc_exist(fptr, acc_number, &is_account);

	if (is_account == true) {
		printf("account exists\n");
		current_position = ftell(fptr);
		get_password(new_password);
	} else {
		printf("account doesn't exist\n");
		exit(1);
	}

	fclose(fptr);
	
	return 1;
}
