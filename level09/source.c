#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user_msg
{
    char data[140];
    char username[40];
    int msg_size;
    // Compiler adds here 8 bytes for alignment
};

void secret_backdoor()
{
    char input[128];

    fgets(input, 128, stdin);
    system(input);
}

void set_username(struct user_msg* msg)
{
    char buffer[128];
    int i;

    memset(buffer, 0, 128);

    puts("Enter your username");
    printf(">> ");

    fgets(buffer, 128, stdin);

    for (i = 0; i < 40 && buffer[i] != '\0'; i++)
    {
        msg->username[i] = buffer[i];
    }

    printf("Welcome, %s", msg->username);
}

void set_msg(struct user_msg* msg)
{
    char temp_msg[1024];

    memset(temp_msg, 0, 1024);

    puts("Msg @Unix-Dude");
    printf(">> ");

    fgets(temp_msg, 1024, stdin);

    strncpy(msg->data, temp_msg, msg->msg_size);
}

void handle_msg()
{
    struct user_msg msg;

    memset(msg.username, 0, 40);
    msg.msg_size = 140;

    set_username(&msg);
    set_msg(&msg);

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
