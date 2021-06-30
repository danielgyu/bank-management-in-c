#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define PW_LENGTH (10)

void get_and_change_pw(FILE *fptr, long current_position) {
	char new_password[PW_LENGTH];
	char line_buffer[8];

	printf("type new password: ");
	scanf("%s", new_password);
	printf("\n");

	fseek(fptr, current_position, SEEK_SET);
	fscanf(fptr, "%s", line_buffer);
	printf("ftell: %ld, position: %ld, line:%s\n", ftell(fptr), current_position, line_buffer);
	fprintf(fptr, "%s", new_password);
}

void check_acc_exist(FILE *fptr, size_t acc_number, bool *is_account, size_t line_num)
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
			*is_account = true;
			break;
		}
	}
}

int update_account()
{
	FILE *fptr;
	size_t acc_number;
	size_t line_num = 0;
	bool is_account = {false};
	long current_position;

	printf("please enter your account number: \n");
	scanf("%lu", &acc_number);

	fptr = fopen("account_db", "r+");
	if (fptr == NULL) {
		exit(1);
	}

	check_acc_exist(fptr, acc_number, &is_account, line_num);

	if (is_account == true) {
		printf("account exists\n");
		current_position = ftell(fptr) - 10;
		get_and_change_pw(fptr, current_position);
	} else {
		printf("account doesn't exist\n");
		exit(1);
	}

	fclose(fptr);
	
	return 1;
}
