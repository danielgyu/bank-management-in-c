#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define PW_LENGTH (4)
#define ONE_LINE (19)
#define TEMP_BUFFER (1000)

void get_and_change_pw(FILE *fptr, size_t current_line, char *line_data) {
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

	for (i = 0; i < 14; i++) {
		modified_line[i] = line_data[i];
	}
	
	n = 0;
	for (i = 14; i < ONE_LINE; i++) {
		modified_line[i] = new_password[n];
		n++;
	}
	printf("modified_line: %s", modified_line);

	temp_fptr = fopen("temp_db", "w");
	count = 0;
	fseek(fptr, 0, SEEK_SET);
	while ((fgets(buffer, TEMP_BUFFER, fptr)) != NULL) {
		count++;

		if (count == current_line) {
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

void check_acc_exist(FILE *fptr, size_t acc_number, bool *is_account, size_t line_num, char *line_data)
{
	char char_acc_num[9], buffer[9];
	char *line = NULL;
	size_t len = 0;
	ssize_t read_offset;

	sprintf(char_acc_num, "%lu", acc_number);
	while ((read_offset = getline(&line, &len, fptr)) != -1) {
		line_num++;

		strncpy(buffer, line, 8);
		if (strcmp(buffer, char_acc_num) == 0) {
			strncpy(line_data, line, 18);
			line_data[ONE_LINE - 1] = '\0';
			*is_account = true;
			break;
		}
	}
}

int update_account()
{
	FILE *fptr;
	char line_data[ONE_LINE];
	size_t acc_number;
	size_t line_num = 0;
	bool is_account = {false};
	size_t current_line;

	printf("please enter your account number: ");
	scanf("%lu", &acc_number);

	fptr = fopen("account_db", "r+");
	if (fptr == NULL) {
		exit(1);
	}

	check_acc_exist(fptr, acc_number, &is_account, line_num, line_data);
	printf("Line data: %s\n", line_data);

	if (is_account == true) {
		printf("Account exists in db\n");
		current_line = ftell(fptr) / 19;

		printf("Line number: %lu\n", current_line);
		get_and_change_pw(fptr, current_line, line_data);
	} else {
		printf("account doesn't exist\n");
		exit(1);
	}
	
	return 1;
}
