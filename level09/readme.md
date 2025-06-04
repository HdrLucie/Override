# level09

Last one!

This binary asks the user for a username and a message, which are both stored. The message isn't sent anywhere, contrary to what the program pretends before exiting.

The first thing we note is that there's a never called function named `secret_backdoor`, which takes user input and directly pass it to a `system` call.

After having properly reverse-engineered the binary, it's revealed that the user inputs are stored in a **stack allocated structure**.

```C
struct user_data
{
    char message[140];
    char username[40];
    int msg_size;
};
```

Of course the first idea we have here is to overwrite RIP to make it point to the unused `secret_backdoor()` function. But the program is careful enough to only use `fgets`, on temporary buffers, to get user inputs.

When getting the message in the `set_msg()` function, `msg_size` is given as the length parameter of `strncpy`. `msg_size` is initialized at the creation of the struct in `handle_msg()` with a value of 140, which matches precisely the length of the message buffer.

When getting the username in the `set_username()` function, the string is copied by hand with a loop that goes until the end of the string or the 41st character. But wait... The username buffer in the struct is only **40** character long! Since we copy 41 characters, **we can overwrite the value just after**, which happens to be `msg_size`!

This means that **we can set msg_size to up to 255**. Which is more than enough, because the RIP is stored 200 bytes after the start of the message buffer.

> Note: Since the binary is compiled with PIE enabled, we need the program to be running to get the correct address of `secret_backdoor`.

Here's the exploit:

```bash
#    name padding v   message padding v                       newline to end message input v
python -c 'print "."*40 + "\xFF\n" + "."*200 + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1] + "\ncat /home/users/end/.pass"' | ./level09
#                 msg_size ^                    ^ secret_backdoor address                    ^ command to give to secret_backdoor
```

And that's it! 🎉
