#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define ONE_LINE (19)

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
			printf("found account\n");
			break;
		}
	}
}
