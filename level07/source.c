#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void clear_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

unsigned int get_unum(void) {
    unsigned int local_10[3];

    local_10[0] = 0;
    fflush(stdout);
    scanf("%u", local_10);
    clear_stdin();
    return local_10[0];
}

int store_number(unsigned int* storage) {
    unsigned int number;
    unsigned int index;

    printf(" Number: ");
    number = get_unum();

    printf(" Index: ");
    index = get_unum();

    if ((index % 3 == 0) || ((number >> 24) == 0xb7)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
    storage[index] = number;
    return 0;
}

int read_number(unsigned int* storage) {
    unsigned int index;

    printf(" Index: ");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, storage[index]);
    return 0;
}

int main(int argc, char** argv, char** envp) {
    unsigned int storage[100];
    char command[20];
    int result = 1;
    int i;

    for (i = 0; argv[i] != NULL; i++) {
        memset(argv[i], 0, strlen(argv[i]));
    }

    for (i = 0; envp[i] != NULL; i++) {
        memset(envp[i], 0, strlen(envp[i]));
    }
    memset(storage, 0, sizeof(storage));
    memset(command, 0, sizeof(command));
    puts("----------------------------------------------------");
    puts("  Welcome to wil's crappy number storage service!   ");
    puts("----------------------------------------------------");
    puts(" Commands:                                          ");
    puts("    store - store a number into the data storage    ");
    puts("    read  - read a number from the data storage     ");
    puts("    quit  - exit the program                        ");
    puts("----------------------------------------------------");
    puts("   wil has reserved some storage :>                 ");
    puts("----------------------------------------------------");
    while (1) {
        printf("Input command: ");
        result = 1;
        fgets(command, 20, stdin);
        unsigned int len = strlen(command);
        if (len > 0 && command[len-1] == '\n') {
            command[len-1] = '\0';
        }
        if (strcmp(command, "store") == 0) {
            result = store_number(storage);
        }
        else if (strcmp(command, "read") == 0) {
            result = read_number(storage);
        }
        else if (strcmp(command, "quit") == 0) {
            return 0;
        }
        if (result == 0) {
            printf(" Completed %s command successfully\n", command);
        } else {
            printf(" Failed to do %s command\n", command);
        }
        memset(command, 0, sizeof(command));
    }

    return 0;
}
