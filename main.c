// main.c
#include <stdio.h>
#include "lib_math.h"

int main() {
    int sum = add(5, 3);
    int difference = subtract(5, 3);
    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", difference);
    return 0;
}