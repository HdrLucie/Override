int auth(char *login, unsigned int serial)
{
    size_t len;
    int i;
    unsigned int hash;
    size_t newline_pos = strcspn(login, "\n");
    login[newline_pos] = '\0';
    len = strnlen(login, 32);
    if (len < 6) {
        return 1;
    }
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
        puts("\x1b[32m.---------------------------.");
        puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1b[32m\'---------------------------\'");
        return 1;
    }
    hash = ((int)login[3] ^ 0x1337) + 0x5EEDED;
  
    for (i = 0; i < len; i++) {
        if (login[i] < ' ') {
            return 1;
        }
        hash += ((int)login[i] ^ hash) % 0x539;
    }
    if (serial == hash) {
        return 0;
    } else {
        return 1;
    }
}

int main(void)
{
    char login[32];
    unsigned int serial;
    int result;
    
    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    fgets(login, 32, stdin);
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");
    scanf("%u", &serial);
    result = auth(login, serial);
    if (result == 0) {
        puts("Authenticated!");
        system("/bin/sh");
    }
    return (result != 0);
}
