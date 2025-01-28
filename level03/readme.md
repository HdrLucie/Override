# level03

This one is a reverse engineering exercise.

The program reads a number on stdin and tests if the value is the correct one by using it to try and decrypt a string.

More precisely, the test function checks if `0x1337d00d` minus the given value is between 1 and 21. If it is, it calls a decrypt function with this calculated value. Otherwise, it gives a random value to decrypt.

The decrypt function then iterates on this string: "Q}|u`sfg~sf{}|a3" and applies a xor with the given key on each byte. If the resulting string is "Congratulations!", decrypt opens a shell.

To find to correct key, we just need to xor between any corresponding characters, for example 'Q' and 'C'. We get a value of 18. Which means that the key is 0x1337d00d - 18 = 322424827. That's it!
