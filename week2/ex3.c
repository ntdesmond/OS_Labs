//Ex. 3
//Tried to think of some more figures :)

#include <stdio.h>
#include <stdlib.h>

void isosceles(int height) {
    int count = 2 * height - 1;
    for (unsigned short stars = 1; stars <= count; stars += 2) {
        int spaces = (count - stars) / 2;
        for (unsigned short i = 0; i < count; i++) {
            if (i >= spaces && i < spaces + stars)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void rectangle(int height) {
    for (unsigned short line = 0; line < height; line++) {
        for (unsigned short column = 0; column < height / 2; column++) {
            printf("*");
        }
        printf("\n");
    }
}

void grid(int height) {
    if (height < 3) {
        printf("The minimal height for the grid is 3.\n");
        return;
    }
    for (unsigned short line = 0; line < height; line++) {
        //using char as bool, lol
        char star = line % 2 == 1;
        for (unsigned short column = 0; column < height; column++) {
            printf(star ? "*" : " ");
            if (line % 2 == 0)
                star = !star;
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("You must specify the height and the type of the drawing! e.g. ./third.out 5 2\n\n");
        printf("Possible options for drawing:\n");
        printf("1) Isosceles triangle\n");
        printf("2) Vertical rectangle (half of a square, rounded down if number is odd)\n");
        printf("3) Grid (1x1 squares, height must be at least 3)\n");
        return 0;
    }
    char type = *argv[2];
    int height = atoi(argv[1]);
    switch (type) {
        case '1':
            isosceles(height);
            break;
        case '2':
            rectangle(height);
            break;
        case '3':
            grid(height);
            break;
        default:
            printf("Wrong type specified! Only digits 1-3 are allowed");
            break;
    }
    return 0;
}
