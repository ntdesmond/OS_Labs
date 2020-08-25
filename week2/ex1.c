//Ex. 1
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int a = INT_MAX;
    float b = FLT_MAX;
    double c = DBL_MAX;
    printf("Value is %d, %lu bytes\n", a, sizeof(a));
    printf("Value is %f, %lu bytes\n", b, sizeof(b));
    printf("Value is %f, %lu bytes\n", c, sizeof(c));

    return 0;
}
