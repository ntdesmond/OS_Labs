#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int n = fork();
    if (n == 0)
        printf("Hello from child [PID - %d]\n", getpid());
    else
        printf("Hello from parent [PID - %d]\n", getpid());
    return 0;
}
// PIDs are different at each execution since PIDS are not reused until the next system reboot.
