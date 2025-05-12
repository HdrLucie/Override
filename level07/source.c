#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_STORAGE 100
#define MAX_COMMAND_LENGTH 20

void clear_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

unsigned int get_unum(void) {
    unsigned int number = 0;
    unsigned int local_input[3] = {0};
    fflush(stdout);
    if (scanf("%u", &local_input[0]) != 1) {
        printf("Erreur de lecture du nombre\n");
        local_input[0] = 0;
    }
    clear_stdin();
    return local_input[0];
}

int store_number(uint32_t* storage) {
    printf(" Number: ");
    uint32_t number = get_unum();
    
    printf(" Index: ");
    uint32_t index = get_unum();
    if ((index % 3 == 0) || ((number >> 24) == 0xb7)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
    if (index >= MAX_STORAGE) {
        puts(" *** Index out of bounds! ***");
        return 1;
    }
    
    storage[index] = number;
    return 0;
}

int read_number(uint32_t* storage) {
    printf(" Index: ");
    uint32_t index = get_unum();
    
    if (index >= MAX_STORAGE) {
        puts(" *** Index out of bounds! ***");
        return 1;
    }
    
    printf(" Number at index %u: %u\n", index, storage[index]);
    return 0;
}

int main() {
    char command[MAX_COMMAND_LENGTH] = {0};
    uint32_t storage[MAX_STORAGE] = {0};
    
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
    while (true) {
        printf("Input command: ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        command[strcspn(command, "\n")] = 0;
        if (strcmp(command, "store") == 0) {
            if (store_number(storage) == 0) {
                printf(" Completed %s command successfully\n", command);
            } else {
                printf(" Failed to do %s command\n", command);
            }
        }
        else if (strcmp(command, "read") == 0) {
            if (read_number(storage) == 0) {
                printf(" Completed %s command successfully\n", command);
            } else {
                printf(" Failed to do %s command\n", command);
            }
        }
        else if (strcmp(command, "quit") == 0) {
            break;
        }
        else {
            printf(" Unknown command: %s\n", command);
        }
    }
    
    return 0;
}
