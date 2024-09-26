#include <stdio.h>

typedef long long quad_t;

quad_t func(quad_t a0, quad_t a1, quad_t a2, quad_t a3, quad_t a4) {
    return ((a1 - (a2 + (a3 & (a1 ^ a4)))) ^ a0);
}

int main() {
    // Test the func with some example values
    quad_t a0 = 2;
    quad_t a1 = 3;
    quad_t a2 = 4;
    quad_t a3 = 5;
    quad_t a4 = 6;

    quad_t result = func(a0, a1, a2, a3, a4);
    printf("Result: %lld\n", result);
}

// Notes for compiling and running:
// gcc -o 2_4 2_4.c
// ./2_4
