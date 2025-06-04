#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user_data
{
    char message[140];
    char username[40];
    int msg_size;
};

void secret_backdoor()
{
    char input[128];

    fgets(input, 128, stdin);
    system(input);
}

void set_username(struct user_data* user)
{
    char buffer[128];
    int i;

    memset(buffer, 0, 128);

    puts("Enter your username");
    printf(">> ");

    fgets(buffer, 128, stdin);

    for (i = 0; i <= 40 && buffer[i] != '\0'; i++)
    {
        user->username[i] = buffer[i];
    }

    printf("Welcome, %s", user->username);
}

void set_msg(struct user_data* user)
{
    char buffer[1024];

    memset(buffer, 0, 1024);

    puts("Msg @Unix-Dude");
    printf(">> ");

    fgets(buffer, 1024, stdin);

    strncpy(user->message, buffer, user->msg_size);
}

void handle_msg()
{
    struct user_data user;

    memset(user.username, 0, sizeof(user.username));
    user.msg_size = 140;

    set_username(&user);
    set_msg(&user);

    puts("Msg sent!");
}

int main()
{
    puts("--------------------------------------------\n"
         "|   ~Welcome to l33t-m$n ~    v1337        |\n"
         "--------------------------------------------");
    handle_msg();
    return 0;
}
