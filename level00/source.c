#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int nb;

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &nb);
	if (nb != 5276) {
		puts("\nInvalid Password!");
	}
	else {
		puts("\nAuthenticated!");
		system("/bin/sh");
	}
	return (nb != 5276);
}
