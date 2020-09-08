#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Welcome to the YAWsh - Yet Another Worthless Shell. Type in whatever you want below.\nAnd yeah, we don't support arguments yet. Sorry. \n");
    char cmd[200];
    while (1) {
        printf("YAWsh > ");
        scanf("%s", cmd);
        system(cmd);
    }
    return 0;
}
