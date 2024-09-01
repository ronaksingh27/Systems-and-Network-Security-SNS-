#include <stdio.h>
#include <stdlib.h>

void extendedGCD(int a, int b, int* gcd, int* x, int* y) {
    if (a == 0) {
        *gcd = b;
        *x = 0;
        *y = 1;
        return;
    }
    int x1, y1;
    extendedGCD(b % a, a, gcd, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
}

void multiplicativeInverse(int a, int m) {
    int gcd, x, y;
    extendedGCD(a, m, &gcd, &x, &y);
    if (gcd != 1)
        printf("N\n");
    else {
        printf("Y\n%d\n", (x % m + m) % m);
    }
}

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int m = atoi(argv[2]);
    multiplicativeInverse(a, m);
    return 0;
}
