# Level01

Level00 is very similar to Rainfall's level0. 

In fact, we have a “main” function, which reads from stdin with the scanf function. We're asked to enter a password. In the assembler, we can read the following line: 

```0x080484e7 <+83>: cmp $0x149c,%eax.```

If we enter the value 0x149c (5276), a shell is executed with the UID level01, giving us access to the token for level01. 
That's it.
