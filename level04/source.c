#include <string.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char	input[128];
    int		childStatus;
    int		waitStatus;
    long	syscallnb;
    pid_t	childPid;
    memset(input, 0, sizeof(input));
    childPid = fork();
    if (childPid == 0) {
        prctl(PR_SET_PDEATHSIG, SIGKILL);
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(input);
    } else {
        while (1) {
            wait(&waitStatus);
            if (WIFEXITED(waitStatus) || WIFSIGNALED(waitStatus)) {
                puts("child is exiting...");
                return 0;
            }
            syscallnb = ptrace(PTRACE_PEEKUSER, childPid, 4 * 0x2c, 0); //0x2c = 44
            // Syscallnumber 11 stands for an execve call. 
            if (syscallnb == 11) {
                puts("no exec() for you");
                kill(childPid, SIGKILL);
                break;
            }
        }
    }
    return 0;
}
