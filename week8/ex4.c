#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

int main() {
    void *chunks[10];
    struct rusage usage_info;
    for (int i = 0; i < 10; i++) {
        chunks[i] = malloc(10*1024*1024); // allocate 10 MiB
        memset(chunks[i], 0, 10*1024*1024); // fill these with zeroes
        getrusage(RUSAGE_SELF, &usage_info);
        printf("%ld %ld %ld %ld \n", usage_info.ru_maxrss, usage_info.ru_ixrss, usage_info.ru_idrss, usage_info.ru_isrss);
        sleep(1);
    }
    for (int i = 0; i < 10; i++) {
        free(chunks[i]); // free the memory
    }

    return 0;
}

// Ex. 4
// The trouble of getrusage is that it shoes only max memory usage; integral memory values are not used in Linux.
// So after the memory freeing the maxrss value remains the same (about 100 MiB)
