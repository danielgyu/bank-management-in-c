#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int x, y;
	char string[9];

	x = 1234;
	y = 5678;

	sprintf(string, "%d%d", x, y);
	printf("%s", string);
}
