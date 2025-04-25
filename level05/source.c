#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
    char buffer[100];

    fgets(buffer, 100, stdin);
    for (unsigned int i = 0; i < ft_strlen(buffer); i++) {
        if (buffer[i] > '@' && buffer[i] < '[') {
            buffer[i] ^= 0x20;
        }
    }
    printf(buffer);
    exit(0);
}
