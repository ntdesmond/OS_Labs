#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Welcome to the IBSWsh - Improved But Still Worthless Shell. Type in whatever you want below.\nNow we support arguments!\n");
    while (1) {
        size_t size = 0;
        char *cmd = NULL;
        printf("IBSWsh > ");
        getline(&cmd, &size, stdin);
        system(cmd);
        free(cmd);
    }
    return 0;
}
