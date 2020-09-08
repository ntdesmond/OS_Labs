#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    for (int i = 0; i < 5; i++) {
        fork();
        sleep(5);
    }
    return 0;
}
// There are 2^n processes created in total, since every fork() call doubles the process count.
