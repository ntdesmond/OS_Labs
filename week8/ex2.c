#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *chunks[10];
    for (int i = 0; i < 10; i++) {
        chunks[i] = malloc(10*1024*1024); // allocate 10 MiB
        memset(chunks[i], 0, 10*1024*1024); // fill these with zeroes
        sleep(1);
    }
    for (int i = 0; i < 10; i++) {
        free(chunks[i]); // free the memory
    }

    return 0;
}

// Ex. 2
// The code above doesn't trigger swap usage since my laptop has enough physical memory to fit 100 MiB
// Thus, si and so in vmstat output are equal to 0 at each iteration
//
// Ex. 3
// top output shows the increasing amount of memory used by the program (in my case max memory used was 104M)
// p.s. I prefer htop instead of usual top
