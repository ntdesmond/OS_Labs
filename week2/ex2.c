//Ex. 2
#include <stdio.h>
#include <string.h>

int main() {
    char str[200];
    printf("Enter a string: ");
    scanf("%s", str);
    printf("Reversed string: ");
    for (unsigned int i = strlen(str); i > 0; i--)
        printf("%c", str[i-1]);
    printf("\n");

    return 0;
}
