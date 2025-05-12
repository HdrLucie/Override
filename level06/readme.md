# level06

This executable asks for a login and a password, and verify if a debugger is currently in use
by calling `ptrace` and checking if it returns an error. If the login is at least 6 characters long
and no debugger is detected, a hash is generated from the login and if the password matches it,
a shell is opened.

We could create a program that generates the hash from a given login, but we just used gdb anyway.

We just need to change `ptrace`'s return value to avoid bypass the check, and then print the generated hash.

### Magic ✨

```bash
gdb -batch level06 -ex 'b * 0x080487ba' -ex 'b * 0x08048866' -ex 'r' -ex 'set $eax=0x1' -ex 'c' -ex 'p *(int *)($ebp - 0x10)' -ex 'c'
```

(Thanks to [this stackoverflow answer](https://stackoverflow.com/a/46867839))
