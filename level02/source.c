#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char input_pass[112] = {0};
    char pass[48] = {0};
    char username[100] = {0};
    size_t len = 0;
    FILE *passfile = NULL;

    passfile = fopen("/home/users/level03/.pass", "r");
    if (passfile == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }
    len = fread(pass, 1, 41, passfile);
    pass[strcspn(pass, "\n")] = '\0';

    if (len != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }
    fclose(passfile);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("--[ Password: ");
    fgets(input_pass, 100, stdin);
    input_pass[strcspn(input_pass, "\n")] = '\0';
    puts("*****************************************");
    if (strncmp(pass, input_pass, 41) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    }
    printf(username);
    puts(" does not have access!");
    exit(1);
}
