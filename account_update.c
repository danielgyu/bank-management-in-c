#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bank.h"

#define PW_LENGTH (4)
#define ONE_LINE (19)
#define TEMP_BUFFER (1000)
#define UNTIL_PASSWORD (14)

void get_and_change_pw(FILE *fptr, size_t line_num, char *line_data) {
	FILE *temp_fptr;
	char new_password[PW_LENGTH + 1];
	char buffer[TEMP_BUFFER];
	char modified_line[ONE_LINE];
	size_t count, i, n;

	printf("Enter new password(4 digit PIN): ");
	scanf("%s", new_password);
	if (new_password[PW_LENGTH]) {
		printf("Not four digits\n");
		exit(1);
	}

	for (i = 0; i < UNTIL_PASSWORD; i++) {
		modified_line[i] = line_data[i];
	}
	
	n = 0;
	for (i = UNTIL_PASSWORD; i < ONE_LINE; i++) {
		modified_line[i] = new_password[n];
		n++;
	}
	printf("modified_line: %s", modified_line);

	temp_fptr = fopen("temp_db", "w");
	count = 0;
	fseek(fptr, 0, SEEK_SET);
	while ((fgets(buffer, TEMP_BUFFER, fptr)) != NULL) {
		count++;

		if (count == line_num) {
			fputs(modified_line, temp_fptr);
			fprintf(temp_fptr, "\n");
		} else {
			fputs(buffer, temp_fptr);
		}
	}

	fclose(fptr);
	fclose(temp_fptr);

	remove("account_db");
	rename("temp_db", "account_db");
}

int update_account()
{
	FILE *fptr;
	char line_data[ONE_LINE];
	size_t acc_number;
	size_t line_num = 0;
	bool is_account = {false};

	printf("please enter your account number: ");
	scanf("%lu", &acc_number);

	fptr = fopen("account_db", "r+");
	if (fptr == NULL) {
		exit(1);
	}

	check_acc_exist(fptr, acc_number, &is_account, &line_num, line_data);
	printf("Line data: %s\n", line_data);

	if (is_account == true) {
		get_and_change_pw(fptr, line_num, line_data);
	} else {
		printf("Account doesn't exist\n");
		exit(1);
	}
	
	return 1;
}
