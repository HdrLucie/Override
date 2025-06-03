# Level07

This level was quite difficult and long.

First, let's explain how the program works: a 100-element array is allocated on the stack.

We can store data in this array at any index using the "**store**" command, **except for indexes that are divisible by 3**. 

We can then access the data in the array using the "**read**" command by entering the desired index.

Note that the program prevents us from using environment variables or arguments with the memset function. This means placing shellcode in our environment variables won't help us exploit the program's vulnerability.

On the other hand, we can try to overwrite the EIP. And that's what we're going to do. 
We can overwrite the EIP because the program **doesn't check whether the given index is out of bounds**.

One way of doing this would be to put our [shellcode](https://github.com/HdrLucie/Override/blob/main/level07/shellcode.asm) in the array and overwrite the EIP address with the address of our shellcode. To do this, we'll use the shellcode we wrote for a previous level. We need to convert it into base 10 integers to store them in our array. Nevertheless, we face the problem mentioned above: we cannot write data to indexes divisible by 3.

Since the array is an array of `int`, the index is multiplied by 4 to calculate the address of the value. This means that the two most significant bits will be discarded. 
To store at an index divisible by 3, we can add `2^31` to the index, which gives a value that is not divisible by 3, but when multiplied by 4, produces the desired address.

For example, to store a value at index 3 (byte 12):
> (2^31 + 3) * 4 = 3 * 4

This way, we can store parts of our shellcode contiguously in the array.

The final step is finding the index to overwrite our EIP:
> (array address - eip backup address) / 4 == 114.

To simplify the process, we've written a [script](https://github.com/HdrLucie/Override/blob/main/level07/payload_generator.bash) that converts our shellcode to decimal and generates the set of commands needed to input the shellcode in the array, taking care of the indexes that are multiples of 3. It then overwrites EIP, and exits.

All that remains is to copy the output from our bash script into the program. And if all goes well, our shellcode is executed and the flag is displayed. 
And that's it! Not the simplest level for sure.
