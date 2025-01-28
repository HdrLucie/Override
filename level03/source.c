#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void decrypt(int key) {
    char str[] = "Q}|u`sfg~sf{}|a3";
    int len = strlen(str);

    for(int i = 0; i < len; i++) {
        str[i] ^= key;
    }

    if(strcmp(str, "Congratulations!") == 0) {
        system("/bin/sh");
    } else {
        puts("Invalid Password!");
    }
}

void test(int input, int target) {
    int diff = target - input;

    if(diff > 0 && diff <= 21) {
        decrypt(diff);
    } else {
        decrypt(rand());
    }
}

int main() {
    srand(time(NULL));

    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");

    printf("Password:");
    int password;
    scanf("%d", &password);

    test(password, 0x1337d00d);

    return 0;
}
