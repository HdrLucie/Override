# Level07

This level was quite difficult and long.

First of all, let's explain how the program works: an array of size 100 is allocated on the stack.

We can store data (with the command "**store**") in this array at any index we like, **except for indexes that are divisible by 3**. 

We can then access the data in the array with the “**read**” command and by entering the required index.

We also note that the program makes it impossible to use the environment or arguments with the memset function. 
Putting shellcode in our env will therefore be useless for exploiting a vulnerability in the program.

On the other hand, we can try to overwrite the eip. And that's what we're going to do. 
We can overwrite the EIP because the program **doesn't check whether the given index is out of bounds**.

One way of doing this would be to put our [shellcode](https://github.com/HdrLucie/Override/blob/main/level07/shellcode.asm) in our array and overwrite the eip address to store the address of the beginning of our shellcode. To do this, we use the shellcode we wrote for a previous level. We need to convert it into several int in order to store them in our array. Nevertheless, we find ourselves confronted with the problem mentioned above: we can't write data to indexes divisible by 3. So we need to find a way around this problem.

Since the array is an int array, the index is multiplied by 4 to calculate the address of the value. This means that the two most significant bits will be lost. 
To store at an index divisible by 3, we can therefore add `2 ^ 31 + our index` to this index, which will give a value that is not divisible by 3, but multiplied by 4, will give the desired address. 

For example, to store a value at index 3/byte 12:
> (2 ^ 31 + 3) * 4 = 3 * 4.

In this way, we can store parts of our shellcode contiguously in the table.

The last thing to do is find the index to overwrite our EIP:
> (array address - eip backup address) / 4 == 114.

To simplify the work, we've written a [script](https://github.com/HdrLucie/Override/blob/main/level07/payload_generator.bash) that converts our shellcode to decimal and stores our data in an array. Then, to browse this array, we call the store command, check whether our index is divisible by 3 or not and write the index accordingly. 
Once the array has been browsed, we overwrite our eip. Then quit.

All that remains is to copy the output from our bash into the program. And if all goes well, our shellcode executes and the flag is written. 
And that's it! Not the simplest.
