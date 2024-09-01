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

int chineseRemainderTheorem(int a[], int n[], int len) {
    int x = 0, N = 1;
    for (int i = 0; i < len; i++)
        N *= n[i];

    for (int i = 0; i < len; i++) {
        int ni = N / n[i];
        int x1, y1, gcd;
        extendedGCD(ni, n[i], &gcd, &x1, &y1);
        x += a[i] * y1 * ni;
    }

    return (x % N + N) % N;
}

int main(int argc, char *argv[]) {
    int len = (argc - 1) / 2;
    int a[len], n[len];
    for (int i = 0; i < len; i++) {
        a[i] = atoi(argv[2*i + 1]);
        n[i] = atoi(argv[2*i + 2]);
    }
    int result = chineseRemainderTheorem(a, n, len);
    printf("Y\n%d\n", result);
    return 0;
}
