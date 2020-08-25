//Ex. 4
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int a, b;
    printf("Enter number A: ");
    scanf("%d", &a);
    printf("Enter number B: ");
    scanf("%d", &b);
    printf("Swapping...\n");
    swap(&a, &b);
    printf("Number A is %d, number B is %d\n", a, b);
    return 0;
}
